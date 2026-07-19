## review group param_0265  (1 cluster(s), kinds=param)

### proposal for param_0265
struct_name: bt_smp | is_library: True | library_name: struct bt_smp (Zephyr subsys/bluetooth/host/smp.c) | is_array: None | confidence: high
purpose: Zephyr Bluetooth SMP (Security Manager Protocol) pairing context struct, shared across the whole SMP pairing state machine (pairing req/confirm/random, DHKey check, identity info, error handling).
fields:
  0x2  uint8_t      field_0x2  
  0x4  uint32_t     chan_conn  likely bt_l2cap_chan/conn pointer index
  0x8  uint8_t      field_0x8  
  0x9  uint8_t      field_0x9  
  0xa  uint32_t     field_0xa  
  0xe  uint16_t     field_0xe  
  0x10  uint8_t      method  pairing method byte
  0x11  uint32_t     field_0x11  
  0x15  uint16_t     field_0x15  
  0x47  uint8_t      local_key_byte0  part of local/remote key material buffer region
  0x48  uint8_t      local_key_byte1  
  0x49  uint8_t      local_key_byte2  
  0x4a  uint8_t      local_key_byte3  
  0xd8  uint32_t     field_0xd8  
  0xdc  uint8_t      field_0xdc  
  0xe0  void *       field_0xe0  
  0xe4  void *       field_0xe4  
  0xe8  uint16_t     field_0xe8  
  0xf0  uint32_t     field_0xf0  

<ground-truth bundle for param_0265>
### cluster param_0265  (param, 14 members, 27 fields, size>=0xf4)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att,bt,smp; 0/14 members are LIBRARY-class)

members (14 shown of 14):
  - bt_smp_send_pdu @ 0x5cb38  as param_1  [APPLICATION]
  - bt_smp_send_pairing_confirm @ 0x5cdc4  as param_1  [APPLICATION]
  - smp_public_key_central @ 0x5cff0  as param_1  [APPLICATION]
  - smp_dhkey_check_generate @ 0x5d0ac  as param_1  [APPLICATION]
  - smp_pairing_req @ 0x5d5c0  as param_1  [APPLICATION]
  - smp_pairing_complete @ 0x5daf0  as param_1  [APPLICATION]
  - smp_error @ 0x5dc2c  as param_1  [APPLICATION]
  - smp_ident_addr_info @ 0x5de70  as param_1  [APPLICATION]
  - smp_central_ident @ 0x5e080  as param_1  [APPLICATION]
  - FUN_0005e130 @ 0x5e130  as param_1  [APPLICATION]
  - bt_conn_security_sufficient @ 0x83002  as param_1  [APPLICATION]
  - send_pairing_rsp @ 0x830ee  as param_1  [APPLICATION]
  - att_chan_reset @ 0x83204  as param_1  [APPLICATION]
  - smp_pairing_confirm_send @ 0x832f0  as param_1  [APPLICATION]

layout notes: 0xa: access width 4 exceeds gap 1 to next field (overlap/union); 0x11: access width 4 exceeds gap 1 to next field (overlap/union); 0x15: access width 2 exceeds gap 1 to next field (overlap/union); 0xe8: access width 2 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0265 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x3[0x1];   /* +0x3 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=rw types=byte,char */
    uint8_t    field_0x9;   /* +0x9  sz=1 rw=w types=undefined1 */
    uint8_t    field_0xa;   /* +0xa  sz=4 rw=w types=undefined4 */
    uint8_t    field_0xb;   /* +0xb  sz=1 rw=r types=byte */
    uint8_t    field_0xc;   /* +0xc  sz=1 rw=r types=byte */
    uint8_t    field_0xd;   /* +0xd  sz=1 rw=r types=byte */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=w types=undefined2 */
    uint8_t    field_0x10;   /* +0x10  sz=1 rw=w types=undefined1 */
    uint8_t    field_0x11;   /* +0x11  sz=1,4 rw=rw types=undefined1,undefined4 */
    uint8_t    field_0x12;   /* +0x12  sz=1 rw=rw types=byte,undefined1 */
    uint8_t    field_0x13;   /* +0x13  sz=1 rw=rw types=byte,undefined1 */
    uint8_t    field_0x14;   /* +0x14  sz=1 rw=rw types=byte,undefined1 */
    uint8_t    field_0x15;   /* +0x15  sz=1,2 rw=rw types=byte,undefined1,undefined2 */
    uint8_t    field_0x16;   /* +0x16  sz=1 rw=rw types=byte,undefined1 */
    uint8_t    _pad_0x17[0x30];   /* +0x17 pad */
    uint8_t    field_0x47;   /* +0x47  sz=1 rw=w types=char */
    uint8_t    field_0x48;   /* +0x48  sz=1 rw=w types=char */
    uint8_t    field_0x49;   /* +0x49  sz=1 rw=w types=char */
    uint8_t    field_0x4a;   /* +0x4a  sz=1 rw=w types=char */
    uint8_t    _pad_0x4b[0x8d];   /* +0x4b pad */
    uint32_t   field_0xd8;   /* +0xd8  sz=4 rw=rw types=uint,undefined4 */
    uint8_t    field_0xdc;   /* +0xdc  sz=1 rw=rw types=byte,undefined1 */
    uint8_t    _pad_0xdd[0x3];   /* +0xdd pad */
    void *     field_0xe0;   /* +0xe0  sz=4 rw=r types=ptr */
    void *     field_0xe4;   /* +0xe4  sz=4 rw=r types=ptr */
    uint8_t    field_0xe8;   /* +0xe8  sz=1,2 rw=rw types=short,undefined1 */
    uint8_t    field_0xe9;   /* +0xe9  sz=1 rw=rw types=byte,undefined1 */
    uint8_t    _pad_0xea[0x6];   /* +0xea pad */
    uint32_t   field_0xf0;   /* +0xf0  sz=4 rw=r types=int,undefined4 */
};
```
