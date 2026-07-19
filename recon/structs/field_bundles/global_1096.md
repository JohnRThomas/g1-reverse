### struct app_event_header  (library:struct app_event_header (NCS app_event_manager))  cid=global_1096

purpose: Event header (fixed global 0x4f850) passed to app_event_manager_submit (NCS Application Event Manager): event type-id pointer plus one index-typed word.

This object is accessed by these functions (read their fully-named source):
  - app_event_manager_submit  (as 0x0004f850)  ->  recon/readable_sources/app/g1/app_event_manager_submit.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct app_event_header {
    uint32_t     type_id;  /* +0x0  rw=r sz=4 */
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
};
```