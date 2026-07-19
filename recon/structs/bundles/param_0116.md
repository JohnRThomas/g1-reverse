### cluster param_0116  (param, 1 members, 2 fields, size>=0x378)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - panel_off @ 0x46d2c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0116 {
    uint8_t    _pad_0x0[0x35c];   /* +0x0 pad */
    uint32_t   field_0x35c;   /* +0x35c  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x360[0x14];   /* +0x360 pad */
    uint32_t   field_0x374;   /* +0x374  sz=4 rw=rw types=int,undefined4 */
};
```