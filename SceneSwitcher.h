#pragma once

#define MYICON 1001
#define MYAUDIO 102

#ifndef RC_INVOKED

#include <windows.h>

/* avoid C++ std headers; stick to C headers */
#include <stdio.h>
#include <stdint.h>

#ifndef VK_USE_PLATFORM_WIN32_KHR
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#include <vulkan/vulkan.h>

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#ifndef GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#endif
#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

/* --------------------------------------------------------------------------
   Centralized key bindings for scene switching (WM_KEYDOWN / virtual-keys)
   Change these if you prefer different keys in the future.
   -------------------------------------------------------------------------- */
#ifndef SCENESWITCHER_KEY_SCENE0
#define SCENESWITCHER_KEY_SCENE0 VK_F1
#endif
#ifndef SCENESWITCHER_KEY_SCENE1
#define SCENESWITCHER_KEY_SCENE1 VK_F2
#endif
#ifndef SCENESWITCHER_KEY_SCENE2
#define SCENESWITCHER_KEY_SCENE2 VK_F3
#endif

#ifndef WIN_WIDTH
#define WIN_WIDTH 800
#endif

#ifndef WIN_HEIGHT
#define WIN_HEIGHT 600
#endif

struct Win32WindowContext_Switcher
{
    const char* gpszAppName = "ARTR";

    // Global variables
    HWND ghwnd = NULL;
    HDC ghdc = NULL;
    HGLRC ghrc = NULL;

    DWORD dwStyle = 0;
    WINDOWPLACEMENT wpPrev;

    int gbActiveWindow = 0;
    int gbFullscreen = 0;
    int gbWindowMinimized = FALSE;

    int giHeight = 0;
    int giWidth = 0;
};

struct GlobalContext_Switcher
{
    FILE* gpFile = NULL;

    // Vulkan related global variables
    // Instance Extension related variables
    uint32_t enabledInstanceExtensionCount = 0;
    // VK_KHR_SURFACE_EXTENSION_NAME
    // VK_KHR_WIN32_SURFACE_EXTENSION_NAME
    // VK_EXT_DEBUG_REPORT_EXTENSION_NAME
    const char* enabledInstanceExtensionNames_array[3];

    // Vulkan Instance
    VkInstance vkInstance = VK_NULL_HANDLE;

    // Vulkan Presentation Surface
    VkSurfaceKHR vkSurfaceKHR = VK_NULL_HANDLE;

    // Vulkan Physical Device related
    VkPhysicalDevice vkPhysicalDevice_selected = VK_NULL_HANDLE;
    uint32_t graphicsQueueFamilyIndex_selected = UINT32_MAX;
    VkPhysicalDeviceMemoryProperties vkPhysicalDeviceMemoryProperties;

    // Vulkan Printing VkInfo related
    VkPhysicalDevice* vkPhysicalDevice_array = NULL;
    uint32_t physicalDeviceCount = 0;

    // Device Extension related variables
    uint32_t enabledDeviceExtensionCount = 0;
    // VK_KHR_SWAPCHAIN_EXTENSION_NAME
    const char* enabledDeviceExtensionNames_array[1];

    // Vulkan Device
    VkDevice vkDevice = VK_NULL_HANDLE;

    // DeviceQueue
    VkQueue vkQueue = VK_NULL_HANDLE;

    // Color format and color Space
    VkFormat vkFormat_color = VK_FORMAT_UNDEFINED;
    VkColorSpaceKHR vkColorSpaceKHR = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

    // Presentation Mode
    VkPresentModeKHR vkPresentModeKHR = VK_PRESENT_MODE_FIFO_KHR;

    // Swapchain related
    int winWidth = WIN_WIDTH;
    int winHeight = WIN_HEIGHT;
    VkSwapchainKHR vkSwapchainKHR = VK_NULL_HANDLE;
    VkExtent2D vkExtent2D_swapchain;

    // for color images
    // SwapchainImage and swapchainImagesViews related
    uint32_t swapchainImageCount = UINT32_MAX;
    VkImage* swapchainImage_array = NULL;
    VkImageView* swapchainImageView_array = NULL;

