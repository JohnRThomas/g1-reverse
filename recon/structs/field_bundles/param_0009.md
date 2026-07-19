### struct array_scan_bounds  (G1-original)  cid=param_0009

purpose: Pointer arg to array_max_skip_nan_a; two index/length fields describing an array scan (bounds or accumulator).

This object is accessed by these functions (read their fully-named source):
  - array_max_skip_nan_a  (as param_1)  ->  recon/readable_sources/app/g1/array_max_skip_nan_a.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct array_scan_bounds {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```