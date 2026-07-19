### struct ipc0_ept_recv_msg  (G1-original)  cid=param_0061

purpose: Message/buffer object passed as param_1 to ipc0_ept_recv (nRF IPC service endpoint receive callback), read as consecutive words.

This object is accessed by these functions (read their fully-named source):
  - ipc0_ept_recv  (as param_1)  ->  recon/readable_sources/app/g1/ipc0_ept_recv.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ipc0_ept_recv_msg {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1c;  /* +0x1c  rw=r sz=4 */   <-- NAME ME
};
```