@echo off
cd ..
tools\embed.exe shaders -o include\Mountain\binary_resources
tools\embed.exe assets -o include\Mountain\binary_resources
