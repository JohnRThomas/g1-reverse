# CPUNET IPC/OpenAMP/libmetal stock adoption

All four selected functions match their configured NCS 2.5.1 object sections; only call relocations are masked, and every one resolves into the proven helper closure.

| Address | Raw back-map | Stock identity | Owner | Match |
|---|---|---|---|---|
| `0x010353ec` | `FUN_010353ec` | `virtqueue_add_consumed_buffer` | openamp | raw exact |
| `0x0103ab0e` | `FUN_0103ab0e` | `metal_io_block_write` | libmetal | raw exact |
| `0x0103ac50` | `FUN_0103ac50` | `virtqueue_get_available_buffer` | openamp | relocation-masked exact |
| `0x0103a056` | `FUN_0103a056` | `ipc_static_vrings_shm_size` | zephyr | raw exact |

The static-vrings symbol is the compiler-emitted `.text.shm_size` helper; `ipc_static_vrings_shm_size` is its collision-safe durable name.

Version precision: OpenAMP `42b7c577714b8f22ce82a901e19c1814af4609a8` and libmetal `b91611a6f47dd29fb24c46e5621e797557f80ec6` are the exact manifest commits. Those revisions are shared by NCS 2.4.0 through 2.6.1, so the functions do not uniquely identify a top-level patch version; the configured build is NCS 2.5.1 / Zephyr v3.4.99-ncs1-1.

No selected section has a mutable-state relocation. This receipt does not remove private/SDC code and does not regenerate shared named, symbolized, manifest, or CMake outputs.
