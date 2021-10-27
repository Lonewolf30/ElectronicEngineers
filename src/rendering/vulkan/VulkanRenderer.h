#include <vector>
#include <string>

#ifndef ELECTRONICENGINEERS_VULKANRENDERER_H
#define ELECTRONICENGINEERS_VULKANRENDERER_H

using namespace std;

#include "../Display.h"
#include "VulkanGraphicsCard.h"
#include "VulkanLogicalCard.h"
#include "VulkanDebugger.h"
#include "VulkanSwapChain.h"
#include "../openvr/VREnvironment.h"
#include "VulkanShader.h"

#include "../../core/Game.h"
#include "../../core/Game.h"

class VulkanRenderer {
private:
	#ifdef NDEBUG
	const bool enableValidationLayers = false;
	#else
	const bool enableValidationLayers = true;
	#endif

	Display* display;
	Configuration* configuration;
	Game* game;

	vector<VulkanGraphicsCard*> graphicsCards;
	VulkanGraphicsCard* selectedCard;
	VulkanLogicalCard* logicalCard;
	VulkanDebugger* vulkanDebugger;
	VulkanSwapChain* vulkanSwapChain;
	VulkanShader* vulkanShader;

	VkInstance instance;
	VkSurfaceKHR  surface;
	VkRenderPass renderPass;

	vector<VkImageView> swapChainImageViews;
	vector<VkFramebuffer> swapChainFrameBuffers;
	VkCommandPool commandPool;
	vector<VkCommandBuffer> commandBuffers;

	int currentFrame = 0;
	const int MAX_FRAMES_IN_FLIGHT = 2;

	vector<VkSemaphore> imageAvailableSemaphores;
	vector<VkSemaphore> renderFinishedSemaphores;
	vector<VkFence> inFlightFences;
	vector<VkFence> imagesInFlight;

	void CreateVulkanInstance();
	vector<const char*> GetRequiredExtensions();
	void PickPhysicalDevice();
	void CreateSurface();
	void CreateImageViews();
	void CreateFrameBuffers();
	void CreateCommandPool();
	void CreateCommandBuffers();
	void CreateRenderPass();
	void CreateSyncObjects();
	void SetupDebugMessenger();
	void RecreateSwapChain();
	void CleanUpSwapChain();
public:
	VulkanRenderer(Display* display, Configuration* configuration);
	void Initialise();
	void SetGame(Game* game);
	void Draw();
	void CleanUp();
};


#endif
