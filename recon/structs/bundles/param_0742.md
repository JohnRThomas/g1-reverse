### cluster param_0742  (param, 1 members, 2 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - libc_stream_write_syscall @ 0x86f5a  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0742 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint16_t   field_0xc;   /* +0xc  sz=2 rw=rw types=ushort */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=r types=short */
};
```