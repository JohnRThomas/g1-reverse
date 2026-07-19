### cluster param_0039  (param, 5 members, 19 fields, size>=0x40)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (5 shown of 5):
  - audio_fw_load_get_wrapper @ 0x19b54  as param_2  [APPLICATION]
  - master_process_audio_fw_load_req @ 0x2af4c  as param_3  [APPLICATION]
  - uart_callback @ 0x33384  as param_3  [APPLICATION]
  - post_notification_cmd_response @ 0x340c4  as param_6  [APPLICATION]
  - uint32_to_little_endian @ 0x4a568  as param_1  [APPLICATION]

layout notes: 0x0: access width 4 exceeds gap 1 to next field (overlap/union); 0x4: access width 4 exceeds gap 2 to next field (overlap/union); 0x6: access width 4 exceeds gap 2 to next field (overlap/union); 0x8: access width 4 exceeds gap 2 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0039 {
    uint8_t    field_0x0;   /* +0x0  sz=4 rw=w types=undefined4 */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x2[0x2];   /* +0x2 pad */
    uint16_t   field_0x4;   /* +0x4  sz=2,4 rw=rw types=idx4,undefined2 */
    uint16_t   field_0x6;   /* +0x6  sz=4 rw=w types=undefined4 */
    uint16_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4,int */
    uint16_t   field_0xa;   /* +0xa  sz=2 rw=w types=undefined2 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=idx4 */
};
```