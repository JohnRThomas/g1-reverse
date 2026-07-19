### struct event_registration  (G1-original)  cid=param_0415

purpose: Event registration record shared by register_events and add_event: event id, callback pointer, count, and next-list pointer.

This object is accessed by these functions (read their fully-named source):
  - register_events  (as param_1)  ->  recon/readable_sources/app/g1/register_events.c
  - add_event  (as param_2)  ->  recon/readable_sources/app/g1/add_event.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct event_registration {
    uint32_t     event_id;  /* +0x4  rw=r sz=4 */
    void *       callback;  /* +0x8  rw=w sz=4 */
    uint32_t     count;  /* +0xc  rw=rw sz=4 */
    uint8_t      field_0xd;  /* +0xd  rw=r sz=1 */   <-- NAME ME
    void *       next;  /* +0x10  rw=r sz=4 */
};
```