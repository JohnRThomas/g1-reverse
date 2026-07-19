### cluster stack_1042  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_40 in proxy_thread_handler (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - proxy_thread_handler @ 0x47c48  as local_40  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1042 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```