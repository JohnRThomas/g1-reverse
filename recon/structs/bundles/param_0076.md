### cluster param_0076  (param, 3 members, 14 fields, size>=0x1b8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (3 shown of 3):
  - master_process_audio_fw_load_req @ 0x2af4c  as param_2  [APPLICATION]
  - post_notification_cmd_response @ 0x340c4  as param_4  [APPLICATION]
  - post_notification_cmd_response @ 0x340c4  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0076 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=byte,char */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=r types=ushort */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4,uint,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=int */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x30[0x184];   /* +0x30 pad */
    uint32_t   field_0x1b4;   /* +0x1b4  sz=4 rw=r types=uint */
};
```