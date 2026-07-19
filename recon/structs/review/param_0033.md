## review group param_0033  (5 cluster(s), kinds=param)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for param_0033
struct_name: bt_addr_format_ctx | is_library: False | library_name:  | is_array: True | confidence: low
purpose: Object passed to format_bt_addr_str; accessed as a uniform array of six 32-bit index/word fields, likely an address-byte buffer treated word-wise or a small formatting scratch struct
fields:
  0x4  uint32_t     word_0  
  0x8  uint32_t     word_1  
  0xc  uint32_t     word_2  
  0x10  uint32_t     word_3  
  0x14  uint32_t     word_4  
  0x18  uint32_t     word_5  

<ground-truth bundle for param_0033>
### cluster param_0033  (param, 1 members, 6 fields, size>=0x1c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - format_bt_addr_str @ 0x18334  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0033 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0183
struct_name: bt_addr_str_scratch | is_library: False | library_name:  | is_array: True | confidence: low
purpose: Scratch/format buffer accessed word-wise by bt_addr_le_str while stringifying a Bluetooth LE address.
fields:
  0x4  uint32_t     word_0  array element
  0x8  uint32_t     word_1  array element
  0xc  uint32_t     word_2  array element
  0x10  uint32_t     word_3  array element
  0x14  uint32_t     word_4  array element
  0x18  uint32_t     word_5  array element

<ground-truth bundle for param_0183>
### cluster param_0183  (param, 1 members, 6 fields, size>=0x1c)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_addr_le_str @ 0x52cdc  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0183 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0184
struct_name: bt_settings_key_ctx | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Context describing a Bluetooth identity/key used when encoding a settings storage key (bt_settings_encode_key); several idx4 fields likely correspond to id, address bytes, and key type.
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x18  uint32_t     field_0x18  

<ground-truth bundle for param_0184>
### cluster param_0184  (param, 1 members, 6 fields, size>=0x1c)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_settings_encode_key @ 0x52e7c  as param_4  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0184 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0519
struct_name: sector_cb_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Flash/storage sector-enumeration callback context passed to get_sectors_cb, carrying sector geometry values (offset, count, size, etc.).
fields:
  0x4  uint32_t     sector_count  read-only uint
  0x8  uint32_t     sector_offset  read-only int
  0xc  uint32_t     sector_size  read-only int
  0x10  uint32_t     cursor  rw int/uint
  0x14  uint32_t     limit  read-only uint
  0x18  uint32_t     result  write-only

<ground-truth bundle for param_0519>
### cluster param_0519  (param, 1 members, 6 fields, size>=0x1c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - get_sectors_cb @ 0x7f020  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0519 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=uint */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=int */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=int,uint */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=uint */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=w types=undefined4 */
};
```

### proposal for param_0730
struct_name: k_queue | is_library: True | library_name: struct k_queue | is_array: False | confidence: medium
purpose: Zephyr k_queue kernel object initialized by z_impl_k_queue_init: internal sflist head/tail, poll-event list, and spinlock/flag words.
fields:
  0x4  uint32_t     data_q_head  
  0x8  uint32_t     data_q_tail  
  0xc  uint32_t     lock  
  0x10  uint32_t     poll_events_head  
  0x14  uint32_t     poll_events_tail  
  0x18  uint32_t     flags  

<ground-truth bundle for param_0730>
### cluster param_0730  (param, 1 members, 6 fields, size>=0x1c)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: z; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - z_impl_k_queue_init @ 0x864e8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0730 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
};
```
