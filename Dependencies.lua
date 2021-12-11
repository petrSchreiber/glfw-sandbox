
-- Akai Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["Glew"] = "%{wks.location}/Akai/thirdparty/glew-2.2.0/include/GL"
IncludeDir["Glfw"] = "%{wks.location}/Akai/thirdparty/glfw-3.3.3.bin.WIN64/include"
IncludeDir["Spdlog"] = "%{wks.location}/Akai/thirdparty/glfw-3.3.3.bin.WIN64/include"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["Glew"] = "%{wks.location}/Akai/thirdparty/glew-2.2.0/lib/Release/x64"
LibraryDir["Glfw"] = "%{wks.location}/Akai/thirdparty/glfw-3.3.3.bin.WIN64/lib-vc2019/"

Library = {}

-- print()

Library["Glew"] = "glew32s.lib"
Library["Glfw"] = "glfw3.lib"
Library["Vulkan"] = "vulkan-1.lib"

Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"
