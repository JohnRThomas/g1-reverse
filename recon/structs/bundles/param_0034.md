### cluster param_0034  (param, 21 members, 29 fields, size>=0xc4)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att,bt,l2cap,smp; 2/21 members are LIBRARY-class)

members (21 shown of 21):
  - ancs_connected @ 0x1861c  as param_1  [APPLICATION]
  - bt_conn_notify_connected @ 0x55fb4  as param_1  [APPLICATION]
  - tx_notify @ 0x56020  as param_1  [LIBRARY]
  - conn_tx_send_to_driver @ 0x560cc  as param_1  [APPLICATION]
  - bt_conn_tx_drain_and_reset @ 0x56300  as param_1  [APPLICATION]
  - bt_acl_data_recv @ 0x56394  as param_1  [APPLICATION]
  - ble_conn_unref @ 0x566a4  as param_1  [APPLICATION]
  - ble_conn_set_state @ 0x56704  as param_1  [APPLICATION]
  - bt_conn_disconnect_by_state @ 0x56a68  as param_1  [APPLICATION]
  - send_conn_le_param_update @ 0x57038  as param_1  [APPLICATION]
  - bt_conn_tx_process @ 0x571e8  as param_1  [APPLICATION]
  - l2cap_chan_add @ 0x57874  as param_1  [APPLICATION]
  - att_get @ 0x5858c  as param_1  [APPLICATION]
  - smp_send_security_req @ 0x5d964  as param_1  [APPLICATION]
  - bt_conn_reset_rx_state @ 0x813d6  as param_1  [LIBRARY]
  - FUN_0008142c @ 0x8142c  as param_1  [APPLICATION]
  - g1_recon_bt_conn_set_security @ 0x8149a  as param_1  [APPLICATION]
  - bt_conn_get_security @ 0x814e2  as param_1  [APPLICATION]
  - bt_conn_le_param_update @ 0x8157a  as param_1  [APPLICATION]
  - bt_conn_create_pdu @ 0x81820  as param_1  [APPLICATION]
  - bt_l2cap_le_lookup_rx_cid @ 0x81aca  as param_1  [APPLICATION]

layout notes: overlap at 0x3 (prev field ends 0x4); overlap at 0x6 (prev field ends 0x8); overlap at 0xc (prev field ends 0xe); overlap at 0xd (prev field ends 0xe); overlap at 0x10 (prev field ends 0x12)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0034 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=char,undefined1 */
    uint16_t   field_0x2;   /* +0x2  sz=1,2 rw=r types=byte,char,short */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=rw types=int,uint */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=r types=undefined1 */
    uint8_t    field_0x9;   /* +0x9  sz=1 rw=r types=undefined1 */
    void *     field_0xa;   /* +0xa  sz=1,4 rw=rw types=byte,ptr,undefined1 */
    uint32_t   field_0xe;   /* +0xe  sz=4 rw=r types=int */
    uint8_t    _pad_0x12[0x2];   /* +0x12 pad */
    void *     field_0x14;   /* +0x14  sz=4 rw=rw types=int,ptr,undefined4 */
    void *     field_0x18;   /* +0x18  sz=4 rw=rw types=ptr,undefined4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=rw types=int,undefined4 */
    void *     field_0x20;   /* +0x20  sz=4 rw=rw types=ptr,undefined4 */
    void *     field_0x24;   /* +0x24  sz=4 rw=rw types=ptr,undefined4 */
    uint8_t    _pad_0x28[0x2c];   /* +0x28 pad */
    void *     field_0x54;   /* +0x54  sz=4 rw=rw types=ptr,undefined4 */
    void *     field_0x58;   /* +0x58  sz=4 rw=rw types=ptr,undefined4 */
    uint8_t    _pad_0x5c[0x4a];   /* +0x5c pad */
    uint16_t   field_0xa6;   /* +0xa6  sz=2 rw=r types=ushort */
    uint16_t   field_0xa8;   /* +0xa8  sz=2 rw=w types=undefined2,ushort */
    uint16_t   field_0xaa;   /* +0xaa  sz=2 rw=w types=undefined2,ushort */
    uint16_t   field_0xac;   /* +0xac  sz=2 rw=r types=ushort */
    uint16_t   field_0xae;   /* +0xae  sz=2 rw=r types=ushort */
    uint16_t   field_0xb0;   /* +0xb0  sz=2 rw=w types=undefined2,ushort */
    uint16_t   field_0xb2;   /* +0xb2  sz=2 rw=w types=undefined2,ushort */
    uint8_t    field_0xb4;   /* +0xb4  sz=1 rw=w types=char */
    uint8_t    field_0xb5;   /* +0xb5  sz=1 rw=r types=byte */
    uint8_t    _pad_0xb6[0xa];   /* +0xb6 pad */
    uint32_t   field_0xc0;   /* +0xc0  sz=4 rw=rw types=int,undefined4 */
};
```