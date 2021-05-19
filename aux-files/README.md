# Auxilary Files

These files exist to provide defaults for compiling and linking. Right now,
there is a GCC specs file and a linker script.


## Specs

The specs provides sensible default options for cross compiling to the GBA. In
particular it:
* Includes the headers, start files, and libraries required to cross compile
* Compiles for the GBA's `-mcpu=arm7tdmi`
* Turns on `-ffreestanding`
* Turns on `-mthumb-interwork`
* Errors out on orphaned sections during linking
* Disables C++ exceptions and run-time type information


## Linker Script

The linker script allows GBA games to be linked and mapped to ROM. It will place
`crt0.o`'s `.text.bootstrap` section first. Then it will place all the other
code sections, any interworking code, the initialization and finalization
arrays, and any variables.

It also provides some symbols for the program loader. The `_stt` symbols mark
the first address in a section, while the `_end` symbols mark the address *just
past* the end of a section - computed as `start + size`. The script also gives
symbols for the end of all the sections of memory. A full list of symbols
defined is:
* `__text_bootstrap_stt`
* `__text_bootstrap_end`
* `__text_stt`
* `__text_end`
* `__rodata_stt`
* `__rodata_end`
* `__init_arr_stt`
* `__init_arr_end`
* `__fini_arr_stt`
* `__fini_arr_end`
* `__data_vma_stt`
* `__data_vma_end`
* `__data_lma`
* `__data_lma_end`
* `__bss_vma_stt`
* `__bss_vma_end`
* `__iwram_noinit_vma_stt`
* `__iwram_noinit_vma_end`
* `__iwram_end`
* `__crom_end`
