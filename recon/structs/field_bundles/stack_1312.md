### struct gpiote_evt_info  (G1-original)  cid=stack_1312

purpose: Stack-local GPIOTE event info (local_30) in gpiote_irq_handler (pin/event pair + third word).

This object is accessed by these functions (read their fully-named source):
  - gpiote_irq_handler  (as local_30)  ->  recon/readable_sources/app/library/gpiote_irq_handler.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct gpiote_evt_info {
    uint32_t     pin;  /* +0x0  rw=r sz=4 */
    uint32_t     event_or_action;  /* +0x4  rw=r sz=4 */
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
};
```