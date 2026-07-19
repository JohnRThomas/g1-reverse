## review group param_0299  (1 cluster(s), kinds=param)

### proposal for param_0299
struct_name: periph_drv_data | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Cluster likely conflates distinct QSPI-NOR and I2S driver instance-data structs that happen to share the same parameter position; treat as generic per-driver runtime data (semaphore/ready flags/counters)
fields:
  0x4  int32_t      state_or_flag  r
  0x10  int32_t      field_a  r
  0x14  int32_t      field_b  r

<ground-truth bundle for param_0299>
### cluster param_0299  (param, 9 members, 3 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (9 shown of 9):
  - qspi_nor_acquire @ 0x60a10  as param_1  [APPLICATION]
  - qspi_nor_suspend_bus @ 0x60a5c  as param_1  [APPLICATION]
  - qspi_nor_pm_action @ 0x60b48  as param_1  [APPLICATION]
  - qspi_nor_configure @ 0x60c00  as param_1  [APPLICATION]
  - qspi_nor_erase @ 0x60dd0  as param_1  [APPLICATION]
  - qspi_nor_write @ 0x60f20  as param_1  [APPLICATION]
  - storage_read_with_word_cache @ 0x61070  as param_1  [APPLICATION]
  - audio_i2s_stop_and_reset_channels @ 0x83906  as param_1  [APPLICATION]
  - audio_i2s_start_channels @ 0x8392e  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0299 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int,undefined4 */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int,undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=int */
};
```
