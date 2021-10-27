#include "VulkanGraphicsCard.h"
#include "VulkanSwapChain.h"

VulkanGraphicsCard::VulkanGraphicsCard(VkPhysicalDevice device) {
	this->physicalDevice = device;

	vkGetPhysicalDeviceProperties(device, &properties);
	vkGetPhysicalDeviceFeatures(device, &features);
}

int VulkanGraphicsCard::DeviceSuitability() {
	int score = 0;

	if(properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		score += 1000;

	score += static_cast<int>(properties.limits.maxImageDimension2D);

	if(!features.geometryShader)
		return 0;
	return score;
}

VkPhysicalDevice VulkanGraphicsCard::getPhysicalDevice() {
	return physicalDevice;
}

QueueFamilyIndices VulkanGraphicsCard::findQueueFamilies(VkSurfaceKHR surface) {
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);

		if (presentSupport) {
			indices.presentFamily = i;
		}

		if(indices.isComplete())
			break;

		i++;
	}

	return indices;
}

bool VulkanGraphicsCard::isDeviceSuitable(VkSurfaceKHR surface) {
	QueueFamilyIndices indices = findQueueFamilies(surface);

	bool extensionSupported = CheckDeviceExtensionSupport();

	bool swapChainAdequate = false;
	if (extensionSupported) {
		SwapChainSupportDetails swapChainSupport = VulkanSwapChain::QuerySwapChainSupport(physicalDevice, surface);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}

	return indices.isComplete() && extensionSupported && swapChainAdequate;
}

bool VulkanGraphicsCard::CheckDeviceExtensionSupport() {

	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

	vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

	set<string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}
