### struct mpsc_pbuf_buffer  (library:mpsc_pbuf_buffer)  cid=param_0132

purpose: param_2 of mpsc_pbuf_init - Zephyr multi-producer/single-consumer packet buffer instance (buffer ptr/size + wr/rd index bookkeeping).

This object is accessed by these functions (read their fully-named source):
  - mpsc_pbuf_init  (as param_2)  ->  recon/readable_sources/app/library/mpsc_pbuf_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct mpsc_pbuf_buffer {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```