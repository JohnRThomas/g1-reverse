### struct pt_queue_free_slot_state  (G1-original)  cid=global_0969

purpose: G1-original global at 0x33bec used by pt_queue_get_free_slot (index/flag bookkeeping bytes).

This object is accessed by these functions (read their fully-named source):
  - pt_queue_get_free_slot  (as 0x00033bec)  ->  recon/readable_sources/app/g1/pt_queue_get_free_slot.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct pt_queue_free_slot_state {
    uint8_t      write_idx;  /* +0x114  rw=w sz=1 */
    uint8_t      field_0x115;  /* +0x115  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x116;  /* +0x116  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x118;  /* +0x118  rw=r sz=1 */   <-- NAME ME
};
```