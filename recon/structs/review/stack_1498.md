## review group stack_1498  (1 cluster(s), kinds=stack)

### proposal for stack_1498
struct_name: spi_chunk_state | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Local chunk-index/flag pair used while writing SPI data to the projector display in chunks.
fields:
  0x0  uint8_t      chunk_idx  
  0x8  uint8_t      chunk_flag  

<ground-truth bundle for stack_1498>
### cluster stack_1498  (stack, 1 members, 2 fields, size>=0x9)

Stack-frame local local_24 in projector_spi_write_chunked (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - projector_spi_write_chunked @ 0x7d7b6  as local_24  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1498 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x7];   /* +0x1 pad */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=r types=idx1 */
};
```
