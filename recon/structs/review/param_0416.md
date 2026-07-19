## review group param_0416  (1 cluster(s), kinds=param)

### proposal for param_0416
struct_name: k_poll_signal | is_library: True | library_name: k_poll_signal | is_array: None | confidence: high
purpose: Zephyr kernel poll-signal object, locked/signaled by poll_signal_event_locked
fields:
  0x8  uint32_t     signaled  matches k_poll_signal.signaled at +0x8 after 8-byte poll_events dlist node
  0xc  int32_t      result  matches k_poll_signal.result

<ground-truth bundle for param_0416>
### cluster param_0416  (param, 1 members, 2 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - poll_signal_event_locked @ 0x757b0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0416 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
