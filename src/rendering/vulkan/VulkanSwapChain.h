#include <vulkan/vulkan.h>
#include <vector>

#ifndef ELECTRONICENGINEERS_VULKANSWAPCHAIN_H
#define ELECTRONICENGINEERS_VULKANSWAPCHAIN_H

#include "VulkanLogicalCard.h"

using namespace std;

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	vector<VkSurfaceFormatKHR> formats;
	vector<VkPresentModeKHR> presentModes;
};

class VulkanSwapChain {
private:
	VulkanLogicalCard* logicalCard;

public:
	vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	VkSwapchainKHR swapChain;

	VulkanSwapChain(VkSurfaceKHR surface, Vector2<int> displaySize, VulkanGraphicsCard *graphicsCard,
					VulkanLogicalCard *logicalCard);

	void CleanUp();
	static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const vector<VkSurfaceFormatKHR> &availableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const vector<VkPresentModeKHR> &availablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, Vector2<int> displaySize);
};


#endif
