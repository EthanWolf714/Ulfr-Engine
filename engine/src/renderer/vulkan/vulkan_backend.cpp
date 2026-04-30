
#include "vulkan_backend.h"

b8 vulkan_backend::initialize(const char* application_name, struct platform_state* plat_state)
{
    context.allocator = 0;

    //setup vulkan instance
    VkApplicationInfo appInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
    appInfo.pApplicationName = application_name;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
    appInfo.apiVersion = VK_API_VERSION_1_0;


    //tell vulkan driver what extentions to use for creating the instance
    VkInstanceCreateInfo create_info = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
    create_info.pApplicationInfo = &appInfo;
    create_info.enabledExtensionCount = 0;
    create_info.ppEnabledExtensionNames = 0;
    create_info.enabledLayerCount = 0;
    create_info.ppEnabledLayerNames = 0;
    //TODO: add extentions later

    VkResult result = vkCreateInstance(&create_info,context.allocator, &context.instatnce);

    if(result != VK_SUCCESS){
        FERROR("vKCreateInstance failed with result: %u", result);

        
    }

    FINFO("Vulkan renderer initialized successfully!");
    return TRUE;
    
}

void vulkan_backend::shutdown()
{
    
}

void vulkan_backend::resize(u16 width, u16 height)
{
    
}

b8 vulkan_backend::begin_frame(f32 delta_time)
{
    return TRUE;
}

b8 vulkan_backend::end_frame(f32 delta_time)
{
    return TRUE;
}
void vulkan_backend::set_frame_num(u64 num)
{
    frame_number = num;
}

u64 vulkan_backend::get_frame_num()
{
    return frame_number;
}
