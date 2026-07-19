## review group param_0087  (1 cluster(s), kinds=param)

### proposal for param_0087
struct_name: nfc_eeprom_link_cfg | is_library: False | library_name:  | is_array: None | confidence: low
purpose: NFC EEPROM link configuration descriptor consumed by pt_nfc_eeprom_link_init (base address / size / offset triple).
fields:
  0x4  uint32_t     base_addr  read as idx4
  0x8  uint32_t     length  read as idx4
  0xc  uint32_t     offset  read as idx4

<ground-truth bundle for param_0087>
### cluster param_0087  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - pt_nfc_eeprom_link_init @ 0x30b3c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0087 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
