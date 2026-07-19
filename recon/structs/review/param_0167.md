## review group param_0167  (1 cluster(s), kinds=param)

### proposal for param_0167
struct_name: kernel_obj_or_thread_merged | is_library: True | library_name: k_thread (probable, cluster likely merges multiple distinct Zephyr kernel structs sharing a param slot) | is_array: None | confidence: low
purpose: Heterogeneous cluster: same parameter slot is shared by unrelated Zephyr kernel objects (k_mutex/k_sem/k_msgq via _wait_q_t fields at low offsets, and k_thread stack/entry info via fields at 0x50-0xd4 accessed by arch_new_thread/z_setup_new_thread). Treat as an approximate k_thread layout; low-offset fields likely belong to embedded sync primitives instead.
fields:
  0x8  uint32_t     field_0x8  list/waitq node
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x18  void *       field_0x18  
  0x1c  uint32_t     field_0x1c  
  0x20  uint32_t     field_0x20  
  0x24  uint32_t     field_0x24  
  0x50  uint32_t     field_0x50  thread entry/stack info region begins
  0x54  uint32_t     field_0x54  
  0x58  uint32_t     field_0x58  
  0x5c  uint32_t     field_0x5c  
  0x70  uint8_t      field_0x70  
  0x74  uint32_t     field_0x74  
  0x7c  uint32_t     field_0x7c  
  0x80  uint32_t     field_0x80  
  0x84  uint32_t     field_0x84  
  0x88  uint32_t     field_0x88  
  0x8c  uint32_t     field_0x8c  
  0xd4  uint32_t     field_0xd4  

<ground-truth bundle for param_0167>
### cluster param_0167  (param, 11 members, 23 fields, size>=0xd8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt,k,z; 0/11 members are LIBRARY-class)

members (11 shown of 11):
  - arch_new_thread @ 0x502c4  as param_1  [APPLICATION]
  - bt_gatt_discover @ 0x5b9cc  as param_1  [APPLICATION]
  - bt_gatt_write @ 0x5c22c  as param_1  [APPLICATION]
  - k_mem_slab_alloc @ 0x71c20  as param_1  [APPLICATION]
  - z_setup_new_thread @ 0x71df8  as param_1  [APPLICATION]
  - k_msgq_put @ 0x720d0  as param_1  [APPLICATION]
  - k_msgq_get @ 0x72240  as param_1  [APPLICATION]
  - k_mutex_lock @ 0x723b8  as param_1  [APPLICATION]
  - k_mutex_unlock @ 0x72558  as param_1  [APPLICATION]
  - k_sem_give @ 0x72880  as param_1  [APPLICATION]
  - z_impl_k_sem_take @ 0x72908  as param_1  [APPLICATION]

layout notes: 0xc: access width 4 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0167 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=idx4,int,undefined4 */
    uint8_t    field_0xc;   /* +0xc  sz=1,4 rw=rw types=idx4,int,undefined1,undefined4 */
    uint8_t    field_0xd;   /* +0xd  sz=1 rw=rw types=char,undefined1 */
    uint8_t    field_0xe;   /* +0xe  sz=1 rw=w types=char */
    uint8_t    field_0xf;   /* +0xf  sz=1 rw=w types=undefined1 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=idx4,int,uint,undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=int,uint */
    void *     field_0x18;   /* +0x18  sz=4 rw=rw types=int,ptr,uint,undefined4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=rw types=int,uint */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=rw types=int,uint */
    uint8_t    _pad_0x28[0x28];   /* +0x28 pad */
    uint32_t   field_0x50;   /* +0x50  sz=4 rw=w types=int */
    uint32_t   field_0x54;   /* +0x54  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x58;   /* +0x58  sz=4 rw=w types=int */
    uint32_t   field_0x5c;   /* +0x5c  sz=4 rw=w types=int */
    uint8_t    _pad_0x60[0x10];   /* +0x60 pad */
    uint8_t    field_0x70;   /* +0x70  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x71[0x3];   /* +0x71 pad */
    uint32_t   field_0x74;   /* +0x74  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x78[0x4];   /* +0x78 pad */
    uint32_t   field_0x7c;   /* +0x7c  sz=4 rw=w types=int */
    uint32_t   field_0x80;   /* +0x80  sz=4 rw=w types=uint */
    uint32_t   field_0x84;   /* +0x84  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x88;   /* +0x88  sz=4 rw=w types=int */
    uint32_t   field_0x8c;   /* +0x8c  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x90[0x44];   /* +0x90 pad */
    uint32_t   field_0xd4;   /* +0xd4  sz=4 rw=w types=undefined4 */
};
```
