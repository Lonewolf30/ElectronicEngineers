if (!(Test-Path -Path '.\Resources' -PathType Container)) { mkdir .\Resources}
if (!(Test-Path -Path '.\Resources\Shaders' -PathType Container)) { mkdir .\Resources\Shaders}

C:\VulkanSDK\1.2.182.0\Bin32\glslc.exe .\res\shaders\shader_base.vert -o .\Resources\Shaders\vert.spv
C:\VulkanSDK\1.2.182.0\Bin32\glslc.exe .\res\shaders\shader_base.frag -o .\Resources\Shaders\frag.spv

