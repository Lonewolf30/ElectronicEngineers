#include "VulkanRenderer.h"

#include "../../game_components/ModelRender.h"

void VulkanRenderer::Initialise() {
	vulkanDebugger = new VulkanDebugger();
	CreateVulkanInstance();
	SetupDebugMessenger();
	CreateSurface();
	PickPhysicalDevice();
	logicalCard = new VulkanLogicalCard(selectedCard, surface);

	vulkanSwapChain = new VulkanSwapChain(surface, *display->GetDisplaySize(), selectedCard, logicalCard);
	CreateImageViews();
	CreateRenderPass();
	vulkanShader = new VulkanShader(vulkanSwapChain, logicalCard, renderPass);
	CreateFrameBuffers();
	CreateCommandPool();

	// Run Model Creation
	for (auto &object : game->GetGameObjects()){
		for (auto& component : object.GetComponentsOfType<ModelRender>()){
			if(auto* render = dynamic_cast<ModelRender*>(component)){
				render->InitialiseRendering(logicalCard, selectedCard, commandPool);
			}
		}
	}

	CreateCommandBuffers();
	CreateSyncObjects();
}

void VulkanRenderer::SetupDebugMessenger() {
	if (!enableValidationLayers) return;
	vulkanDebugger->Initialise(instance);
}

VulkanRenderer::VulkanRenderer(Display *display, Configuration *configuration) {
	this->display = display;
	this->configuration = configuration;

	instance = {};
	surface = {};
	renderPass = {};
	commandPool = {};

	selectedCard = nullptr;
	logicalCard = nullptr;
	vulkanDebugger = nullptr;
	vulkanSwapChain = nullptr;
	vulkanShader = nullptr;
	game = nullptr;
}

