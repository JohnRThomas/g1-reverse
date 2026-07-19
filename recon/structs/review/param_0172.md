## review group param_0172  (1 cluster(s), kinds=param)

### proposal for param_0172
struct_name: net_buf | is_library: True | library_name: net_buf | is_array: None | confidence: medium
purpose: Zephyr net_buf network buffer object threaded through the BLE stack (HCI/L2CAP/ATT/SMP receive and send paths, net_buf_ref/unref/id/frags_len).
fields:
  0x4  void *       frags  struct net_buf *frags fragment chain pointer
  0x8  uint8_t      ref  reference count byte
  0x9  uint8_t      flags  flag byte
  0xa  uint8_t      pool_id  pool index byte
  0xb  uint8_t      user_data_size  byte
  0xc  void *       user_data_or_size  packed size/len or user_data pointer region
  0x10  uint16_t     len  current buffer length
  0x14  uint32_t     reserved  rw word
  0x18  void *       data  uint8_t *data pointer into backing storage
  0x1c  uint8_t      tail_flag  write-only trailing byte

<ground-truth bundle for param_0172>
### cluster param_0172  (param, 16 members, 10 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att,bt,hci,l2cap,net_buf,smp; 3/16 members are LIBRARY-class)

members (16 shown of 16):
  - smp_process_request_packet @ 0x513e8  as param_2  [APPLICATION]
  - hci_event_dispatch_handler @ 0x53658  as param_2  [APPLICATION]
  - hci_cmd_complete_handle @ 0x538f8  as param_3  [APPLICATION]
  - hci_event_prio @ 0x54784  as param_1  [LIBRARY]
  - bt_hci_core_recv_dispatch @ 0x54828  as param_1  [APPLICATION]
  - bt_acl_data_recv @ 0x56394  as param_2  [APPLICATION]
  - l2cap_chan_le_send_seg @ 0x5757c  as param_2  [APPLICATION]
  - bt_l2cap_recv @ 0x57cc4  as param_2  [APPLICATION]
  - att_chan_send @ 0x58a54  as param_2  [APPLICATION]
  - bt_att_recv @ 0x58cfc  as param_2  [APPLICATION]
  - net_buf_id @ 0x5ee18  as param_1  [LIBRARY]
  - net_buf_unref @ 0x5f24c  as param_1  [APPLICATION]
  - net_buf_ref @ 0x5f2d4  as param_1  [APPLICATION]
  - smp_alloc_rsp @ 0x80ae6  as param_1  [APPLICATION]
  - net_buf_frags_len @ 0x81616  as param_1  [LIBRARY]
  - bt_conn_create_pdu @ 0x81820  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0172 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=rw types=int,undefined4 */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=rw types=char */
    uint8_t    field_0x9;   /* +0x9  sz=1 rw=r types=byte */
    uint8_t    field_0xa;   /* +0xa  sz=1 rw=r types=byte,undefined1 */
    uint8_t    field_0xb;   /* +0xb  sz=1 rw=r types=byte,undefined1 */
    void *     field_0xc;   /* +0xc  sz=4 rw=rw types=ptr,uint,undefined4 */
    uint16_t   field_0x10;   /* +0x10  sz=2 rw=rw types=short,undefined2,ushort */
    uint8_t    _pad_0x12[0x2];   /* +0x12 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=rw types=int,undefined4 */
    void *     field_0x18;   /* +0x18  sz=1,4 rw=rw types=byte,int,ptr,undefined4 */
    uint8_t    field_0x1c;   /* +0x1c  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x1d[0x3];   /* +0x1d pad */
};
```