    // for depth image
    VkFormat vkFormat_depth = VK_FORMAT_UNDEFINED;
    VkImage vkImage_depth = VK_NULL_HANDLE;
    VkDeviceMemory vkDeviceMemory_depth = VK_NULL_HANDLE;
    VkImageView vkImageView_depth = VK_NULL_HANDLE;

    // commandPool
    VkCommandPool vkCommandPool = VK_NULL_HANDLE;

    // Command Buffers per scene
    VkCommandBuffer* vkCommandBuffer_scene0_array = NULL;
    VkCommandBuffer* vkCommandBuffer_scene1_array = NULL;
    VkCommandBuffer* vkCommandBuffer_scene2_array = NULL;

    // RenderPass
    VkRenderPass vkRenderPass = VK_NULL_HANDLE;

    // FrameBuffers
    VkFramebuffer* vkFrameBuffer_array = NULL;

    // semaphore
    VkSemaphore vkSemaphore_backBuffer = VK_NULL_HANDLE;
    VkSemaphore vkSemaphore_renderComplete = VK_NULL_HANDLE;

    // Fence
    VkFence* vkFence_array = NULL;

    // BuildCommandBuffers
    // clear color values
    VkClearColorValue vkClearColorValue;  // 3 arrays
    VkClearDepthStencilValue vkClearDepthStencilValue;  // for depth

    // Render
    VkBool32 bInitialized = FALSE;
    uint32_t currentImageIndex = UINT32_MAX;

    // Validation
    BOOL bValidation = TRUE;
    uint32_t enabledValidationLayerCount = 0;
    const char* enabledValidationLayerNames_array[1]; // for VK_LAYER_KHRONOS_validation
    VkDebugReportCallbackEXT vkDebugReportCallbackEXT = VK_NULL_HANDLE;
    PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT_fnptr = NULL;

    // VertexBuffer related variables
    struct VertexData
    {
        VkBuffer vkBuffer = VK_NULL_HANDLE;
        VkDeviceMemory vkDeviceMemory = VK_NULL_HANDLE;
    };

    // position
    VertexData vertexData_position;
    VertexData vertexData_texcoord;

    // Uniform related declarations
    struct MyUniformData
    {
        glm::mat4 modelMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        /* Scene 0: fade.x.
           Scene 1: fade = (fadeAmt, screenWidth, screenHeight, overlaySizeFrac).
           Scene 2: reserved (set to zero). */
        glm::vec4 fade;
    };

    struct UniformData
    {
        VkBuffer vkBuffer = VK_NULL_HANDLE;
        VkDeviceMemory vkDeviceMemory = VK_NULL_HANDLE;
    };

    UniformData uniformData_scene0;
    UniformData uniformData_scene1;
    UniformData uniformData_scene2;

    // Shader related variables
    VkShaderModule vkShaderModule_vertex_shader = VK_NULL_HANDLE;
    VkShaderModule vkShaderModule_fragment_shader = VK_NULL_HANDLE;

    // DescriptorSetLayout related variables
    VkDescriptorSetLayout vkDescriptorSetLayout = VK_NULL_HANDLE;

    // PipelineLayout related variables
    VkPipelineLayout vkPipelineLayout = VK_NULL_HANDLE;

    // Descriptor pool
    VkDescriptorPool vkDescriptorPool = VK_NULL_HANDLE;

    // Descriptor set
    VkDescriptorSet vkDescriptorSet_scene0 = VK_NULL_HANDLE;
    VkDescriptorSet vkDescriptorSet_scene1 = VK_NULL_HANDLE;
    VkDescriptorSet vkDescriptorSet_scene2 = VK_NULL_HANDLE;

    // Pipeline
    VkViewport vkViewport;
    VkRect2D vkRect2D_scissor; // mostly viewport and scissor dimensions are same
    VkPipeline vkPipeline_scene0 = VK_NULL_HANDLE;
    VkPipeline vkPipeline_scene1 = VK_NULL_HANDLE;
    VkPipeline vkPipeline_scene2 = VK_NULL_HANDLE;
    VkPipelineCache vkPipelineCache = VK_NULL_HANDLE;

    float angle = 0.0f;

