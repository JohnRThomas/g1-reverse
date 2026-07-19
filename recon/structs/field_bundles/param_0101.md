### struct param_0101_false_union  (G1-original)  cid=param_0101

purpose: COINCIDENTAL over-unification: this cid merges param pointers from 18 unrelated functions (cJSON/log parse, mpsc_pbuf_init, img_mgmt, smp_transport_init, bt_keys_clear, lc3 setup, rpmsg/virtqueue, k_work_init, mbedtls ctr_drbg, onoff_manager_init, ipc vrings). Not one real object — a union of several distinct real structs sharing only generic first-arg pointer flow.

This object is accessed by these functions (read their fully-named source):
  - parse_ncs_notification  (as param_2)  ->  recon/readable_sources/app/g1/parse_ncs_notification.c
  - log_notification_fields_debug  (as param_2)  ->  recon/readable_sources/app/g1/log_notification_fields_debug.c
  - mpsc_pbuf_init  (as param_1)  ->  recon/readable_sources/app/library/mpsc_pbuf_init.c
  - FUN_0004d058  (as param_1)  [no source file]
  - img_mgmt_upload_inspect  (as param_2)  ->  recon/readable_sources/app/library/img_mgmt_upload_inspect.c
  - img_mgmt_read_info  (as param_2)  ->  recon/readable_sources/app/library/img_mgmt_read_info.c
  - smp_transport_init  (as param_1)  ->  recon/readable_sources/app/library/smp_transport_init.c
  - bt_keys_clear  (as param_1)  ->  recon/readable_sources/app/library/bt_keys_clear.c
  - lc3_setup_bits  (as param_1)  ->  recon/readable_sources/app/library/lc3_setup_bits.c
  - lc3_setup_encoder  (as param_4)  ->  recon/readable_sources/app/library/lc3_setup_encoder.c
  - rpmsg_register_endpoint  (as param_1)  [no source file]
  - rpmsg_create_ept  (as param_2)  [no source file]
  - rpmsg_virtqueue_channel_init  (as param_1)  ->  recon/readable_sources/app/library/rpmsg_virtqueue_channel_init.c
  - k_work_init  (as param_1)  ->  recon/readable_sources/app/library/k_work_init.c
  - k_work_init_delayable  (as param_1)  ->  recon/readable_sources/app/library/k_work_init_delayable.c
  - cc_mbedtls_ctr_drbg_init  (as param_1)  [no source file]
  - onoff_manager_init  (as param_1)  [no source file]
  - ipc_static_vrings_deinit  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct param_0101_false_union {
    int32_t      field_0x0;  /* +0x0  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=rw sz=1,4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=rw sz=4 */   <-- NAME ME
    void *       field_0x10;  /* +0x10  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x1c;  /* +0x1c  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x20;  /* +0x20  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x24;  /* +0x24  rw=w sz=4 */   <-- NAME ME
    void *       cb_ptr_0x28;  /* +0x28  rw=w sz=4 */
    void *       cb_ptr_0x2c;  /* +0x2c  rw=rw sz=4 */
    void *       cb_ptr_0x30;  /* +0x30  rw=w sz=4 */
    void *       cb_ptr_0x34;  /* +0x34  rw=w sz=4 */
    uint32_t     field_0x48;  /* +0x48  rw=r sz=4 */   <-- NAME ME
    void *       field_0x6c;  /* +0x6c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x70;  /* +0x70  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x78;  /* +0x78  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x7c;  /* +0x7c  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x80;  /* +0x80  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x84;  /* +0x84  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x88;  /* +0x88  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x8c;  /* +0x8c  rw=w sz=4 */   <-- NAME ME
    uint8_t      flag_0x90;  /* +0x90  rw=rw sz=1 */
    uint32_t     field_0x94;  /* +0x94  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x98;  /* +0x98  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x9c;  /* +0x9c  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0xa0;  /* +0xa0  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xa4;  /* +0xa4  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xa8;  /* +0xa8  rw=rw sz=4 */   <-- NAME ME
    void *       field_0xac;  /* +0xac  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0xb0;  /* +0xb0  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xb4;  /* +0xb4  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0xb8;  /* +0xb8  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0xd4;  /* +0xd4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xd8;  /* +0xd8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1b0;  /* +0x1b0  rw=r sz=4 */   <-- NAME ME
    void *       field_0x4a0;  /* +0x4a0  rw=w sz=4 */   <-- NAME ME
    void *       field_0x4a4;  /* +0x4a4  rw=w sz=4 */   <-- NAME ME
    void *       field_0x4a8;  /* +0x4a8  rw=w sz=4 */   <-- NAME ME
};
```