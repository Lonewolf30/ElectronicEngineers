#include <vulkan/vulkan.h>
#include <iostream>

#ifndef ELECTRONICENGINEERS_VULKANDEBUGGER_H
#define ELECTRONICENGINEERS_VULKANDEBUGGER_H

using namespace std;

class VulkanDebugger {
private:
	VkDebugUtilsMessengerEXT debugMessenger;
	void DestroyDebugUtilsMessengerEXT(VkInstance instance);
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo);

public:
	static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
	void Initialise(VkInstance instance);
	void CleanUp(VkInstance instance);
	bool CheckValidationLayerSupport();

	const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
	};
};


#endif