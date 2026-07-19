## review group param_0739  (1 cluster(s), kinds=param)

### proposal for param_0739
struct_name: k_poll_event | is_library: True | library_name: k_poll_event | is_array: None | confidence: medium
purpose: Zephyr k_poll event/signal object used by signal_poll_event: an object pointer and a state/result word
fields:
  0x8  void *       obj  rw pointer to waited-on kernel object
  0xc  uint32_t     state  rw uint, poll state/result

<ground-truth bundle for param_0739>
### cluster param_0739  (param, 1 members, 2 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - signal_poll_event @ 0x867da  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0739 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    void *     field_0x8;   /* +0x8  sz=4 rw=rw types=ptr,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=uint */
};
```
