#include <vector>
#include "VulkanDebugger.h"

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
													VkDebugUtilsMessageTypeFlagsEXT messageType,
													const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
													void *pUserData) {
	if (messageSeverity > VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		cerr << "validation layer: " << pCallbackData->pMessage << endl;

	return VK_FALSE;
}

void VulkanDebugger::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
}

VkResult
VulkanDebugger::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo) {
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, nullptr, &debugMessenger);
	} else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void VulkanDebugger::DestroyDebugUtilsMessengerEXT(VkInstance instance) {
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance,
																			"vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(instance, debugMessenger, nullptr);
	}
}

void VulkanDebugger::CleanUp(VkInstance instance) {
	DestroyDebugUtilsMessengerEXT(instance);
}

void VulkanDebugger::Initialise(VkInstance instance) {
	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	PopulateDebugMessengerCreateInfo(createInfo);
	if (CreateDebugUtilsMessengerEXT(instance, &createInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to set up debug messenger!");
	}
}

bool VulkanDebugger::CheckValidationLayerSupport() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char *layerName: validationLayers) {
		bool layerFound = false;

		for (const auto &layerProperties: availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}
