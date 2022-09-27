# avans-whether-station

## important details

- the client subfolder uses qmake to generate `client/makefile`, thus only
  `client/client.pro` should be tracked under version control, not
  `client/makefile`
- the stm32 makefile uses git submodules to pull necessary files for
  compilation. make sure to initialize and sync the git submodules, or re-clone
  using the `--recursive` flag.

## windows specific notes

[link to windows toolchain installation](scripts/readme.md#windows-install)

- if you're experiencing libusb-related issues while using st-link,
  try using [zadig](https://zadig.akeo.ie/) to update the usb driver.
- make sure to use the 64-bit version of msys2 (titled "MSYS2 MINGW64" in your
  start menu)
