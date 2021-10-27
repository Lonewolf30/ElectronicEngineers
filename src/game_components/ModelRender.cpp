#include "ModelRender.h"

void ModelRender::CreateDraw(VkCommandBuffer commandBuffer) {
	VkBuffer vertexBuffers[] = {modelBuffer};
	VkDeviceSize offsets[] = {0};
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
	vkCmdBindIndexBuffer(commandBuffer, modelBuffer, sizeof(vertices[0]) * vertices.size(), VK_INDEX_TYPE_UINT16);
	vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
}

void ModelRender::CleanUp() {
	vkDestroyBuffer(logicalCard->GetLogicalDevice(), modelBuffer, nullptr);
	vkFreeMemory(logicalCard->GetLogicalDevice(), modelBufferMemory, nullptr);

	logicalCard = nullptr;
	graphicsCard = nullptr;
	commandPool = nullptr;
}

uint32_t ModelRender::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(graphicsCard->getPhysicalDevice(), &memProperties);
	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	throw runtime_error("failed to find suitable memory type!");
}

void ModelRender::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = commandPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(logicalCard->GetLogicalDevice(), &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	VkBufferCopy copyRegion{};
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(logicalCard->GetGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(logicalCard->GetGraphicsQueue());

	vkFreeCommandBuffers(logicalCard->GetLogicalDevice(), commandPool, 1, &commandBuffer);
}

void ModelRender::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
							   VkBuffer &buffer, VkDeviceMemory &bufferMemory) {
	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(logicalCard->GetLogicalDevice(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to create buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(logicalCard->GetLogicalDevice(), buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(logicalCard->GetLogicalDevice(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate buffer memory!");
	}

	vkBindBufferMemory(logicalCard->GetLogicalDevice(), buffer, bufferMemory, 0);
}

void ModelRender::CreateModelBuffer() {
	VkDeviceSize vertexBuffer = sizeof(vertices[0]) * vertices.size();
	VkDeviceSize indexBuffer = sizeof(indices[0]) * indices.size();

	VkDeviceSize totalSize = vertexBuffer + indexBuffer;

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	CreateBuffer(totalSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
				 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer,
				 stagingBufferMemory);

	void *data;
	vkMapMemory(logicalCard->GetLogicalDevice(), stagingBufferMemory, 0, vertexBuffer, 0, &data);
	memcpy(data, vertices.data(), (size_t) vertexBuffer);
	vkUnmapMemory(logicalCard->GetLogicalDevice(), stagingBufferMemory);
	vkMapMemory(logicalCard->GetLogicalDevice(), stagingBufferMemory, vertexBuffer, indexBuffer, 0, &data);
	memcpy(data, indices.data(), (size_t) indexBuffer);
	vkUnmapMemory(logicalCard->GetLogicalDevice(), stagingBufferMemory);

	CreateBuffer(totalSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
				 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, modelBuffer, modelBufferMemory);

	CopyBuffer(stagingBuffer, modelBuffer, totalSize);

	vkDestroyBuffer(logicalCard->GetLogicalDevice(), stagingBuffer, nullptr);
	vkFreeMemory(logicalCard->GetLogicalDevice(), stagingBufferMemory, nullptr);
}

void
ModelRender::InitialiseRendering(VulkanLogicalCard *card, VulkanGraphicsCard* graphicsCard, VkCommandPool commandPool) {
	this->logicalCard = card;
	this->graphicsCard = graphicsCard;
	this->commandPool = commandPool;

	CreateModelBuffer();
}

void ModelRender::UpdateUniforms() {
}

int ModelRender::GetValue() {
	return 5;
}
