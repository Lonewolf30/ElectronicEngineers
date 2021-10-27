cmake_minimum_required(VERSION 3.19)
project("ElectronicEngineers")

set(CMAKE_CXX_STANDARD 17)

set(CORE src/core/Time.h
        src/core/Vector2.h
        src/core/Vector3.h
        src/core/Quaternion.h
        src/core/Matrix4f.h
        src/core/GameObject.cpp src/core/GameObject.h
        src/core/Transform.cpp src/core/Transform.h
        src/core/Vertex.cpp src/core/Vertex.h
        src/game_components/GameComponent.h
        src/core/Configuration.cpp src/core/Configuration.h
        src/core/FileManager.cpp src/core/FileManager.h
        src/core/MathHelper.h
        src/Program.cpp src/scene/Scene.h src/core/Game.cpp src/core/Game.h)

set(CLIENT
        src/rendering/RenderingEngine.cpp src/rendering/RenderingEngine.h
        src/rendering/Display.cpp src/rendering/Display.h

        src/core/Mouse.cpp src/core/Mouse.h
        src/core/Keyboard.cpp src/core/Keyboard.h

        src/rendering/vulkan/VulkanRenderer.cpp src/rendering/vulkan/VulkanRenderer.h
        src/rendering/vulkan/VulkanGraphicsCard.cpp src/rendering/vulkan/VulkanGraphicsCard.h
        src/rendering/vulkan/VulkanLogicalCard.cpp src/rendering/vulkan/VulkanLogicalCard.h
        src/rendering/vulkan/VulkanDebugger.cpp src/rendering/vulkan/VulkanDebugger.h
        src/rendering/vulkan/VulkanSwapChain.cpp src/rendering/vulkan/VulkanSwapChain.h
        src/rendering/openvr/VRHandController.cpp src/rendering/openvr/VRHandController.h
        src/rendering/openvr/VREnvironment.cpp src/rendering/openvr/VREnvironment.h
        src/rendering/vulkan/VulkanShader.cpp src/rendering/vulkan/VulkanShader.h
        src/game_components/Camera.cpp src/game_components/Camera.h
        src/game_components/ModelRender.cpp src/game_components/ModelRender.h src/scene/MainMenu.h src/scene/MainMenu.cpp)

add_executable(${PROJECT_NAME} src/Program.cpp ${CORE} ${CLIENT})

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/glfw/lib/glfw3.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/glfw/include")
target_link_libraries(${PROJECT_NAME} glfw)

find_package(Vulkan REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

add_library(openvr STATIC IMPORTED)
set_target_properties(openvr PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/openvr/lib/win64/openvr_api.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/openvr/include")
target_link_libraries(${PROJECT_NAME} openvr)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/openvr/bin/openvr_api.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")


add_custom_target(copy)
add_custom_command(TARGET copy PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources" "${CMAKE_CURRENT_BINARY_DIR}/Resources")
add_dependencies(${PROJECT_NAME} copy)