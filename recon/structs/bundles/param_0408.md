### cluster param_0408  (param, 3 members, 11 fields, size>=0xf4)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: k; 0/3 members are LIBRARY-class)

members (3 shown of 3):
  - k_work_queue_start @ 0x730e8  as param_1  [APPLICATION]
  - sched_ready_queue_insert @ 0x73840  as param_1  [APPLICATION]
  - sched_thread_ready @ 0x73a78  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0408 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x5];   /* +0x8 pad */
    uint8_t    field_0xd;   /* +0xd  sz=1 rw=rw types=byte,char */
    uint8_t    field_0xe;   /* +0xe  sz=1 rw=r types=char */
    uint8_t    _pad_0xf[0x9];   /* +0xf pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x1c[0xbc];   /* +0x1c pad */
    uint32_t   field_0xd8;   /* +0xd8  sz=4 rw=w types=undefined4 */
    uint32_t   field_0xdc;   /* +0xdc  sz=4 rw=w types=undefined4 */
    uint32_t   field_0xe0;   /* +0xe0  sz=4 rw=w types=int */
    uint32_t   field_0xe4;   /* +0xe4  sz=4 rw=w types=int */
    uint32_t   field_0xe8;   /* +0xe8  sz=4 rw=w types=int */
    uint32_t   field_0xec;   /* +0xec  sz=4 rw=w types=int */
    uint32_t   field_0xf0;   /* +0xf0  sz=4 rw=rw types=uint,undefined4 */
};
```