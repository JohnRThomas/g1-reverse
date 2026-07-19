### cluster param_0461  (param, 5 members, 11 fields, size>=0x70)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (5 shown of 5):
  - opt_field1_set @ 0x7c430  as param_1  [APPLICATION]
  - opt_field2_set @ 0x7c456  as param_1  [APPLICATION]
  - opt_field3_set @ 0x7c48a  as param_1  [APPLICATION]
  - opt_record_init @ 0x7c4b6  as param_1  [APPLICATION]
  - opt_record_decode @ 0x7c4f4  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0461 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=rw types=idx4,int,uint */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=idx4,int,uint */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=w types=int,uint */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=idx4,int,uint */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=rw types=idx4,undefined4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=rw types=idx4,undefined4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x20[0x40];   /* +0x20 pad */
    uint32_t   field_0x60;   /* +0x60  sz=4 rw=r types=idx4 */
    uint32_t   field_0x64;   /* +0x64  sz=4 rw=r types=idx4 */
    uint32_t   field_0x68;   /* +0x68  sz=4 rw=r types=idx4 */
    uint32_t   field_0x6c;   /* +0x6c  sz=4 rw=r types=idx4 */
};
```