## review group param_0007  (1 cluster(s), kinds=param)

### proposal for param_0007
struct_name: app_shared_ctx_blob | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Very large (0x1578-byte) heterogeneous object shared across unrelated functions (random, PKCS7 parsing, BLE dispatch, notification building, push_message, battery SOC curve model init) — evidence pattern (disjoint clusters of scalar fields at low offsets plus five separate float-array regions) strongly suggests this cluster is a mis-merge of multiple distinct pointer objects rather than one true struct; the float regions at 0x324-0x334, 0x11a8-0x11ac, 0x1388-0x1394, 0x1570-0x1574 look like fragments of the battery SOC calibration curve table
fields:
  0x1  uint16_t     field_0x1  overlapping access widths (1/2 bytes) suggest header/flags region
  0x3  uint8_t      field_0x3  
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  rw
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x1b0  int32_t      field_0x1b0  
  0x324  float        soc_curve_pt0  battery SOC calibration float array fragment
  0x328  float        soc_curve_pt1  
  0x32c  float        soc_curve_pt2  
  0x330  float        soc_curve_pt3  
  0x334  float        soc_curve_pt4  
  0x514  float        field_0x514  isolated float, unclear grouping
  0x11a8  float        field_0x11a8  second float-array region
  0x11ac  float        field_0x11ac  
  0x1388  float        field_0x1388  third float-array region
  0x138c  float        field_0x138c  
  0x1390  float        field_0x1390  
  0x1394  float        field_0x1394  
  0x1570  float        field_0x1570  fourth float-array region
  0x1574  float        field_0x1574  

<ground-truth bundle for param_0007>
### cluster param_0007  (param, 8 members, 29 fields, size>=0x1578)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (8 shown of 8):
  - random @ 0x17f70  as param_2  [APPLICATION]
  - parse_receiver_pack_pkcs7 @ 0x19cd0  as param_2  [APPLICATION]
  - parse_receiver_msg_pack_pkcs7 @ 0x19da4  as param_2  [APPLICATION]
  - build_status_notify_packet @ 0x21334  as param_2  [APPLICATION]
  - ble_process_req_dispatch @ 0x21460  as param_3  [APPLICATION]
  - post_notification_cmd_process @ 0x338ec  as param_3  [APPLICATION]
  - push_message @ 0x33f54  as param_1  [APPLICATION]
  - battery_soc_curve_model_init @ 0xe53c  as param_7  [APPLICATION]

layout notes: 0x1: access width 2 exceeds gap 1 to next field (overlap/union); 0x4: access width 4 exceeds gap 1 to next field (overlap/union); 0xc: access width 4 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0007 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1,2 rw=r types=byte,short,undefined1 */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=byte,undefined1 */
    uint8_t    field_0x3;   /* +0x3  sz=1 rw=r types=byte,char,undefined1 */
    uint8_t    field_0x4;   /* +0x4  sz=1,4 rw=r types=byte,char,idx4,undefined1,undefined4 */
    uint8_t    field_0x5;   /* +0x5  sz=1 rw=r types=byte */
    uint8_t    field_0x6;   /* +0x6  sz=1 rw=r types=byte */
    uint8_t    field_0x7;   /* +0x7  sz=1 rw=r types=undefined1 */
    uint32_t   field_0x8;   /* +0x8  sz=1,4 rw=r types=idx4,undefined1,undefined4 */
    uint8_t    field_0xc;   /* +0xc  sz=1,4 rw=rw types=byte,idx4 */
    uint8_t    field_0xd;   /* +0xd  sz=1 rw=w types=undefined1 */
    uint8_t    field_0xe;   /* +0xe  sz=1 rw=w types=undefined1 */
    uint8_t    field_0xf;   /* +0xf  sz=1 rw=w types=undefined1 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x198];   /* +0x18 pad */
    uint32_t   field_0x1b0;   /* +0x1b0  sz=4 rw=r types=int,undefined4 */
    uint8_t    _pad_0x1b4[0x170];   /* +0x1b4 pad */
    float      field_0x324;   /* +0x324  sz=4 rw=r types=float */
    float      field_0x328;   /* +0x328  sz=4 rw=r types=float */
    float      field_0x32c;   /* +0x32c  sz=4 rw=r types=float */
    float      field_0x330;   /* +0x330  sz=4 rw=r types=float */
    float      field_0x334;   /* +0x334  sz=4 rw=r types=float */
    uint8_t    _pad_0x338[0x1dc];   /* +0x338 pad */
    float      field_0x514;   /* +0x514  sz=4 rw=r types=float */
    uint8_t    _pad_0x518[0xc90];   /* +0x518 pad */
    float      field_0x11a8;   /* +0x11a8  sz=4 rw=r types=float */
    float      field_0x11ac;   /* +0x11ac  sz=4 rw=r types=float */
    uint8_t    _pad_0x11b0[0x1d8];   /* +0x11b0 pad */
    float      field_0x1388;   /* +0x1388  sz=4 rw=r types=float */
    float      field_0x138c;   /* +0x138c  sz=4 rw=r types=float */
    float      field_0x1390;   /* +0x1390  sz=4 rw=r types=float */
    float      field_0x1394;   /* +0x1394  sz=4 rw=r types=float */
    uint8_t    _pad_0x1398[0x1d8];   /* +0x1398 pad */
    float      field_0x1570;   /* +0x1570  sz=4 rw=r types=float */
    float      field_0x1574;   /* +0x1574  sz=4 rw=r types=float */
};
```
