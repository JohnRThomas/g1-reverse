## review group global_1450  (1 cluster(s), kinds=global)

### proposal for global_1450
struct_name: cc_hal_interrupt_regs | is_library: True | library_name: CryptoCell (CC3XX) HAL internal state / register block | is_array: False | confidence: low
purpose: Large hardware register/state block accessed by CC_HalClearInterruptBit (Arm CryptoCell HAL) at fixed writes 0x108 and 0xa08.
fields:
  0x108  uint32_t     field_0x108  write-only, likely interrupt-clear register mirror
  0xa08  int32_t      field_0xa08  write-only status/flag

<ground-truth bundle for global_1450>
### cluster global_1450  (global, 1 members, 2 fields, size>=0xa0c)

Global object at fixed address 0x0007a2a8.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - CC_HalClearInterruptBit @ 0x7a290  as 0x0007a2a8  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1450 {
    uint8_t    _pad_0x0[0x108];   /* +0x0 pad */
    uint32_t   field_0x108;   /* +0x108  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x10c[0x8fc];   /* +0x10c pad */
    uint32_t   field_0xa08;   /* +0xa08  sz=4 rw=w types=int */
};
```
