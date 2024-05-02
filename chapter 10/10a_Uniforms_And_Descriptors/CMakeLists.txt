#
# Chapter 10 - Uniforms And Descriptors.
#

cmake_minimum_required(VERSION 3.25.1)

set(Recipe_Name "10a_Uniforms_And_Descriptors")

project(${Recipe_Name} C CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(Vulkan COMPONENTS glslang SPIRV-Tools glslangValidator)

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/lib/x86_64-linux-gnu/)
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include/)
find_package(X11 REQUIRED)

# BUILD_SPV_ON_COMPILE_TIME - accepted value ON or OFF, default value OFF.
# ON  - Reads the GLSL shader file and auto convert in SPIR-V form (.spv). 
# 			This requires additional libraries support from 
#			VulkanSDK like SPIRV glslang OGLCompiler OSDependent HLSL
# OFF - Only reads .spv files, which need to be compiled offline 
#			using glslangValidator.exe.
# For example: glslangValidator.exe <GLSL file name> -V -o <output filename in SPIR-V(.spv) form>
option(BUILD_SPV_ON_COMPILE_TIME "BUILD_SPV_ON_COMPILE_TIME" ON)
# Define directories and the contained folder and files inside.

if(WIN32)
# Add any required preprocessor definitions here
	add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)
    source_group("include" REGULAR_EXPRESSION "include/*")
    source_group("source" REGULAR_EXPRESSION "source/*")
endif(WIN32)

# Gather list of header and source files for compilation
file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

# Build project, give it a name and includes list of file to be compiled
add_executable(${Recipe_Name} ${CPP_FILES})
set_target_properties(${Recipe_Name} PROPERTIES LINK_FLAGS "/ignore:4099")

# Define include path
target_include_directories(${Recipe_Name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# Link the debug and release libraries to the project
target_link_libraries(${Recipe_Name} PRIVATE  Vulkan::Vulkan)

if(linux)
	target_link_libraries( ${Recipe_Name} PRIVATE  X11::xcb)
endif()
message($ENV{VULKAN_SDK})

set(_Vulkan_hint_library_search_paths "$ENV{VULKAN_SDK}/Lib" "$ENV{VULKAN_SDK}/Bin")

find_library(Vulkan_SPIRV_Tools_opt_LIBRARY
NAMES SPIRV-Tools-opt
HINTS
  ${_Vulkan_hint_library_search_paths}
)

find_library(Vulkan_SPIRV_Tools_opt_DEBUG_LIBRARY
NAMES SPIRV-Tools-optd
HINTS
  ${_Vulkan_hint_library_search_paths}
)

message(Vulkan_SPIRV_Tools_opt_LIBRARY ${Vulkan_SPIRV_Tools_opt_LIBRARY})

add_library(Vulkan::SPIRV-Tools-opt STATIC IMPORTED)
set_property(TARGET Vulkan::SPIRV-Tools-opt APPEND
  PROPERTY
	IMPORTED_CONFIGURATIONS Release)
set_property(TARGET Vulkan::SPIRV-Tools-opt APPEND
  PROPERTY
	IMPORTED_LOCATION_RELEASE "${Vulkan_SPIRV_Tools_opt_LIBRARY}")
set_property(TARGET Vulkan::SPIRV-Tools-opt APPEND
PROPERTY
	IMPORTED_CONFIGURATIONS Debug)
set_property(TARGET Vulkan::SPIRV-Tools-opt
PROPERTY
	IMPORTED_LOCATION_DEBUG "${Vulkan_SPIRV_Tools_opt_DEBUG_LIBRARY}")

if(BUILD_SPV_ON_COMPILE_TIME)
	
	# Preprocessor  flag allows the solution to use glslang library functions
	add_definitions(-DAUTO_COMPILE_GLSL_TO_SPV)

	target_link_libraries( ${Recipe_Name} PRIVATE 
		Vulkan::Headers
		Vulkan::glslang-oglcompiler  
		Vulkan::glslang-osdependent
		Vulkan::glslang
		Vulkan::glslang-spirv
		Vulkan::SPIRV-Tools 
		Vulkan::SPIRV-Tools-opt
	)
endif()

# Define project properties
set_property(TARGET ${Recipe_Name} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${Recipe_Name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${Recipe_Name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${Recipe_Name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${Recipe_Name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/binaries)