@echo off
cd ..
::rmdir /S /Q include\Mountain\binary_resources\embedded_resources
tools\embed.exe shaders -o include\Mountain\binary_resources
