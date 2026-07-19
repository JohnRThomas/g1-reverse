## review group param_0725  (1 cluster(s), kinds=param)

### proposal for param_0725
struct_name: k_msgq_state | is_library: True | library_name: struct k_msgq | is_array: False | confidence: high
purpose: Zephyr message queue control block initialized by k_msgq_init / z_impl_k_msgq_alloc_init.
fields:
  0x0  uint32_t     lock  k_spinlock lock word
  0x4  uint32_t     wait_q  wait queue head word
  0x8  uint32_t     msg_size  size of one message
  0xc  uint32_t     max_msgs  max queued messages
  0x10  uint8_t*     buffer_start  ring buffer start
  0x14  uint8_t*     buffer_end  ring buffer end
  0x18  uint8_t*     read_ptr  current read pointer
  0x1c  uint8_t*     write_ptr  current write pointer
  0x20  uint32_t     used_msgs  number of queued messages
  0x24  uint32_t     poll_events_or_flags  rw word, poll/event related
  0x28  uint32_t     field_0x28  write-only word
  0x2c  uint32_t     field_0x2c  write-only word
  0x30  uint8_t      flags  write-only byte, e.g. K_MSGQ_FLAG_ALLOC

<ground-truth bundle for param_0725>
### cluster param_0725  (param, 2 members, 13 fields, size>=0x34)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: k,z; 1/2 members are LIBRARY-class)

members (2 shown of 2):
  - k_msgq_init @ 0x86420  as param_1  [APPLICATION]
  - z_impl_k_msgq_alloc_init @ 0x86448  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0725 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=w types=int */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=w types=int */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=w types=undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=w types=int */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=w types=int */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=w types=int */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=w types=int */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=w types=int */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=w types=int */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=w types=int */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=w types=int */
    uint8_t    field_0x30;   /* +0x30  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x31[0x3];   /* +0x31 pad */
};
```
