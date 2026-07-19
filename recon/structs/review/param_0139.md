## review group param_0139  (1 cluster(s), kinds=param)

### proposal for param_0139
struct_name: unk_ctx_0139 | is_library: False | library_name:  | is_array: False | confidence: low
purpose: G1-original object with a pointer and dword near end of a 0x1b0-byte structure, used by unnamed FUN_0004cce0.
fields:
  0x1a8  void *       field_0x1a8  
  0x1ac  uint32_t     field_0x1ac  

<ground-truth bundle for param_0139>
### cluster param_0139  (param, 1 members, 2 fields, size>=0x1b0)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - FUN_0004cce0 @ 0x4cce0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0139 {
    uint8_t    _pad_0x0[0x1a8];   /* +0x0 pad */
    void *     field_0x1a8;   /* +0x1a8  sz=4 rw=r types=ptr */
    uint32_t   field_0x1ac;   /* +0x1ac  sz=4 rw=r types=undefined4 */
};
```
