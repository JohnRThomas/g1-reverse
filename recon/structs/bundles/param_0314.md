### cluster param_0314  (param, 10 members, 3 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (10 shown of 10):
  - uart_poll_out @ 0x62f28  as param_1  [APPLICATION]
  - uarte_nrfx_tx_start @ 0x62fe8  as param_1  [APPLICATION]
  - uarte_nrfx_isr @ 0x6312c  as param_1  [APPLICATION]
  - audio_hw_lock_get_status_byte @ 0x7ef1c  as param_1  [APPLICATION]
  - transport_notify_callback @ 0x84840  as param_1  [APPLICATION]
  - post_event_tag2_from_node @ 0x8484e  as param_1  [APPLICATION]
  - audio_dma_start_transfer @ 0x8496c  as param_1  [APPLICATION]
  - nvs_timer_arm_and_mark_dirty @ 0x849da  as param_1  [APPLICATION]
  - uarte_nrfx_tx_complete @ 0x84ade  as param_1  [APPLICATION]
  - flowctl_release_credit_and_kick @ 0x84b32  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0314 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=int,ptr,undefined4 */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=int */
};
```