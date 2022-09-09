# avans-whether-station

## important details

- the client subfolder uses qmake to generate `client/makefile`, thus only
  `client/client.pro` should be tracked under version control, not
  `client/makefile`
- the stm32 makefile uses git submodules to pull necessary files for
  compilation. make sure to initialize and sync the git submodules, or re-clone
  using the `--recursive` flag.

