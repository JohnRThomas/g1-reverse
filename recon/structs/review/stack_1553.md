## review group stack_1553  (1 cluster(s), kinds=stack)

### proposal for stack_1553
struct_name: dppi_channel_cfg_entry | is_library: False | library_name:  | is_array: True | confidence: low
purpose: Local DPPI channel/config pair read by dppi_apply_channel_config_table while iterating the channel configuration table.
fields:
  0x0  uint32_t     channel  
  0x8  uint32_t     config  

<ground-truth bundle for stack_1553>
### cluster stack_1553  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_2c in dppi_apply_channel_config_table (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - dppi_apply_channel_config_table @ 0x83ede  as local_2c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1553 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
