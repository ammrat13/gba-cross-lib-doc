# LibPlacement

This library exists to make it easier to place variables in certain sections of
memory. The linker script allows users to place symbols in IWRAM and EWRAM with
the `.iwram_{data,bss}*` and `.ewram_{data,bss}*` sections respectively. For
convinience, we define a header with macros to put variables in these sections.

The header `placement.h` defines the macros:
* `IDATA(var)`: Puts `var` in `.iwram_data.var`
* `IBSS(var)`: Puts `var` in `.iwram_bss.var`
* `EDATA(var)`: Puts `var` in `.ewram_data.var`
* `EBSS(var)`: Puts `var` in `.ewram_bss.var`

To use these macros, define a variable as shown below
```

```
