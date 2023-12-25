#
# Chapter 6 - SwapChain
#

cmake_minimum_required(VERSION 3.25.1)
set(Recipe_Name "6_0_SwapChain")
project(${Recipe_Name} C CXX)

get_property(importTargets DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
	find_package(Vulkan)
	set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/lib/x86_64-linux-gnu/)
	set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include/)

	find_package(X11 REQUIRED)
	get_property(importTargetsAfter DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
list(REMOVE_ITEM importTargetsAfter ${importTargets})
message("${importTargetsAfter}")

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

if(linux)
	target_link_libraries( ${Recipe_Name} X11::xcb)
endif(linux)

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
