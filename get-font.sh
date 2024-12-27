#!/bin/bash

# Create resources directory if it doesn't exist
mkdir -p resources

# Download Inter font directly from GitHub
echo "Downloading Inter font..."
curl -L "https://github.com/rsms/inter/releases/download/v3.19/Inter-3.19.zip" -o inter.zip

# List contents to debug
unzip -l inter.zip | grep -i "regular.ttf"

# Unzip and move the regular TTF file
unzip -j inter.zip "*Regular.ttf" -d resources/
mv resources/*Regular.ttf resources/font.ttf

# Clean up
rm inter.zip

echo "Font downloaded and installed to resources/font.ttf" 