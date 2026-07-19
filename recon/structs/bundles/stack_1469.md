### cluster stack_1469  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_1c in mbedtls_hardware_poll (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: mbedtls; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - mbedtls_hardware_poll @ 0x7a9fc  as local_1c  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1469 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```