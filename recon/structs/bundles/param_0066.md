### cluster param_0066  (param, 1 members, 9 fields, size>=0x21)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - spi_master_init @ 0x26418  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0066 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=rw types=int,undefined4 */
    uint8_t    field_0x18;   /* +0x18  sz=1 rw=r types=byte,char */
    uint8_t    field_0x19;   /* +0x19  sz=1 rw=r types=byte */
    uint8_t    field_0x1a;   /* +0x1a  sz=1 rw=r types=byte */
    uint8_t    field_0x1b;   /* +0x1b  sz=1 rw=r types=byte */
    uint8_t    field_0x1c;   /* +0x1c  sz=1 rw=r types=byte */
    uint8_t    field_0x1d;   /* +0x1d  sz=1 rw=r types=byte */
    uint8_t    _pad_0x1e[0x3];   /* +0x1e pad */
};
```