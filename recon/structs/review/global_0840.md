## review group global_0840  (8 cluster(s), kinds=global,param)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for global_0840
struct_name: bt_start_ctx_table | is_library: True | library_name: bt_dev (fragment) | is_array: True | confidence: low
purpose: Small consecutive-uint32 table read by bt_start(); likely a Bluetooth controller init parameter/index table rather than a heterogeneous record.
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for global_0840>
### cluster global_0840  (global, 1 members, 4 fields, size>=0x14)

Global object at fixed address 0x00019650.

library hint: LIKELY LIBRARY (prefixes: bt; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_start @ 0x19308  as 0x00019650  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0840 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0086
struct_name: flash_blob_write_req | is_library: False | library_name:  | is_array: False | confidence: medium
purpose: Descriptor passed to flash_write_and_verify_blob: source pointer, length, and a secondary pointer, describing a blob to write+verify to flash.
fields:
  0x4  void *       src_ptr  source data pointer
  0x8  uint32_t     length  blob length
  0xc  uint16_t     flags_or_id  overlapping int/ushort access
  0x10  void *       dest_ptr  destination pointer or verify buffer

<ground-truth bundle for param_0086>
### cluster param_0086  (param, 1 members, 4 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - flash_write_and_verify_blob @ 0x30528  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0086 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=2,4 rw=r types=int,ushort */
    void *     field_0x10;   /* +0x10  sz=4 rw=r types=int,ptr */
};
```

### proposal for param_0132
struct_name: mpsc_pbuf_buffer | is_library: True | library_name: mpsc_pbuf_buffer (Zephyr sys/mpsc_pbuf.h) | is_array: None | confidence: medium
purpose: Zephyr mpsc_pbuf (multi-producer single-consumer packet buffer) instance initialized by mpsc_pbuf_init: buffer pointer/size and read/write index bookkeeping.
fields:
  0x4  uint32_t     buf  
  0x8  uint32_t     size  
  0xc  uint32_t     wr_idx  
  0x10  uint32_t     rd_idx  

<ground-truth bundle for param_0132>
### cluster param_0132  (param, 1 members, 4 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - mpsc_pbuf_init @ 0x4bc28  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0132 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0200
struct_name: ble_conn_addr_params | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Small struct read by ble_conn_addr_and_params_valid to validate a BLE peer's address and connection parameters (type/value plus a validity/role code).
fields:
  0x4  uint32_t     addr_type_or_id  
  0x8  uint32_t     addr_val_hi  
  0xc  uint32_t     addr_val_lo  
  0x10  int32_t      role_or_status  

<ground-truth bundle for param_0200>
### cluster param_0200  (param, 1 members, 4 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - ble_conn_addr_and_params_valid @ 0x55614  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0200 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=uint */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=uint */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
};
```

### proposal for param_0353
struct_name: nrfx_twim_xfer_desc | is_library: True | library_name: nrfx_twim_xfer_desc_t | is_array: None | confidence: high
purpose: nrfx TWI(M) transfer descriptor passed to nrfx_twim_xfer
fields:
  0x4  uint32_t     type  transfer type
  0x8  uint32_t     address  primary buffer/address ptr
  0xc  uint32_t     primary_length  length
  0x10  uint32_t     secondary_length  secondary length

<ground-truth bundle for param_0353>
### cluster param_0353  (param, 1 members, 4 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_twim_xfer @ 0x67938  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0353 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4,int,uint,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=uint,undefined4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=uint,undefined4 */
};
```

### proposal for param_0437
struct_name: deferred_call_pair | is_library: False | library_name:  | is_array: None | confidence: low
purpose: G1-original deferred-call/work pairing structure set up by setup_deferred_call_pair, holding four related handles/pointers (callback + arg + linkage).
fields:
  0x4  uint32_t     handle_a  read-only idx4
  0x8  uint32_t     handle_b  read-only idx4
  0xc  uint32_t     handle_c  read-only idx4
  0x10  uint32_t     handle_d  read-only idx4

<ground-truth bundle for param_0437>
### cluster param_0437  (param, 1 members, 4 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - setup_deferred_call_pair @ 0x79780  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0437 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0485
struct_name: countdown_timer_state | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Countdown/reset timer state block reset by reset_countdown_timer_default (a run of four uint32 counters/thresholds).
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for param_0485>
### cluster param_0485  (param, 1 members, 4 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - reset_countdown_timer_default @ 0x7d1b8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0485 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```

### proposal for param_0513
struct_name: status_byte_packet_ctx | is_library: False | library_name:  | is_array: False | confidence: low
purpose: G1-original status-byte packet building context used by build_status_byte_packet.
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for param_0513>
### cluster param_0513  (param, 1 members, 4 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - build_status_byte_packet @ 0x7ef04  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0513 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```
