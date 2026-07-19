### struct bt_smp  (library:bt_smp)  cid=param_0265

purpose: Zephyr Bluetooth SMP pairing context, shared across the whole SMP pairing state machine (pairing req/confirm/random, DHKey check, identity, error handling).

This object is accessed by these functions (read their fully-named source):
  - bt_smp_send_pdu  (as param_1)  ->  recon/readable_sources/app/library/bt_smp_send_pdu.c
  - bt_smp_send_pairing_confirm  (as param_1)  ->  recon/readable_sources/app/library/bt_smp_send_pairing_confirm.c
  - smp_public_key_central  (as param_1)  ->  recon/readable_sources/app/library/smp_public_key_central.c
  - smp_dhkey_check_generate  (as param_1)  ->  recon/readable_sources/app/library/smp_dhkey_check_generate.c
  - smp_pairing_req  (as param_1)  ->  recon/readable_sources/app/library/smp_pairing_req.c
  - smp_pairing_complete  (as param_1)  ->  recon/readable_sources/app/library/smp_pairing_complete.c
  - smp_error  (as param_1)  ->  recon/readable_sources/app/library/smp_error.c
  - smp_ident_addr_info  (as param_1)  ->  recon/readable_sources/app/library/smp_ident_addr_info.c
  - smp_central_ident  (as param_1)  ->  recon/readable_sources/app/library/smp_central_ident.c
  - FUN_0005e130  (as param_1)  [no source file]
  - bt_conn_security_sufficient  (as param_1)  ->  recon/readable_sources/app/library/bt_conn_security_sufficient.c
  - send_pairing_rsp  (as param_1)  ->  recon/readable_sources/app/g1/send_pairing_rsp.c
  - att_chan_reset  (as param_1)  ->  recon/readable_sources/app/library/att_chan_reset.c
  - smp_pairing_confirm_send  (as param_1)  ->  recon/readable_sources/app/library/smp_pairing_confirm_send.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_smp {
    uint8_t      field_0x2;  /* +0x2  rw=w sz=1 */   <-- NAME ME
    uint32_t     chan_or_conn;  /* +0x4  rw=r sz=4 */
    uint8_t      field_0x8;  /* +0x8  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0x9;  /* +0x9  rw=w sz=1 */   <-- NAME ME
    uint32_t     field_0xa;  /* +0xa  rw=w sz=4 */   <-- NAME ME
    uint8_t      field_0xb;  /* +0xb  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0xc;  /* +0xc  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0xd;  /* +0xd  rw=r sz=1 */   <-- NAME ME
    uint16_t     field_0xe;  /* +0xe  rw=w sz=2 */   <-- NAME ME
    uint8_t      method;  /* +0x10  rw=w sz=1 */
    uint32_t     field_0x11;  /* +0x11  rw=rw sz=1,4 */   <-- NAME ME
    uint8_t      field_0x12;  /* +0x12  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0x13;  /* +0x13  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0x14;  /* +0x14  rw=rw sz=1 */   <-- NAME ME
    uint16_t     field_0x15;  /* +0x15  rw=rw sz=1,2 */   <-- NAME ME
    uint8_t      field_0x16;  /* +0x16  rw=rw sz=1 */   <-- NAME ME
    uint8_t      key_byte_0;  /* +0x47  rw=w sz=1 */
    uint8_t      key_byte_1;  /* +0x48  rw=w sz=1 */
    uint8_t      key_byte_2;  /* +0x49  rw=w sz=1 */
    uint8_t      key_byte_3;  /* +0x4a  rw=w sz=1 */
    uint32_t     field_0xd8;  /* +0xd8  rw=rw sz=4 */   <-- NAME ME
    uint8_t      field_0xdc;  /* +0xdc  rw=rw sz=1 */   <-- NAME ME
    void *       field_0xe0;  /* +0xe0  rw=r sz=4 */   <-- NAME ME
    void *       field_0xe4;  /* +0xe4  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0xe8;  /* +0xe8  rw=rw sz=1,2 */   <-- NAME ME
    uint8_t      field_0xe9;  /* +0xe9  rw=rw sz=1 */   <-- NAME ME
    uint32_t     field_0xf0;  /* +0xf0  rw=r sz=4 */   <-- NAME ME
};
```