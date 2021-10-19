cmake_minimum_required(VERSION 3.19)
project("ElectronicEngineers")

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif ()

set(SCENE src/scene/MainMenu.h)

set(CORE src/core/Time.h
        src/core/vec2/Vector2d.cpp src/core/vec2/Vector2d.h
        src/core/vec3/Vector3d.cpp src/core/vec3/Vector3d.h
        src/core/Game.cpp src/core/Game.h
        src/core/Configuration.cpp src/core/Configuration.h
        src/core/GameObject.cpp src/core/GameObject.h
        src/core/Mouse.cpp src/core/Mouse.h
        src/core/Keyboard.cpp src/core/Keyboard.h
        src/game_components/GameComponent.h

        src/Program.cpp)

set(CLIENT
        src/rendering/RenderingEngine.cpp src/rendering/RenderingEngine.h
        src/rendering/Display.cpp src/rendering/Display.h

        src/rendering/opengl/OpenGLShader.cpp src/rendering/opengl/OpenGLShader.h
        src/rendering/opengl/OpenGLShaderResource.cpp src/rendering/opengl/OpenGLShaderResource.h

        src/rendering/opengl/OpenGLTexture.cpp src/rendering/opengl/OpenGLTexture.h
        src/rendering/opengl/OpenGLTextureResource.cpp src/rendering/opengl/OpenGLTextureResource.h

        src/user_interface/UiObject.cpp src/user_interface/UiObject.h
        src/user_interface/UiAnimator.cpp src/user_interface/UiAnimator.h

        src/user_interface/ui_modifier/ui_location/ILocation.h
        src/user_interface/ui_modifier/ui_scale/IScaler.h
        )

add_executable(${PROJECT_NAME} src/Program.cpp ${CORE} ${CLIENT} ${SCENE} )

add_library(glew STATIC IMPORTED)
set_target_properties(glew PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/glew/lib/Release/x64/glew32s.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/glew/include")
target_link_libraries(${PROJECT_NAME} glew)

find_package(OpenGL)
target_include_directories(${PROJECT_NAME} PUBLIC ${OpenGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} opengl32)

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

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/openvr/bin/openvr_api.dll" DESTINATION "${CMAKE_BUILD_RPATH}/")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/glew/bin/glew32.dll" DESTINATION "${CMAKE_BUILD_RPATH}/")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Resources" DESTINATION "${CMAKE_BUILD_RPATH}/")
