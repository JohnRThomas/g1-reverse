### struct esbs_ipc_recv_ctx  (G1-original)  cid=param_0025

purpose: ~4KB local ESB/IPC service receive context (local_esbs_ipc_service_recv): header flag bytes, a large payload buffer region, then trailing buffer pointer + length/counters.

This object is accessed by these functions (read their fully-named source):
  - local_esbs_ipc_service_recv  (as param_1)  ->  recon/readable_sources/app/g1/local_esbs_ipc_service_recv.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct esbs_ipc_recv_ctx {
    uint8_t      field_0xc9;  /* +0xc9  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0xca;  /* +0xca  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0xcb;  /* +0xcb  rw=w sz=1 */   <-- NAME ME
    uint8_t      field_0xcc;  /* +0xcc  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0xcd;  /* +0xcd  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0xce;  /* +0xce  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0xcf;  /* +0xcf  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0xd5;  /* +0xd5  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0xda;  /* +0xda  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0xe4;  /* +0xe4  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0xe9;  /* +0xe9  rw=w sz=1 */   <-- NAME ME
    uint8_t      field_0xea;  /* +0xea  rw=w sz=1 */   <-- NAME ME
    uint8_t      field_0xeb;  /* +0xeb  rw=w sz=1 */   <-- NAME ME
    uint8_t      field_0xec;  /* +0xec  rw=w sz=1 */   <-- NAME ME
    uint8_t      field_0xee4;  /* +0xee4  rw=w sz=1 */   <-- NAME ME
    uint8_t      field_0xfe6;  /* +0xfe6  rw=r sz=1 */   <-- NAME ME
    void *       data_ptr;  /* +0xfec  rw=rw sz=4 */
    uint32_t     field_0xff4;  /* +0xff4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1024;  /* +0x1024  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1028;  /* +0x1028  rw=r sz=4 */   <-- NAME ME
};
```