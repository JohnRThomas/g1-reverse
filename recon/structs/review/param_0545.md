## review group param_0545  (1 cluster(s), kinds=param)

### proposal for param_0545
struct_name: aes_state_matrix | is_library: True | library_name: AES state[16] / round-key array (mbedTLS or CryptoCell AES implementation) | is_array: True | confidence: medium
purpose: AES 128-bit state block accessed by add_round_key both as a run of 32-bit words and overlapping smaller reads — the classic 4x4 byte state matrix used during AddRoundKey.
fields:
  0x2  uint16_t     state_word_0_hi  overlapping short read of state array
  0x4  uint32_t     state_word_1  idx4
  0x8  uint32_t     state_word_2  idx4
  0xc  uint32_t     state_word_3  idx4

<ground-truth bundle for param_0545>
### cluster param_0545  (param, 1 members, 11 fields, size>=0x13)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - add_round_key @ 0x7feda  as param_2  [LIBRARY]

layout notes: 0x2: access width 2 exceeds gap 1 to next field (overlap/union); 0x4: access width 4 exceeds gap 2 to next field (overlap/union); 0x6: access width 2 exceeds gap 1 to next field (overlap/union); 0x8: access width 4 exceeds gap 2 to next field (overlap/union); 0xa: access width 2 exceeds gap 1 to next field (overlap/union); 0xc: access width 4 exceeds gap 2 to next field (overlap/union); 0xe: access width 2 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0545 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint8_t    field_0x2;   /* +0x2  sz=2 rw=r types=undefined2 */
    uint8_t    field_0x3;   /* +0x3  sz=1 rw=r types=byte */
    uint16_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    field_0x6;   /* +0x6  sz=2 rw=r types=undefined2 */
    uint8_t    field_0x7;   /* +0x7  sz=1 rw=r types=byte */
    uint16_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    field_0xa;   /* +0xa  sz=2 rw=r types=undefined2 */
    uint8_t    field_0xb;   /* +0xb  sz=1 rw=r types=byte */
    uint16_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    field_0xe;   /* +0xe  sz=2 rw=r types=undefined2 */
    uint8_t    field_0xf;   /* +0xf  sz=1 rw=r types=byte */
    uint8_t    _pad_0x10[0x3];   /* +0x10 pad */
};
```
