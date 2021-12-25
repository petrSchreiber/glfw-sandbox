import os
import platform
import subprocess
from pathlib import Path

import Utils


class PremakeConfiguration:
    premakeVersion = "5.0.0-alpha16"
    premakeZipUrls = f"https://github.com/premake/premake-core/releases/download/v{premakeVersion}/premake-{premakeVersion}-windows.zip"
    premakeLicenseUrl = "https://raw.githubusercontent.com/premake/premake-core/master/LICENSE.txt"
    premakeDirectory = "./premake/bin"

    @classmethod
    def Validate(cls):
        if not cls.CheckIfPremakeInstalled():
            print("Premake is not installed.")
            print("Akai requires Premake to generate project files.")
            return False

        print(f"Correct Premake located at {os.path.abspath(cls.premakeDirectory)}")
        cls.GenerateProjectFiles()
        return True

    @classmethod
    def CheckIfPremakeInstalled(cls):
        premakeExe = Path(f"{cls.premakeDirectory}/premake5.exe")
        if not premakeExe.exists():
            return cls.InstallPremake()

        return True

    @classmethod
    def InstallPremake(cls):
        permissionGranted = False
        while not permissionGranted:
            reply = str(input(f"Premake not found. Would you like to download Premake {cls.premakeVersion}? [Y/N]: "))

            if reply.lower() == 'y':
                premakePath = f"{cls.premakeDirectory}/premake-{cls.premakeVersion}-windows.zip"
                print(f"Downloading {cls.premakeZipUrls} to {premakePath}")
                Utils.DownloadFile(cls.premakeZipUrls, premakePath)
                print("Extracting", premakePath)
                Utils.UnzipFile(premakePath, deleteZipFile=True)
                print(f"Premake {cls.premakeVersion} has been downloaded to '{cls.premakeDirectory}'")

                premakeLicensePath = f"{cls.premakeDirectory}/LICENSE.txt"
                print(f"Downloading {cls.premakeLicenseUrl} to {premakeLicensePath}")
                Utils.DownloadFile(cls.premakeLicenseUrl, premakeLicensePath)
                print(f"Premake License file has been downloaded to '{cls.premakeDirectory}'")
                return True
            else:
                return False

    @classmethod
    def GenerateProjectFiles(cls):
        if platform.system() == "Windows":
            print("\nRunning premake...")
            print(os.path.abspath("./scripts/Win-GenProjects.bat"))
            subprocess.call([os.path.abspath("./scripts/Win-GenProjects.bat"), "nopause"])

        print("Happy Coding :)")




