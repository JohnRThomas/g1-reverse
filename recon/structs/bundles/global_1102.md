### cluster global_1102  (global, 1 members, 2 fields, size>=0x2c)

Global object at fixed address 0x0005052c.

library hint: likely G1-original

members (1 shown of 1):
  - arm_mem_manage_fault_helper @ 0x503d8  as 0x0005052c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1102 {
    uint8_t    _pad_0x0[0x24];   /* +0x0 pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=rw types=uint */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=int */
};
```