void VulkanRenderer::CreateSyncObjects() {
	imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
	imagesInFlight.resize(swapChainImageViews.size(), VK_NULL_HANDLE);

	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		if (vkCreateSemaphore(logicalCard->GetLogicalDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) !=
			VK_SUCCESS ||
			vkCreateSemaphore(logicalCard->GetLogicalDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) !=
			VK_SUCCESS ||
			vkCreateFence(logicalCard->GetLogicalDevice(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create synchronization objects for a frame!");
		}
	}
}

void VulkanRenderer::Draw() {
	vkWaitForFences(logicalCard->GetLogicalDevice(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(logicalCard->GetLogicalDevice(), vulkanSwapChain->swapChain, UINT64_MAX,
											imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);
	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		RecreateSwapChain();
		return;
	} else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw runtime_error("failed to acquire swap chain image!");
	}

	if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
		vkWaitForFences(logicalCard->GetLogicalDevice(), 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
	}
	imagesInFlight[imageIndex] = inFlightFences[currentFrame];

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

	VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(logicalCard->GetLogicalDevice(), 1, &inFlightFences[currentFrame]);

	if (vkQueueSubmit(logicalCard->GetGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = {vulkanSwapChain->swapChain};
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;

	result = vkQueuePresentKHR(logicalCard->GetPresentQueue(), &presentInfo);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || display->HasFrameBufferResized()) {
		display->SetFrameBufferResized(false);
		RecreateSwapChain();
	} else if (result != VK_SUCCESS) {
		throw runtime_error("failed to present swap chain image!");
	}

	vkWaitForFences(logicalCard->GetLogicalDevice(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void VulkanRenderer::CreateVulkanInstance() {
	if (enableValidationLayers && !vulkanDebugger->CheckValidationLayerSupport()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Electronic Engineering";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.pEngineName = "Lone Development Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_2;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = GetRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(vulkanDebugger->validationLayers.size());
		createInfo.ppEnabledLayerNames = vulkanDebugger->validationLayers.data();

		VulkanDebugger::PopulateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *) &debugCreateInfo;
	} else {
		createInfo.enabledLayerCount = 0;
		createInfo.pNext = nullptr;
	}

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}
}

vector<const char *> VulkanRenderer::GetRequiredExtensions() {
	uint32_t glfwExtensionCount = 0;
	const char **glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}

void VulkanRenderer::CleanUp() {
	vkWaitForFences(logicalCard->GetLogicalDevice(), inFlightFences.size(), inFlightFences.data(), true, -1);
	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		vkDestroySemaphore(logicalCard->GetLogicalDevice(), renderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(logicalCard->GetLogicalDevice(), imageAvailableSemaphores[i], nullptr);
		vkDestroyFence(logicalCard->GetLogicalDevice(), inFlightFences[i], nullptr);
	}

	CleanUpSwapChain();

	vkDestroyCommandPool(logicalCard->GetLogicalDevice(), commandPool, nullptr);
	logicalCard->CleanUp();

	if (enableValidationLayers) {
		vulkanDebugger->CleanUp(instance);
	}

	vkDestroySurfaceKHR(instance, surface, nullptr);
	vkDestroyInstance(instance, nullptr);
}

void VulkanRenderer::PickPhysicalDevice() {
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	if (deviceCount == 0) {
		throw runtime_error("Failed to Find GPUs that support Vulkan");
	}
	vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	graphicsCards = vector<VulkanGraphicsCard *>(deviceCount);
	for (int i = 0; i < deviceCount; ++i) {
		graphicsCards[i] = new VulkanGraphicsCard(devices[i]);
	}

	selectedCard = graphicsCards[0];
	for (int i = 0; i < deviceCount; ++i) {
		if (graphicsCards[i]->DeviceSuitability() > selectedCard->DeviceSuitability())
			selectedCard = graphicsCards[i];
	}
}

void VulkanRenderer::CreateSurface() {
	display->CreateSurface(instance, &surface);
}

void VulkanRenderer::CreateRenderPass() {
	VkAttachmentDescription colorAttachment{};
	colorAttachment.format = vulkanSwapChain->swapChainImageFormat;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef{};
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass{};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;

	VkRenderPassCreateInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;

	if (vkCreateRenderPass(logicalCard->GetLogicalDevice(), &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
		throw std::runtime_error("failed to create render pass!");
	}
}

void VulkanRenderer::CreateImageViews() {
	swapChainImageViews.resize(vulkanSwapChain->swapChainImages.size());

	for (size_t i = 0; i < vulkanSwapChain->swapChainImages.size(); i++) {
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = vulkanSwapChain->swapChainImages[i];

		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = vulkanSwapChain->swapChainImageFormat;

		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(logicalCard->GetLogicalDevice(), &createInfo, nullptr, &swapChainImageViews[i]) !=
			VK_SUCCESS) {
			throw runtime_error("failed to create image views!");
		}
	}
}

void VulkanRenderer::CreateFrameBuffers() {
	swapChainFrameBuffers.resize(swapChainImageViews.size());

	for (size_t i = 0; i < swapChainImageViews.size(); i++) {
		VkImageView attachments[] = {
				swapChainImageViews[i]
		};

		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = 1;
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = vulkanSwapChain->swapChainExtent.width;
		framebufferInfo.height = vulkanSwapChain->swapChainExtent.height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(logicalCard->GetLogicalDevice(), &framebufferInfo, nullptr,
								&swapChainFrameBuffers[i]) != VK_SUCCESS) {
			throw runtime_error("failed to create framebuffer!");
		}
	}
}

void VulkanRenderer::CreateCommandPool() {
	QueueFamilyIndices queueFamilyIndices = selectedCard->findQueueFamilies(surface);

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
	poolInfo.flags = 0; // Optional

	if (vkCreateCommandPool(logicalCard->GetLogicalDevice(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
		throw runtime_error("failed to create command pool!");
	}
}


void VulkanRenderer::CreateCommandBuffers() {
	commandBuffers.resize(swapChainFrameBuffers.size());

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

	if (vkAllocateCommandBuffers(logicalCard->GetLogicalDevice(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
		throw runtime_error("failed to allocate command buffers!");
	}

	for (size_t i = 0; i < commandBuffers.size(); i++) {
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = 0; // Optional
		beginInfo.pInheritanceInfo = nullptr; // Optional

		if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
			throw runtime_error("failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = swapChainFrameBuffers[i];

		renderPassInfo.renderArea.offset = {0, 0};
		renderPassInfo.renderArea.extent = vulkanSwapChain->swapChainExtent;
		VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, vulkanShader->GetGraphicsPipeLine());
		{
			for (auto &object : game->GetGameObjects()){
				for (auto& component : object.GetComponentsOfType<ModelRender>()){
					if(auto* render = dynamic_cast<ModelRender*>(component)){
						render->CreateDraw(commandBuffers[i]);
					}
				}
			}
		}
		vkCmdEndRenderPass(commandBuffers[i]);

		if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
			throw runtime_error("failed to record command buffer!");
		}
	}
}

void VulkanRenderer::RecreateSwapChain() {
	Vector2<int> *displaySize = display->GetDisplaySize();
	while (displaySize->GetX() == 0 || displaySize->GetY() == 0) {
		displaySize = display->GetDisplaySize();
		Display::PollEvents();
	}

	vkDeviceWaitIdle(logicalCard->GetLogicalDevice());

	vulkanSwapChain = new VulkanSwapChain(surface, *display->GetDisplaySize(), selectedCard, logicalCard);
	CreateImageViews();
	CreateRenderPass();
	vulkanShader = new VulkanShader(vulkanSwapChain, logicalCard, renderPass);
	CreateFrameBuffers();
	CreateCommandBuffers();
}

void VulkanRenderer::CleanUpSwapChain() {

	for (auto framebuffer: swapChainFrameBuffers) {
		vkDestroyFramebuffer(logicalCard->GetLogicalDevice(), framebuffer, nullptr);
	}

	vulkanShader->CleanUp(logicalCard);
	vkDestroyRenderPass(logicalCard->GetLogicalDevice(), renderPass, nullptr);

	for (auto imageView: swapChainImageViews) {
		vkDestroyImageView(logicalCard->GetLogicalDevice(), imageView, nullptr);
	}

	vulkanSwapChain->CleanUp();

}

void VulkanRenderer::SetGame(Game* game) {
	this->game = game;
}


