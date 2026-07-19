## review group global_1484  (1 cluster(s), kinds=global)

### proposal for global_1484
struct_name: aes_drv_ctx | is_library: True | library_name: nrf_cc3xx / CRYS AES driver context (best guess) | is_array: None | confidence: low
purpose: Large fixed global (>=0x814 bytes) representing an AES hardware-driver / CryptoCell context; FinishAesDrv reads status/config near the front and writes completion flags near the end.
fields:
  0x440  uint32_t     field_0x440  read, status/config
  0x460  uint32_t     field_0x460  read
  0x47c  uint32_t     field_0x47c  write, completion flag
  0x810  uint32_t     field_0x810  write, completion flag

<ground-truth bundle for global_1484>
### cluster global_1484  (global, 1 members, 4 fields, size>=0x814)

Global object at fixed address 0x0007bbb0.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - FinishAesDrv @ 0x7b9cc  as 0x0007bbb0  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1484 {
    uint8_t    _pad_0x0[0x440];   /* +0x0 pad */
    uint32_t   field_0x440;   /* +0x440  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x444[0x1c];   /* +0x444 pad */
    uint32_t   field_0x460;   /* +0x460  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x464[0x18];   /* +0x464 pad */
    uint32_t   field_0x47c;   /* +0x47c  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x480[0x390];   /* +0x480 pad */
    uint32_t   field_0x810;   /* +0x810  sz=4 rw=w types=undefined4 */
};
```
