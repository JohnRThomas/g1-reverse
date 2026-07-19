## review group param_0040  (1 cluster(s), kinds=param)

### proposal for param_0040
struct_name: ble_work_thread_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: BLE background worker thread context wrapping a work-queue/thread state plus a pending-item pointer and trailing status counters.
fields:
  0x10  uint32_t     init_flag  write-only setup flag
  0x18  uint8_t      state  thread/queue state byte
  0x248  uint8_t      done_flag  write-only completion flag
  0x254  void *       pending_item  read-write pointer, likely queued work item
  0x358  uint32_t     counter_a  rw counter/state word
  0x35c  uint32_t     counter_b  rw counter/state word
  0x360  uint32_t     counter_c  rw counter/state word
  0x364  uint8_t      flags  rw flag byte

<ground-truth bundle for param_0040>
### cluster param_0040  (param, 1 members, 8 fields, size>=0x368)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - ble_work_thread @ 0x21da8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0040 {
    uint8_t    _pad_0x0[0x10];   /* +0x0 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x14[0x4];   /* +0x14 pad */
    uint8_t    field_0x18;   /* +0x18  sz=1 rw=r types=undefined1 */
    uint8_t    _pad_0x19[0x22f];   /* +0x19 pad */
    uint8_t    field_0x248;   /* +0x248  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x249[0xb];   /* +0x249 pad */
    void *     field_0x254;   /* +0x254  sz=4 rw=rw types=int,ptr,undefined4 */
    uint8_t    _pad_0x258[0x100];   /* +0x258 pad */
    uint32_t   field_0x358;   /* +0x358  sz=4 rw=rw types=int,uint,undefined4 */
    uint32_t   field_0x35c;   /* +0x35c  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0x360;   /* +0x360  sz=4 rw=rw types=uint,undefined4 */
    uint8_t    field_0x364;   /* +0x364  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0x365[0x3];   /* +0x365 pad */
};
```
