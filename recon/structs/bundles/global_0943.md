### cluster global_0943  (global, 1 members, 3 fields, size>=0x10)

Global object at fixed address 0x0003074c.

library hint: likely G1-original

members (1 shown of 1):
  - commit_default_config_record @ 0x30710  as 0x0003074c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0943 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```