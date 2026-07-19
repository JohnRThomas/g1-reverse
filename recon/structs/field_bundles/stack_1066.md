### struct log_msg_desc_local  (G1-original)  cid=stack_1066

purpose: Stack local (local_2c) in g1_recon_z_log_msg_alloc: a size/id word plus a length/pointer word, mirroring a Zephyr log message allocation descriptor.

This object is accessed by these functions (read their fully-named source):
  - g1_recon_z_log_msg_alloc  (as local_2c)  ->  recon/readable_sources/app/g1/g1_recon_z_log_msg_alloc.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct log_msg_desc_local {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```