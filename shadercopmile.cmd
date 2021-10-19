mkdir .\Resources
mkdir .\Resources\Shaders

C:\VulkanSDK\1.2.182.0\Bin32\glslc.exe .\res\shaders\UserInterface.vert -o .\Resources\Shaders\userinterfacevert.spv
C:\VulkanSDK\1.2.182.0\Bin32\glslc.exe .\res\shaders\UserInterface.frag -o .\Resources\Shaders\userinterfacefrag.spv