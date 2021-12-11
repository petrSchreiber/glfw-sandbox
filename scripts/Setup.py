import os

# Make sure everything we need for the setup is installed
from SetupPython import PythonConfiguration as PythonRequirements
PythonRequirements.Validate()

from SetupPremake import PremakeConfiguration as PremakeRequirements
from SetupVulkan import VulkanConfiguration as VulkanRequirements

os.chdir('./../')  # Change from devtools/scripts directory to root
VulkanRequirements.Validate()
PremakeRequirements.Validate()

print("\nSetup completed!")
