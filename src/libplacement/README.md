# LibPlacement

This library exists to make it easier to place variables in certain sections of
memory. The linker script allows users to place symbols in IWRAM and EWRAM with
the `.iwram_{data,bss}*` and `.ewram_{data,bss}*` sections respectively. For
convinience, we define a header with macros to put variables in these sections.

The header defines the following macros for placement:
* `IDATA`: Places an initialized variable in IWRAM
* `IZERO`: Places a zero-initialized or an uninitialized variable in IWRAM
* `EDATA`: Same as `IDATA` but for EWRAM
* `EZERO`: Same as `IZERO` but for EWRAM

To use these macros, simply place them as type attributes, for example:
```
EZERO int x[10];
```

## Additional Considerations

Each variable is given a unique identifier for use with `-fdata-sections`. This
is achieved through the `SECTION_ID` macro, which in turn uses the `__FILE__`,
`__LINE__`, and (most importantly) `__COUNTER__` macros.

For this reason, it's best to include the placement macros only with definitions
and not with declarations. Otherwise, the same symbol will be given two
different `SECTION_ID`s.

This header also relies on some macro to convert raw text to a string literal.
It needs this as a runtime dependency, but it can be installed without it.
