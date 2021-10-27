#include <optional>
#include <set>
#include <string>
#include <vector>

#ifndef ELECTRONICENGINEERS_VULKANGRAPHICSCARD_H
#define ELECTRONICENGINEERS_VULKANGRAPHICSCARD_H

using namespace std;

#include "../Display.h"

struct QueueFamilyIndices {
	optional<uint32_t> graphicsFamily;
	optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

class VulkanGraphicsCard {
private:
	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;

public:
	const std::vector<const char *> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	explicit VulkanGraphicsCard(VkPhysicalDevice device);
	int DeviceSuitability();
	bool isDeviceSuitable(VkSurfaceKHR surface);
	VkPhysicalDevice getPhysicalDevice();

	QueueFamilyIndices findQueueFamilies(VkSurfaceKHR surface);

	bool CheckDeviceExtensionSupport();
};


#endif
