## review group global_1483  (1 cluster(s), kinds=global)

### proposal for global_1483
struct_name: cc3xx_aes_drv_ctx | is_library: True | library_name: nrf_cc3xx (CryptoCell AES driver) | is_array: None | confidence: low
purpose: CryptoCell/CC3xx hardware AES driver context/register shadow used by ProcessAesDrv; large struct with a handful of hot fields controlling AES HW operation.
fields:
  0x400  uint32_t     field_0x400  write, likely operation mode/control
  0x440  uint32_t     field_0x440  read, likely status
  0x460  uint32_t     field_0x460  read
  0x810  uint32_t     field_0x810  write
  0xb0c  uint32_t     field_0xb0c  write, uint
  0xc28  uint32_t     field_0xc28  write, tail field

<ground-truth bundle for global_1483>
### cluster global_1483  (global, 1 members, 6 fields, size>=0xc2c)

Global object at fixed address 0x0007b9a8.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - ProcessAesDrv @ 0x7b694  as 0x0007b9a8  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1483 {
    uint8_t    _pad_0x0[0x400];   /* +0x0 pad */
    uint32_t   field_0x400;   /* +0x400  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x404[0x3c];   /* +0x404 pad */
    uint32_t   field_0x440;   /* +0x440  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x444[0x1c];   /* +0x444 pad */
    uint32_t   field_0x460;   /* +0x460  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x464[0x3ac];   /* +0x464 pad */
    uint32_t   field_0x810;   /* +0x810  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x814[0x2f8];   /* +0x814 pad */
    uint32_t   field_0xb0c;   /* +0xb0c  sz=4 rw=w types=uint */
    uint8_t    _pad_0xb10[0x118];   /* +0xb10 pad */
    uint32_t   field_0xc28;   /* +0xc28  sz=4 rw=w types=undefined4 */
};
```
