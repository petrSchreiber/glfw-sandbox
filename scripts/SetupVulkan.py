import os
from pathlib import Path
import Utils


class VulkanConfiguration:
    requiredVulkanVersion = "1.2.198.1"
    installer = 'VulkanSDK-1.2.198.1-Installer.exe'
    vulkanDirectory = r"./VulkanSDK/"

    @classmethod
    def Validate(cls):
        if not cls.CheckVulkanSDK():
            print("Vulkan SDK not installed.")
            return

    @classmethod
    def CheckVulkanSDK(cls):
        vulkanSDK = os.environ.get("VULKAN_SDK")
        if vulkanSDK is None:
            print("\nYou don't have the Vulkan SDK installed!")
            cls.__InstallVulkanSDK()
            return False
        else:
            print(f"\nLocated Vulkan SDK at {vulkanSDK}")

        if cls.requiredVulkanVersion not in vulkanSDK:
            print(f"You don't have the correct Vulkan SDK version! (Engine requires {cls.requiredVulkanVersion})")
            cls.__InstallVulkanSDK()
            return False

        print(f"Correct VulkanSDK installed successfully")

        # Cleanup to save some space
        if os.path.exists(f'VulkanSDK/VulkanSDK-1.2.198.1-Installer.exe'):
            print(f'Removing {cls.installer}')
            os.remove(f'VulkanSDK/{cls.installer}')
        if os.path.exists('VulkanSDK'):
            os.rmdir('VulkanSDK')

        return True

    @classmethod
    def __InstallVulkanSDK(cls):

        reply = str(input(f"Would you like to install VulkanSDK v{cls.requiredVulkanVersion}? [Y/N]: "))
        if reply.lower() == 'y':
            vulkanInstallURL = f"https://sdk.lunarg.com/sdk/download/{cls.requiredVulkanVersion}/windows/VulkanSDK-{cls.requiredVulkanVersion}-Installer.exe"
            vulkanPath = f"{cls.vulkanDirectory}/VulkanSDK-{cls.requiredVulkanVersion}-Installer.exe"
            print(f"Downloading {vulkanInstallURL} to {vulkanPath}")
            Utils.DownloadFile(vulkanInstallURL, vulkanPath)
            print("Running Vulkan SDK installer...")
            os.startfile(os.path.abspath(vulkanPath))
            print("Re-run this script after installation!")
            quit()
        else:
            print('Akai Engine requires VulkanSDK')

    @classmethod
    def CheckVulkanSDKDebugLibs(cls):
        shadercdLib = Path(f"{cls.vulkanDirectory}/Lib/shaderc_sharedd.lib")

        VulkanSDKDebugLibsURLlist = [
            f"https://sdk.lunarg.com/sdk/download/{cls.requiredVulkanVersion}/windows/VulkanSDK-{cls.requiredVulkanVersion}-DebugLibs.zip",
            f"https://files.lunarg.com/SDK-{cls.requiredVulkanVersion}/VulkanSDK-{cls.requiredVulkanVersion}-DebugLibs.zip"
        ]

        if not shadercdLib.exists():
            print(f"\nNo Vulkan SDK debug libs found. (Checked {shadercdLib})")
            vulkanPath = f"{cls.vulkanDirectory}/VulkanSDK-{cls.requiredVulkanVersion}-DebugLibs.zip"
            Utils.DownloadFile(VulkanSDKDebugLibsURLlist, vulkanPath)
            print("Extracting", vulkanPath)
            Utils.UnzipFile(vulkanPath, deleteZipFile=False)
            print(f"Vulkan SDK debug libs installed at {os.path.abspath(cls.vulkanDirectory)}")
        else:
            print(f"\nVulkan SDK debug libs located at {os.path.abspath(cls.vulkanDirectory)}")
        return True


if __name__ == "__main__":
    VulkanConfiguration.Validate()