    // Texture related global data
    VkImage vkImage_texture = VK_NULL_HANDLE;
    VkDeviceMemory vkDeviceMemory_texture = VK_NULL_HANDLE;
    VkImageView vkImageView_texture = VK_NULL_HANDLE;
    VkSampler vkSampler_texture = VK_NULL_HANDLE;

    // Texture related global data for Scene 2
    VkImage vkImage_texture_scene2 = VK_NULL_HANDLE;
    VkDeviceMemory vkDeviceMemory_texture_scene2 = VK_NULL_HANDLE;
    VkImageView vkImageView_texture_scene2 = VK_NULL_HANDLE;
    VkSampler vkSampler_texture_scene2 = VK_NULL_HANDLE;

    // Global
    float gFade = 0.0f;
};

#endif // RC_INVOKED

extern Win32WindowContext_Switcher gWin32WindowCtx_Switcher;
extern GlobalContext_Switcher gCtx_Switcher;

struct Win32FunctionTable_Switcher
{
    LRESULT (CALLBACK* WndProc)(HWND, UINT, WPARAM, LPARAM) = nullptr;
    void (*Update)(void) = nullptr;
    VkResult (*Initialize)(void) = nullptr;
    VkResult (*Resize)(int, int) = nullptr;
    VkResult (*Display)(void) = nullptr;
    void (*Uninitialize)(void) = nullptr;
    void (*ToggleFullscreen)(void) = nullptr;
};

extern Win32FunctionTable_Switcher gWin32FunctionTable_Switcher;

struct FunctionTable_Switcher
{
    VkResult (*createVulkanInstance)(void) = nullptr;
    VkResult (*fillInstanceExtensionNames)(void) = nullptr;
    VkResult (*fillValidationLayerNames)(void) = nullptr;
    VkResult (*createValidationCallbackFunction)(void) = nullptr;
    VkResult (*getSupportedSurface)(void) = nullptr;
    VkResult (*getPhysicalDevice)(void) = nullptr;
    VkResult (*printVkInfo)(void) = nullptr;
    VkResult (*fillDeviceExtensionNames)(void) = nullptr;
    VkResult (*createVulkanDevice)(void) = nullptr;
    void (*getDeviceQueue)(void) = nullptr;
    VkResult (*getPhysicalDeviceSurfaceFormatAndColorSpace)(void) = nullptr;
    VkResult (*getPhysicalDevicePresentMode)(void) = nullptr;
    VkResult (*createSwapchain)(VkBool32) = nullptr;
    VkBool32 (*HasStencilComponent)(VkFormat) = nullptr;
    VkResult (*createImagesAndImageViews)(void) = nullptr;
    VkResult (*GetSupportedDepthFormat)(void) = nullptr;
    VkResult (*createCommandPool)(void) = nullptr;
    VkResult (*createCommandBuffers)(void) = nullptr;
    VkResult (*createVertexBuffer)(void) = nullptr;
    VkResult (*createTexture)(const char*) = nullptr;
    VkResult (*createUniformBuffer)(void) = nullptr;
    VkResult (*updateUniformBuffer)(void) = nullptr;
    VkResult (*createShaders)(void) = nullptr;
    VkResult (*createDescriptorSetLayout)(void) = nullptr;
    VkResult (*createPipelineLayout)(void) = nullptr;
    VkResult (*createDescriptorPool)(void) = nullptr;
    VkResult (*createDescriptorSet)(void) = nullptr;
    VkResult (*createRenderPass)(void) = nullptr;
    VkResult (*createPipeline)(void) = nullptr;
    VkResult (*createFrameBuffers)(void) = nullptr;
    VkResult (*createSemaphores)(void) = nullptr;
    VkResult (*createFences)(void) = nullptr;
    VkResult (*buildCommandBuffers)(void) = nullptr;
    VKAPI_ATTR VkBool32 (VKAPI_CALL* debugReportCallback)(VkDebugReportFlagsEXT,
                                                          VkDebugReportObjectTypeEXT,
                                                          uint64_t,
                                                          size_t,
                                                          int32_t,
                                                          const char*,
                                                          const char*,
                                                          void*) = nullptr;
};

extern FunctionTable_Switcher gFunctionTable_Switcher;

void InitializeFunctionTable(void);

