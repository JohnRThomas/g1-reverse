### cluster param_0716  (param, 12 members, 7 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (12 shown of 12):
  - cbor_finalize_backup_count @ 0x85c26  as param_1  [APPLICATION]
  - zcbor_entry_backup_and_advance @ 0x85c38  as param_1  [APPLICATION]
  - zcbor_backup_store_count @ 0x85d70  as param_1  [APPLICATION]
  - cbor_decode_precheck @ 0x85d82  as param_1  [APPLICATION]
  - cbor_decode_undo_and_fail @ 0x85dc4  as param_1  [APPLICATION]
  - cbor_decode_leave_container @ 0x85df6  as param_1  [APPLICATION]
  - cbor_decode_extract_value @ 0x85e1a  as param_1  [APPLICATION]
  - cbor_decode_length_prefix @ 0x85ebc  as param_1  [APPLICATION]
  - cbor_decode_container_start @ 0x85f06  as param_1  [APPLICATION]
  - cbor_decode_map_start @ 0x85fa2  as param_1  [APPLICATION]
  - cbor_decode_tag @ 0x8603c  as param_1  [APPLICATION]
  - cbor_decode_skip_value @ 0x86064  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0716 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=int */
    uint32_t   field_0x4;   /* +0x4  sz=1,4 rw=rw types=byte,char,idx4,undefined1 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=idx4,int,uint */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    field_0x10;   /* +0x10  sz=1 rw=r types=char */
    uint8_t    field_0x11;   /* +0x11  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x12[0x2];   /* +0x12 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4,int */
};
```