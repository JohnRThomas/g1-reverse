### cluster stack_0900  (stack, 1 members, 2 fields, size>=0x6)

Stack-frame local local_24 in ipc_send_len_prefixed_packet (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - ipc_send_len_prefixed_packet @ 0x25740  as local_24  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0900 {
    uint16_t   field_0x0;   /* +0x0  sz=2 rw=r types=idx2 */
    uint8_t    _pad_0x2[0x2];   /* +0x2 pad */
    uint16_t   field_0x4;   /* +0x4  sz=2 rw=r types=idx2 */
};
```