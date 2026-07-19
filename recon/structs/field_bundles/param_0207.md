### struct k_poll_event  (library:k_poll_event)  cid=param_0207

purpose: Zephyr k_poll_event poll descriptor initialized by k_poll_event_init (poller ptr, packed type/state/mode bitfields, obj union). Cluster also merges an unrelated bt_conn param at the same slot.

This object is accessed by these functions (read their fully-named source):
  - bt_conn_prepare_tx_events  (as param_1)  ->  recon/readable_sources/app/library/bt_conn_prepare_tx_events.c
  - k_poll_event_init  (as param_1)  ->  recon/readable_sources/app/library/k_poll_event_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct k_poll_event {
    struct z_poller * poller;  /* +0x8  rw=w sz=4 */
    uint32_t     tag_type_state_mode;  /* +0xc  rw=rw sz=1,4 */
    void *       obj;  /* +0x10  rw=w sz=4 */
    uint8_t      field_0x20;  /* +0x20  rw=w sz=1 */   <-- NAME ME
};
```