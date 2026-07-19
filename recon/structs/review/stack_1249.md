## review group stack_1249  (1 cluster(s), kinds=stack)

### proposal for stack_1249
struct_name: smp_pairing_pdu_local | is_library: True | library_name: bt_smp_pairing (partial) | is_array: None | confidence: low
purpose: Stack-local partial view of a Bluetooth SMP pairing-request PDU in smp_pairing_req: io_capability byte at offset 0 and a trailing key-distribution/reserved word at offset 0x10.
fields:
  0x0  uint8_t      io_capability  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for stack_1249>
### cluster stack_1249  (stack, 1 members, 2 fields, size>=0x14)

Stack-frame local local_38 in smp_pairing_req (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: smp; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - smp_pairing_req @ 0x5d5c0  as local_38  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1249 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0xc];   /* +0x4 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```
