### struct module_state_event  (library:module_state_event (CAF))  cid=param_0162

purpose: nRF Connect SDK CAF module_state_event handled by module_state_event_log_handler: module id pointer and state.

This object is accessed by these functions (read their fully-named source):
  - module_state_event_log_handler  (as param_1)  ->  recon/readable_sources/app/g1/module_state_event_log_handler.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct module_state_event {
    const void*  module_id;  /* +0x4  rw=r sz=4 */
    void*        field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint8_t      state;  /* +0xc  rw=r sz=1 */
};
```