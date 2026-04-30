#pragma once

#include<vulkan/vulkan.h>

typedef struct vulkan_context {
    VkInstance instatnce;
    VkAllocationCallbacks* allocator;
}vulkan_context;