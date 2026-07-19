## review group global_1096  (1 cluster(s), kinds=global)

### proposal for global_1096
struct_name: app_event_header | is_library: True | library_name: app_event_manager: struct app_event_header (nRF Connect SDK CAF) | is_array: None | confidence: low
purpose: Event header passed to app_event_manager_submit (nRF Connect SDK Application Event Manager) identifying the event type/subscriber index.
fields:
  0x0  uint32_t     type_id  event type identifier, read-only
  0x4  uint32_t     field_0x4  index-typed field, possibly subscriber/listener slot

<ground-truth bundle for global_1096>
### cluster global_1096  (global, 1 members, 2 fields, size>=0x8)

Global object at fixed address 0x0004f850.

library hint: likely G1-original

members (1 shown of 1):
  - app_event_manager_submit @ 0x4f770  as 0x0004f850  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1096 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
