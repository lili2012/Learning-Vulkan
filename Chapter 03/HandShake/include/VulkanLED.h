/*
* Learning Vulkan - ISBN: 9781786469809
*
* Author: Parminder Singh, parminder.vulkan@gmail.com
* Linkedin: https://www.linkedin.com/in/parmindersingh18
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include "Headers.h"

/*
* This structure stores the extensions of a given layer.
* A layer can have one or more extensions.
* Use this structure keep track of those extensions here.
*/
struct LayerProperties{
	VkLayerProperties properties;
	std::vector<VkExtensionProperties> extensions;
};

class VulkanLayerAndExtension{
public:
	VulkanLayerAndExtension();
	~VulkanLayerAndExtension();

	/******* LAYER AND EXTENSION MEMBER FUNCTION AND VARAIBLES *******/
	
	// List of layer names requested by the application.
	std::vector<const char *>			appRequestedLayerNames;
	
	// List of extension names requested by the application.
	std::vector<const char *>			appRequestedExtensionNames;
	
	// Layers and corresponding extension list
	std::vector<LayerProperties>		layerPropertyList;

	// Instance/global layer
	VkResult getInstanceLayerProperties();
	
	// Global extensions
	VkResult getExtensionProperties(LayerProperties &layerProps, VkPhysicalDevice* gpu = NULL);

	// Device based extensions
	VkResult getDeviceExtensionProperties(VkPhysicalDevice* gpu);
};