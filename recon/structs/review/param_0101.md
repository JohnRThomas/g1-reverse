## review group param_0101  (1 cluster(s), kinds=param)

### proposal for param_0101
struct_name: generic_ctx_merge_ambiguous | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Cluster merges parameters from many unrelated functions (cJSON/log parsing, mpsc_pbuf, img_mgmt, smp_transport, bt_keys, lc3 setup, rpmsg/virtqueue, k_work, mbedtls ctr_drbg, onoff_manager, ipc vrings) — almost certainly a false unification of several distinct real structs sharing only generic pointer-arg flow, not one true object.
fields:
  0x0  int          field_0x0  
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  void *       field_0x10  
  0x18  uint32_t     field_0x18  
  0x1c  uint32_t     field_0x1c  
  0x20  uint32_t     field_0x20  
  0x24  uint32_t     field_0x24  
  0x28  void *       cb_ptr_0x28  
  0x2c  void *       cb_ptr_0x2c  
  0x30  void *       cb_ptr_0x30  
  0x34  void *       cb_ptr_0x34  
  0x48  uint32_t     field_0x48  
  0x6c  void *       field_0x6c  
  0x70  uint32_t     field_0x70  
  0x78  uint32_t     field_0x78  
  0x7c  uint32_t     field_0x7c  
  0x80  uint32_t     field_0x80  
  0x84  uint32_t     field_0x84  
  0x88  uint32_t     field_0x88  
  0x8c  uint32_t     field_0x8c  
  0x90  uint8_t      flag_0x90  
  0x94  uint32_t     field_0x94  
  0x98  uint32_t     field_0x98  
  0x9c  uint32_t     field_0x9c  
  0xa0  uint32_t     field_0xa0  
  0xa4  uint32_t     field_0xa4  
  0xa8  uint32_t     field_0xa8  
  0xac  void *       field_0xac  
  0xb0  uint32_t     field_0xb0  
  0xb4  uint32_t     field_0xb4  
  0xb8  uint32_t     field_0xb8  
  0xd4  uint32_t     field_0xd4  
  0xd8  uint32_t     field_0xd8  
  0x1b0  uint32_t     field_0x1b0  
  0x4a0  void *       field_0x4a0  
  0x4a4  void *       field_0x4a4  
  0x4a8  void *       field_0x4a8  

<ground-truth bundle for param_0101>
### cluster param_0101  (param, 18 members, 39 fields, size>=0x4ac)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt,k,lc3,log,smp; 4/18 members are LIBRARY-class)

members (18 shown of 18):
  - parse_ncs_notification @ 0x34980  as param_2  [APPLICATION]
  - log_notification_fields_debug @ 0x4a3d0  as param_2  [APPLICATION]
  - mpsc_pbuf_init @ 0x4bc28  as param_1  [APPLICATION]
  - FUN_0004d058 @ 0x4d058  as param_1  [APPLICATION]
  - img_mgmt_upload_inspect @ 0x518a8  as param_2  [APPLICATION]
  - img_mgmt_read_info @ 0x52038  as param_2  [APPLICATION]
  - smp_transport_init @ 0x526f4  as param_1  [APPLICATION]
  - bt_keys_clear @ 0x5ea18  as param_1  [APPLICATION]
  - lc3_setup_bits @ 0x684a8  as param_1  [APPLICATION]
  - lc3_setup_encoder @ 0x68f94  as param_4  [APPLICATION]
  - rpmsg_register_endpoint @ 0x70f74  as param_1  [LIBRARY]
  - rpmsg_create_ept @ 0x70fb4  as param_2  [LIBRARY]
  - rpmsg_virtqueue_channel_init @ 0x71358  as param_1  [APPLICATION]
  - k_work_init @ 0x72e50  as param_1  [APPLICATION]
  - k_work_init_delayable @ 0x732d4  as param_1  [APPLICATION]
  - cc_mbedtls_ctr_drbg_init @ 0x79c24  as param_1  [LIBRARY]
  - onoff_manager_init @ 0x7e212  as param_1  [APPLICATION]
  - ipc_static_vrings_deinit @ 0x7eda4  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0101 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=w types=int */
    uint32_t   field_0x4;   /* +0x4  sz=1,4 rw=rw types=idx4,int,uint,undefined1,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=idx4,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=idx4,undefined4 */
    void *     field_0x10;   /* +0x10  sz=4 rw=w types=ptr,uint,undefined4 */
    uint8_t    _pad_0x14[0x4];   /* +0x14 pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=rw types=uint,undefined4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=rw types=idx4,int,uint,undefined4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=w types=uint */
    void *     field_0x28;   /* +0x28  sz=4 rw=w types=ptr,undefined4 */
    void *     field_0x2c;   /* +0x2c  sz=4 rw=rw types=int,ptr */
    void *     field_0x30;   /* +0x30  sz=4 rw=w types=ptr */
    void *     field_0x34;   /* +0x34  sz=4 rw=w types=ptr */
    uint8_t    _pad_0x38[0x10];   /* +0x38 pad */
    uint32_t   field_0x48;   /* +0x48  sz=4 rw=r types=uint */
    uint8_t    _pad_0x4c[0x20];   /* +0x4c pad */
    void *     field_0x6c;   /* +0x6c  sz=4 rw=r types=ptr */
    uint32_t   field_0x70;   /* +0x70  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x74[0x4];   /* +0x74 pad */
    uint32_t   field_0x78;   /* +0x78  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x7c;   /* +0x7c  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x80;   /* +0x80  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x84;   /* +0x84  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x88;   /* +0x88  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x8c;   /* +0x8c  sz=4 rw=w types=undefined4 */
    uint8_t    field_0x90;   /* +0x90  sz=1 rw=rw types=byte,char */
    uint8_t    _pad_0x91[0x3];   /* +0x91 pad */
    uint32_t   field_0x94;   /* +0x94  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x98;   /* +0x98  sz=4 rw=rw types=undefined4 */
    uint32_t   field_0x9c;   /* +0x9c  sz=4 rw=w types=undefined4 */
    uint32_t   field_0xa0;   /* +0xa0  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0xa4;   /* +0xa4  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0xa8;   /* +0xa8  sz=4 rw=rw types=undefined4 */
    void *     field_0xac;   /* +0xac  sz=4 rw=w types=ptr */
    uint32_t   field_0xb0;   /* +0xb0  sz=4 rw=rw types=int */
    uint32_t   field_0xb4;   /* +0xb4  sz=4 rw=w types=int */
    uint32_t   field_0xb8;   /* +0xb8  sz=4 rw=w types=int */
    uint8_t    _pad_0xbc[0x18];   /* +0xbc pad */
    uint32_t   field_0xd4;   /* +0xd4  sz=4 rw=r types=undefined4 */
    uint32_t   field_0xd8;   /* +0xd8  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0xdc[0xd4];   /* +0xdc pad */
    uint32_t   field_0x1b0;   /* +0x1b0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x1b4[0x2ec];   /* +0x1b4 pad */
    void *     field_0x4a0;   /* +0x4a0  sz=4 rw=w types=ptr */
    void *     field_0x4a4;   /* +0x4a4  sz=4 rw=w types=ptr */
    void *     field_0x4a8;   /* +0x4a8  sz=4 rw=w types=ptr */
};
```
