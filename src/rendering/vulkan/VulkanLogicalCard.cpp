#include "VulkanLogicalCard.h"

void VulkanLogicalCard::CleanUp() {
	vkDestroyDevice(logicalDevice, nullptr);
}

VulkanLogicalCard::VulkanLogicalCard(VulkanGraphicsCard* card, VkSurfaceKHR surface) {
	logicalDevice = {};
	graphicsQueue = {};
	presentQueue = {};

	QueueFamilyIndices indices = card->findQueueFamilies(surface);

	vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures{};

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = static_cast<uint32_t>(card->deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = card->deviceExtensions.data();

	if (vkCreateDevice(card->getPhysicalDevice(), &createInfo, nullptr, &logicalDevice) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}

	vkGetDeviceQueue(logicalDevice, indices.graphicsFamily.value(), 0, &graphicsQueue);
	vkGetDeviceQueue(logicalDevice, indices.presentFamily.value(), 0, &presentQueue);
}

VkDevice VulkanLogicalCard::GetLogicalDevice() {
	return logicalDevice;
}

VkQueue VulkanLogicalCard::GetGraphicsQueue() {
	return graphicsQueue;
}

VkQueue VulkanLogicalCard::GetPresentQueue() {
	return presentQueue;
}
