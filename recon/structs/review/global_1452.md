## review group global_1452  (1 cluster(s), kinds=global)

### proposal for global_1452
struct_name: cc_crypto_workspace | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Fixed-address crypto dispatch workspace (large 0xa00-byte scratch buffer plus length/status trailer) used by cc_crypto_dispatch_or_error.
fields:
  0xa00  uint32_t     data_len  length of data in workspace buffer, read
  0xa08  uint32_t     status_code  result/error status, write-only

<ground-truth bundle for global_1452>
### cluster global_1452  (global, 1 members, 2 fields, size>=0xa0c)

Global object at fixed address 0x0007a3c8.

library hint: likely G1-original

members (1 shown of 1):
  - cc_crypto_dispatch_or_error @ 0x7a2b8  as 0x0007a3c8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1452 {
    uint8_t    _pad_0x0[0xa00];   /* +0x0 pad */
    uint32_t   field_0xa00;   /* +0xa00  sz=4 rw=r types=uint */
    uint8_t    _pad_0xa04[0x4];   /* +0xa04 pad */
    uint32_t   field_0xa08;   /* +0xa08  sz=4 rw=w types=uint */
};
```
