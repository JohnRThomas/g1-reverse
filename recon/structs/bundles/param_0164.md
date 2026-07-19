### cluster param_0164  (param, 11 members, 21 fields, size>=0x134)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: tc; 10/11 members are LIBRARY-class)

members (11 shown of 11):
  - tc_sha256_compress_block @ 0x4fadc  as param_1  [APPLICATION]
  - tc_sha256_init @ 0x4fca0  as param_1  [LIBRARY]
  - tc_cmac_init @ 0x8013e  as param_1  [LIBRARY]
  - tc_cmac_setup @ 0x8016a  as param_1  [LIBRARY]
  - tc_cmac_update @ 0x801c0  as param_1  [LIBRARY]
  - tc_cmac_final @ 0x80294  as param_2  [LIBRARY]
  - tc_sha256_update @ 0x80300  as param_1  [LIBRARY]
  - tc_sha256_final @ 0x8034c  as param_2  [LIBRARY]
  - tc_hmac_prng_init @ 0x80652  as param_1  [LIBRARY]
  - tc_hmac_prng_generate @ 0x806c4  as param_3  [LIBRARY]
  - gen_hash_m @ 0x8260c  as param_3  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0164 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=rw types=uint */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=rw types=int,uint,undefined4 */
    uint8_t    _pad_0x28[0x1c];   /* +0x28 pad */
    uint32_t   field_0x44;   /* +0x44  sz=4 rw=rw types=int,uint,undefined4 */
    uint32_t   field_0x48;   /* +0x48  sz=4 rw=rw types=undefined4 */
    uint8_t    _pad_0x4c[0x4];   /* +0x4c pad */
    uint32_t   field_0x50;   /* +0x50  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0x54;   /* +0x54  sz=4 rw=rw types=int,uint,undefined4 */
    uint32_t   field_0x58;   /* +0x58  sz=4 rw=w types=int */
    uint8_t    _pad_0x5c[0x4];   /* +0x5c pad */
    uint8_t    field_0x60;   /* +0x60  sz=1 rw=w types=char */
    uint8_t    field_0x61;   /* +0x61  sz=1 rw=w types=char */
    uint8_t    field_0x62;   /* +0x62  sz=1 rw=w types=char */
    uint8_t    field_0x63;   /* +0x63  sz=1 rw=w types=char */
    uint32_t   field_0x64;   /* +0x64  sz=4 rw=w types=uint */
    uint32_t   field_0x68;   /* +0x68  sz=4 rw=rw types=int,uint,undefined4 */
    uint8_t    _pad_0x6c[0xc4];   /* +0x6c pad */
    uint32_t   field_0x130;   /* +0x130  sz=4 rw=rw types=int,undefined4 */
};
```