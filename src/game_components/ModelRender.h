#include <vulkan/vulkan.h>

#ifndef ELECTRONICENGINEERS_MODELRENDER_H
#define ELECTRONICENGINEERS_MODELRENDER_H

#include "../rendering/vulkan/VulkanLogicalCard.h"
#include "GameComponent.h"
#include "../core/Vertex.h"

const std::vector<Vertex> vertices = {
		{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
};

const std::vector<uint16_t> indices = {
		0,1,2,2,3,0
};

class ModelRender : public GameComponent{
public:
	void InitialiseRendering(VulkanLogicalCard* card, VulkanGraphicsCard* graphicsCard, VkCommandPool commandPool);
	void UpdateUniforms();
	void CreateDraw(VkCommandBuffer commandBuffer);

	void CleanUp() override;

	int GetValue() override;

private:
	void CreateModelBuffer();
	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer,
					  VkDeviceMemory &bufferMemory);
	uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	VulkanLogicalCard* logicalCard = nullptr;
	VulkanGraphicsCard* graphicsCard = nullptr;
	VkCommandPool commandPool = {};

	VkBuffer modelBuffer = {};
	VkDeviceMemory modelBufferMemory = {};
};


#endif
