## review group global_0968  (2 cluster(s), kinds=global)

These clusters share an IDENTICAL Ghidra footprint signature — very likely the SAME type. Merge them into one canonical struct.

### proposal for global_0968
struct_name: resend_pending_msg_state | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Global state tracking a pending BLE message queued for resend
fields:
  0x114  uint8_t      field_0x114  write-only flag, possibly resend-pending flag
  0x115  uint8_t      field_0x115  
  0x116  char         field_0x116  
  0x118  uint8_t      field_0x118  

<ground-truth bundle for global_0968>
### cluster global_0968  (global, 1 members, 4 fields, size>=0x119)

Global object at fixed address 0x00033bbc.

library hint: likely G1-original

members (1 shown of 1):
  - stage_pending_message_for_resend @ 0x33b88  as 0x00033bbc  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0968 {
    uint8_t    _pad_0x0[0x114];   /* +0x0 pad */
    uint8_t    field_0x114;   /* +0x114  sz=1 rw=w types=undefined1 */
    uint8_t    field_0x115;   /* +0x115  sz=1 rw=r types=byte */
    uint8_t    field_0x116;   /* +0x116  sz=1 rw=r types=char */
    uint8_t    _pad_0x117[0x1];   /* +0x117 pad */
    uint8_t    field_0x118;   /* +0x118  sz=1 rw=r types=byte */
};
```

### proposal for global_0969
struct_name: pt_queue_state | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Pointer/task queue control block; tail fields track free-slot bookkeeping for a queue of pointer entries.
fields:
  0x114  uint8_t      field_0x114  written; likely queue write index or count
  0x115  uint8_t      field_0x115  read byte flag
  0x116  uint8_t      field_0x116  read char/flag
  0x118  uint8_t      field_0x118  read byte flag

<ground-truth bundle for global_0969>
### cluster global_0969  (global, 1 members, 4 fields, size>=0x119)

Global object at fixed address 0x00033bec.

library hint: likely G1-original

members (1 shown of 1):
  - pt_queue_get_free_slot @ 0x33bc4  as 0x00033bec  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_0969 {
    uint8_t    _pad_0x0[0x114];   /* +0x0 pad */
    uint8_t    field_0x114;   /* +0x114  sz=1 rw=w types=undefined1 */
    uint8_t    field_0x115;   /* +0x115  sz=1 rw=r types=byte */
    uint8_t    field_0x116;   /* +0x116  sz=1 rw=r types=char */
    uint8_t    _pad_0x117[0x1];   /* +0x117 pad */
    uint8_t    field_0x118;   /* +0x118  sz=1 rw=r types=byte */
};
```
