### cluster param_0412  (param, 1 members, 4 fields, size>=0x12)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - add_thread_to_wait_queue @ 0x73ec0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0412 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x1];   /* +0xc pad */
    uint8_t    field_0xd;   /* +0xd  sz=1 rw=rw types=byte */
    uint8_t    field_0xe;   /* +0xe  sz=1 rw=r types=char */
    uint8_t    _pad_0xf[0x3];   /* +0xf pad */
};
```