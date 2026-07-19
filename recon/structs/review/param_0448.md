## review group param_0448  (1 cluster(s), kinds=param)

### proposal for param_0448
struct_name: sha_hash_context | is_library: True | library_name: mbedtls_sha256_context | is_array: None | confidence: medium
purpose: SHA hashing context shared by mbedtls_sha_finish_internal/mbedtls_sha_update_internal/ProcessHashDrv: bit-count word, 8-word chaining state (SHA-256 shaped), message buffer, and trailing length/flag fields.
fields:
  0x4  uint32_t     total_hi  rw, bit-count word
  0x8  uint32_t     state_0  read as idx4
  0xc  uint32_t     state_1  read as idx4
  0x10  uint32_t     state_2  read as idx4
  0x14  uint32_t     state_3  read as idx4
  0x18  uint32_t     state_4  read as idx4
  0x1c  uint32_t     state_5  read as idx4
  0x20  uint32_t     state_6  read as idx4
  0x24  uint32_t     state_7  read as idx4
  0x48  uint32_t     buffer_word_a  read, within message buffer region
  0x4c  uint32_t     buffer_word_b  read, within message buffer region
  0x5c  uint32_t     msg_len  read, trailing length field
  0x60  uint32_t     process_flag  rw, trailing status/flag field

<ground-truth bundle for param_0448>
### cluster param_0448  (param, 3 members, 13 fields, size>=0x64)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: mbedtls; 3/3 members are LIBRARY-class)

members (3 shown of 3):
  - mbedtls_sha_finish_internal @ 0x7ace0  as param_1  [LIBRARY]
  - mbedtls_sha_update_internal @ 0x7ad3c  as param_1  [LIBRARY]
  - ProcessHashDrv @ 0x7b1e4  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0448 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=rw types=idx4,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x28[0x20];   /* +0x28 pad */
    uint32_t   field_0x48;   /* +0x48  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4c;   /* +0x4c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x50[0xc];   /* +0x50 pad */
    uint32_t   field_0x5c;   /* +0x5c  sz=4 rw=r types=uint,undefined4 */
    uint32_t   field_0x60;   /* +0x60  sz=4 rw=rw types=int,uint,undefined4 */
};
```
