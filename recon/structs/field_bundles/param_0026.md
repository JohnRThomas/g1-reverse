### struct esbs_ipc_msg  (G1-original)  cid=param_0026

purpose: IPC message struct passed to local_esbs_ipc_service_recv; header bytes at 0x4 overlapped by a wide word read, plus three data words.

This object is accessed by these functions (read their fully-named source):
  - local_esbs_ipc_service_recv  (as param_2)  ->  recon/readable_sources/app/g1/local_esbs_ipc_service_recv.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct esbs_ipc_msg {
    uint8_t[3]   field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x7;  /* +0x7  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```