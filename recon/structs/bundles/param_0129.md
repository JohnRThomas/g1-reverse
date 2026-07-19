### cluster param_0129  (param, 4 members, 8 fields, size>=0x22)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (4 shown of 4):
  - onoff_process_event @ 0x4b4fc  as param_1  [APPLICATION]
  - onoff_request_enqueue @ 0x4b908  as param_1  [APPLICATION]
  - onoff_release @ 0x4ba38  as param_1  [APPLICATION]
  - process_recheck @ 0x7e18e  as param_1  [APPLICATION]

layout notes: overlap at 0x7 (prev field ends 0x8)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0129 {
    void *     field_0x0;   /* +0x0  sz=4 rw=r types=ptr,undefined4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x4];   /* +0xc pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x14[0x4];   /* +0x14 pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint16_t   field_0x1c;   /* +0x1c  sz=2 rw=r types=ushort */
    uint16_t   field_0x1e;   /* +0x1e  sz=2 rw=rw types=short */
    uint8_t    _pad_0x20[0x2];   /* +0x20 pad */
};
```