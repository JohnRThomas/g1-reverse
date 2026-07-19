### cluster stack_1097  (stack, 1 members, 5 fields, size>=0x14)

Stack-frame local local_44 in tc_aes128_set_encrypt_key (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: tc; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - tc_aes128_set_encrypt_key @ 0x4fa34  as local_44  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1097 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```