## review group param_0549  (1 cluster(s), kinds=param)

### proposal for param_0549
struct_name: matrix_row_desc | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Row/column descriptor read by mult_row_column_0 during matrix multiplication: three word fields likely stride/length/data-pointer for a matrix row.
fields:
  0x4  uint32_t     field_a  
  0x8  uint32_t     field_b  
  0xc  uint32_t     field_c  

<ground-truth bundle for param_0549>
### cluster param_0549  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - mult_row_column_0 @ 0x7ffd6  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0549 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
