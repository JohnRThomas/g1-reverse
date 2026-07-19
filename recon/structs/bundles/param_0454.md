### cluster param_0454  (param, 1 members, 11 fields, size>=0x44)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - LoadAesKey @ 0x7b530  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0454 {
    uint8_t    _pad_0x0[0x10];   /* +0x0 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=int,undefined4 */
    uint8_t    _pad_0x34[0x8];   /* +0x34 pad */
    uint8_t    field_0x3c;   /* +0x3c  sz=1 rw=r types=char */
    uint8_t    _pad_0x3d[0x3];   /* +0x3d pad */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=r types=undefined4 */
};
```