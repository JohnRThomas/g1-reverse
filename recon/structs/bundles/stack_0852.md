### cluster stack_0852  (stack, 1 members, 2 fields, size>=0x11)

Stack-frame local local_b0 in ble_process_req_dispatch (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - ble_process_req_dispatch @ 0x21460  as local_b0  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0852 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0xf];   /* +0x1 pad */
    uint8_t    field_0x10;   /* +0x10  sz=1 rw=r types=idx1 */
};
```