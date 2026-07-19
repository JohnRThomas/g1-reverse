### struct log_msg_generic_hdr  (library:log_msg / mpsc_pbuf_hdr)  cid=param_0511

purpose: Zephyr log message header/descriptor accessed by log_msg_finalize_commit inside the mpsc_pbuf-backed logging buffer: two sequential descriptor/length words.

This object is accessed by these functions (read their fully-named source):
  - log_msg_finalize_commit  (as param_1)  ->  recon/readable_sources/app/g1/log_msg_finalize_commit.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct log_msg_generic_hdr {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```