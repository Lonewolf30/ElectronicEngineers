#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <vulkan/vulkan.h>
#include "VulkanLogicalCard.h"
#include "VulkanSwapChain.h"

#ifndef ELECTRONICENGINEERS_VULKANSHADER_H
#define ELECTRONICENGINEERS_VULKANSHADER_H

using namespace std;

class VulkanShader {
public:
	VulkanShader(VulkanSwapChain* swapChain, VulkanLogicalCard* logicalCard, VkRenderPass renderPass);
	void CleanUp(VulkanLogicalCard* logicalCard);
	VkPipeline GetGraphicsPipeLine();
private:
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
};


#endif
