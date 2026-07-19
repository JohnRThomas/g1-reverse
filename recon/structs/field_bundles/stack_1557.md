### struct event_tag4_clear_tmp  (G1-original)  cid=stack_1557

purpose: Stack-local tag/flag pair (local_24) inside post_event_tag4_and_clear.

This object is accessed by these functions (read their fully-named source):
  - post_event_tag4_and_clear  (as local_24)  ->  recon/readable_sources/app/g1/post_event_tag4_and_clear.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct event_tag4_clear_tmp {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x4;  /* +0x4  rw=r sz=1 */   <-- NAME ME
};
```