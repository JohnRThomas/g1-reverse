## review group stack_1062  (1 cluster(s), kinds=stack)

### proposal for stack_1062
struct_name: scratch_ctx_0004cf78 | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local scratch aggregate in FUN_0004cf78: a write-only status byte and three later read-only words spread across a large local frame.
fields:
  0x19  uint8_t      field_0x19  write-only byte
  0x3c  int32_t      field_0x3c  read-only idx4
  0x68  int32_t      field_0x68  read-only idx4
  0x6c  int32_t      field_0x6c  read-only idx4

<ground-truth bundle for stack_1062>
### cluster stack_1062  (stack, 1 members, 4 fields, size>=0x70)

Stack-frame local local_24 in FUN_0004cf78 (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - FUN_0004cf78 @ 0x4cf78  as local_24  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1062 {
    uint8_t    _pad_0x0[0x19];   /* +0x0 pad */
    uint8_t    field_0x19;   /* +0x19  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x1a[0x22];   /* +0x1a pad */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x40[0x28];   /* +0x40 pad */
    uint32_t   field_0x68;   /* +0x68  sz=4 rw=r types=idx4 */
    uint32_t   field_0x6c;   /* +0x6c  sz=4 rw=r types=idx4 */
};
```
