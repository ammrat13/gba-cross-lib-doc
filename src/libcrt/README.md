# LibCRT

This library is the C runtime for the GBA. It defines the initialization
routines used, and provides a header with all of them.


## CRT0

The `crt0.s` file contains the code to be executed on startup. The code is
placed in the `.text.bootstrap` section and should be loaded at the very start
of the cartridge ROM since it has the cartridge header. It will:
* Switch to THUMB mode
* Call `_init()`
* Call `main()`
* Spinlock if `main` ever terminates

Note that `crt0.s` does not set any stack pointers. They are set by the GBA
BIOS. As a result, it is not possible to reset a program simply by calling
`_start()`.


## CRTI

The file `crti.c` defines a function `_init` that:
* Copies the `.data` section from ROM to RAM
* Zeroes out the `.bss` section
* Calls all the constructors in `.init_array`

It expects some symbols from the linker script. For `.data`:
* `__data_vma_stt`: The desired starting address of the section in *RAM*
* `__data_vma_end`: The desired address just past the end of the section in
  *RAM*
* `__data_lma`: The address of the `.data` section in *ROM*

For `.bss`:
* `__bss_vma_stt`: Its desired starting address in *RAM*
* `__bss_vma_end`: Its desired address just past the end in *RAM*

For `.init_array`:
* `__init_arr_stt`: The address of the first element
* `__init_arr_end`: The address just past the end
