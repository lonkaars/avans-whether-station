#!/bin/sh
pacman --noconfirm --needed -Sy \
    make git \
    arm-none-eabi-gcc \
    arm-none-eabi-gdb \
    arm-none-eabi-newlib \
    arm-none-eabi-binutils \
    stlink \
    python python-pip

pip3 install compiledb
