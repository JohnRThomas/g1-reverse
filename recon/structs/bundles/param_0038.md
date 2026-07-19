### cluster param_0038  (param, 7 members, 12 fields, size>=0x84a)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (7 shown of 7):
  - ble_ancs_data_req_thread @ 0x19718  as param_1  [APPLICATION]
  - audio_fw_load_get_wrapper @ 0x19b54  as param_1  [APPLICATION]
  - send_dmic_msg @ 0x19ed4  as param_1  [APPLICATION]
  - build_status_notify_packet @ 0x21334  as param_1  [APPLICATION]
  - ble_process_req_dispatch @ 0x21460  as param_1  [APPLICATION]
  - post_notification_cmd_process @ 0x338ec  as param_1  [APPLICATION]
  - ble_flush_queued_indications @ 0x7c20a  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0038 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    void *     field_0xc;   /* +0xc  sz=4 rw=r types=ptr */
    void *     field_0x10;   /* +0x10  sz=4 rw=rw types=ptr,undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=rw types=uint,undefined4 */
    uint8_t    _pad_0x18[0x24];   /* +0x18 pad */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x40[0x1];   /* +0x40 pad */
    uint8_t    field_0x41;   /* +0x41  sz=1 rw=w types=undefined1 */
    uint8_t    field_0x42;   /* +0x42  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x43[0x1];   /* +0x43 pad */
    uint8_t    field_0x44;   /* +0x44  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x45[0x1f];   /* +0x45 pad */
    uint8_t    field_0x64;   /* +0x64  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x65[0x17f];   /* +0x65 pad */
    uint32_t   field_0x1e4;   /* +0x1e4  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x1e8[0x571];   /* +0x1e8 pad */
    uint8_t    field_0x759;   /* +0x759  sz=1 rw=r types=byte */
    uint8_t    _pad_0x75a[0xea];   /* +0x75a pad */
    uint8_t    field_0x844;   /* +0x844  sz=1 rw=r types=byte */
    uint8_t    _pad_0x845[0x1];   /* +0x845 pad */
    uint8_t    field_0x846;   /* +0x846  sz=1 rw=r types=char */
    uint8_t    _pad_0x847[0x3];   /* +0x847 pad */
};
```