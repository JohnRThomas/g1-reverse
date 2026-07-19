## review group param_0367  (1 cluster(s), kinds=param)

### proposal for param_0367
struct_name: lc3_bits_state | is_library: True | library_name: lc3 bits_state (bit I/O context) | is_array: False | confidence: medium
purpose: LC3 codec bit-accumulator/writer state used by lc3_flush_bits: accumulator, bit counts, position pointers and buffer pointers.
fields:
  0x4  uint32_t     accumulator  
  0x8  uint32_t     nbits_acc  
  0xc  uint32_t     position  
  0x10  uint32_t     nbits_out  
  0x14  uint32_t     overflow_flag  
  0x1c  uint32_t     buf_start_offset  
  0x20  int          buf_len  
  0x2c  void *       buf_ptr  
  0x30  void *       buf_end_ptr  
  0x34  int          nbytes  

<ground-truth bundle for param_0367>
### cluster param_0367  (param, 1 members, 10 fields, size>=0x38)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_flush_bits @ 0x685f4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0367 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=rw types=uint */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=uint */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=int,uint,undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=rw types=int,undefined4 */
    uint8_t    _pad_0x18[0x4];   /* +0x18 pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=rw types=uint,undefined4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=rw types=int */
    uint8_t    _pad_0x24[0x8];   /* +0x24 pad */
    void *     field_0x2c;   /* +0x2c  sz=4 rw=r types=ptr */
    void *     field_0x30;   /* +0x30  sz=4 rw=rw types=ptr */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=rw types=int */
};
```
