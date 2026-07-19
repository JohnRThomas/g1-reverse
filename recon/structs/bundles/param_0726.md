### cluster param_0726  (param, 1 members, 2 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: k; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - k_msgq_cleanup @ 0x86480  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0726 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint8_t    field_0xc;   /* +0xc  sz=1 rw=rw types=byte */
    uint8_t    _pad_0xd[0x7];   /* +0xd pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
};
```