#
# Chapter 3 - Device Hand Shake CMake file.
#

cmake_minimum_required(VERSION 3.20.1)

set(Recipe_Name "3_0_DeviceHandshake")

message(STATUS "Attempting auto locate Vulkan using CMake......")

# Find Vulkan Path using CMake's Vulkan Module
# This will return Boolean 'Vulkan_FOUND' indicating the status of find as success(ON) or fail(OFF).
# Include directory path - 'Vulkan_INCLUDE_DIRS' and 'Vulkan_LIBRARY' with required libraries.
get_property(importTargets DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
find_package(Vulkan)
get_property(importTargetsAfter DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
list(REMOVE_ITEM importTargetsAfter ${importTargets})
message("${importTargetsAfter}")

# Specify a suitable project name
project(${Recipe_Name})

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

# Define include path
target_include_directories(${Recipe_Name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link the debug and release libraries to the project
target_link_libraries( ${Recipe_Name} Vulkan::Vulkan)

if(WIN32)
	# vulkan-1 library for build Vulkan application.
	target_link_libraries( ${Recipe_Name} "vulkan-1")
endif(WIN32)

# Define project properties
set_property(TARGET ${Recipe_Name} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${Recipe_Name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${Recipe_Name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${Recipe_Name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${Recipe_Name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/binaries)

# Define C++ version to be used for building the project
set_property(TARGET ${Recipe_Name} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${Recipe_Name} PROPERTY CXX_STANDARD_REQUIRED ON)

# Define C version to be used for building the project
set_property(TARGET ${Recipe_Name} PROPERTY C_STANDARD 99)
set_property(TARGET ${Recipe_Name} PROPERTY C_STANDARD_REQUIRED ON)
