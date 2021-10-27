#include <set>

#ifndef ELECTRONICENGINEERS_VULKANLOGICALCARD_H
#define ELECTRONICENGINEERS_VULKANLOGICALCARD_H

using namespace std;

#include "../Display.h"
#include "VulkanGraphicsCard.h"

class VulkanLogicalCard {
private:
	VkDevice logicalDevice;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

public:
	VkDevice GetLogicalDevice();
	explicit VulkanLogicalCard(VulkanGraphicsCard* card, VkSurfaceKHR surface);

	VkQueue GetGraphicsQueue();
	VkQueue GetPresentQueue();

	void CleanUp();
};


#endif
