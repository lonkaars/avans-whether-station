#!/bin/sh

echo "this installation script is untested, press Ctrl+C to exit, or wait 5 seconds to continue..."
sleep 5

# TODO: missing arm-none-eabi-newlib (manual install?)

brew install --cask \
    make git \
    gcc-arm-embedded \
    stlink

