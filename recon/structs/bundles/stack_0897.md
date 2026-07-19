### cluster stack_0897  (stack, 1 members, 8 fields, size>=0x58)

Stack-frame local local_6c in st25dv_build_and_write_ndef_records (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - st25dv_build_and_write_ndef_records @ 0x250f8  as local_6c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0897 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x1c[0x38];   /* +0x1c pad */
    uint32_t   field_0x54;   /* +0x54  sz=4 rw=r types=idx4 */
};
```