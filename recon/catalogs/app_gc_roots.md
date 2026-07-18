# CPUAPP section-GC root receipt

Normal section GC is authorized by the binary-derived root inventory. Only named recovered definitions are passed to the linker; numeric firmware addresses are never forced as roots.

- Named roots: **16**
- Unresolved candidates: **3**
- Complete recovered root graph: **no**

| Thread | Firmware candidate | Link symbol | State |
|---|---:|---|---|
| `main` | `0x00016eb8` | `main` | named root |
| `ancs` | `0x00019718` | `FUN_00019718` | named root |
| `ble_projector` | `0x00021da8` | `ble_work_thread` | named root |
| `flash` | `0x00023480` | `flash_ops_thread` | named root |
| `brightness` | `0x00023844` | `brightness_level` | named root |
| `run_main_a` | `0x0002a8d8` | `low_speed_peripheral_dispatch_thread` | named root |
| `run_main_a` | `0x0002685c` | `FUN_0002685c` | named root |
| `run_main_b` | `0x000286f8` | `process_task_sync_event` | named root |
| `run_main_c` | `0x0002a4f4` | `FUN_0002a4f4` | named root |
| `run_main_d` | `0x00028bec` | `display_dispatch_thread` | named root |
| `run_main_e` | `0x0002692c` | — | unresolved; not forced |
| `run_main_f` | `0x00027cfc` | — | unresolved; not forced |
| `run_main_g` | `0x0002a0d8` | `touch_key_thread` | named root |
| `run_main_g` | `0x00028a1c` | `click_event_dispatch_loop` | named root |
| `run_main_h` | `0x0002955c` | `key_event_thread` | named root |
| `aging_a` | `0x00032420` | — | unresolved; not forced |
| `aging_b` | `0x000324bc` | `FUN_000324bc` | named root |
| `proxy` | `0x00047c48` | `proxy_thread_handler` | named root |
| `display` | `0x00049090` | `display_thread_handler` | named root |
