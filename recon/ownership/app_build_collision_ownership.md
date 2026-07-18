# CPUAPP retain-all collision ownership

Deterministic report-only audit of the current real retain-all link.
It does not authorize source removal, aliases, CMake changes, or weak owners.

## Current snapshot

| Metric | Count |
|---|---:|
| Strong duplicate symbols | 112 |
| Diagnostic occurrences | 112 |
| Selected source units / batches | 37 |
| Exact-threshold SDK adoption candidates | 9 |
| Automatically authorized exclusions | 0 |
| Fail-closed retained/other | 112 |

## Safe-action partition

| Action | Symbols |
|---|---:|
| `adopt_sdk_whole_public_owner` | 9 |
| `blocked` | 8 |
| `caller_cohesion` | 11 |
| `retain_reconstruction` | 84 |

`adopt_sdk_whole_public_owner` is only a candidate when the selected
global object has DWARF ABI evidence and clears every configured shape
threshold. `caller_cohesion` keeps local SDK helpers scoped to callers;
`blocked` has missing or ambiguous indexed ownership.

## Non-overlapping implementation batches

| Batch | Source unit | Risk | Symbols | Actions |
|---|---|---|---:|---|
| `COLLISION-01` | `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a` | `blocked` | 5 | `blocked` |
| `COLLISION-02` | `modules/hal/libmetal/libmetal/lib/device.c` | `low` | 1 | `adopt_sdk_whole_public_owner` |
| `COLLISION-03` | `modules/hal/nordic/nrfx/drivers/src/nrfx_clock.c` | `medium` | 2 | `retain_reconstruction` |
| `COLLISION-04` | `modules/hal/nordic/nrfx/drivers/src/nrfx_dppi.c` | `medium` | 1 | `retain_reconstruction` |
| `COLLISION-05` | `modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c` | `medium` | 1 | `retain_reconstruction` |
| `COLLISION-06` | `modules/hal/nordic/nrfx/drivers/src/nrfx_nvmc.c` | `medium` | 2 | `retain_reconstruction` |
| `COLLISION-07` | `modules/hal/nordic/nrfx/drivers/src/nrfx_pdm.c` | `medium` | 5 | `retain_reconstruction` |
| `COLLISION-08` | `modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c` | `medium` | 3 | `retain_reconstruction` |
| `COLLISION-09` | `modules/hal/nordic/nrfx/helpers/nrfx_gppi_dppi.c` | `medium` | 2 | `retain_reconstruction` |
| `COLLISION-10` | `modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg_virtio.c` | `low` | 1 | `adopt_sdk_whole_public_owner` |
| `COLLISION-11` | `modules/lib/open-amp/open-amp/lib/virtio/virtqueue.c` | `medium` | 1 | `retain_reconstruction` |
| `COLLISION-12` | `zephyr/arch/arm/core/aarch32/cortex_m/fault.c` | `medium` | 1 | `retain_reconstruction` |
| `COLLISION-13` | `zephyr/arch/arm/core/aarch32/cortex_m/fault_s.S` | `blocked` | 3 | `blocked` |
| `COLLISION-14` | `zephyr/kernel/kheap.c` | `medium` | 1 | `retain_reconstruction` |
| `COLLISION-15` | `zephyr/kernel/mem_slab.c` | `medium` | 2 | `retain_reconstruction` |
| `COLLISION-16` | `zephyr/kernel/mempool.c` | `medium` | 1 | `retain_reconstruction` |
| `COLLISION-17` | `zephyr/kernel/queue.c` | `medium` | 1 | `retain_reconstruction` |
| `COLLISION-18` | `zephyr/kernel/sched.c` | `medium` | 4 | `retain_reconstruction` |
| `COLLISION-19` | `zephyr/kernel/work.c` | `high` | 7 | `caller_cohesion` |
| `COLLISION-20` | `zephyr/lib/crc/crc16_sw.c` | `medium` | 1 | `retain_reconstruction` |
| `COLLISION-21` | `zephyr/lib/libc/newlib/libc-hooks.c` | `medium` | 2 | `retain_reconstruction` |
| `COLLISION-22` | `zephyr/lib/os/heap.c` | `high` | 2 | `caller_cohesion` |
| `COLLISION-23` | `zephyr/lib/os/mpsc_pbuf.c` | `medium` | 4 | `retain_reconstruction` |
| `COLLISION-24` | `zephyr/subsys/bluetooth/host/att.c` | `medium` | 2 | `retain_reconstruction` |
| `COLLISION-25` | `zephyr/subsys/bluetooth/host/conn.c` | `high` | 3 | `adopt_sdk_whole_public_owner`, `retain_reconstruction` |
| `COLLISION-26` | `zephyr/subsys/bluetooth/host/gatt.c` | `high` | 12 | `adopt_sdk_whole_public_owner`, `retain_reconstruction` |
| `COLLISION-27` | `zephyr/subsys/bluetooth/host/hci_core.c` | `medium` | 3 | `retain_reconstruction` |
| `COLLISION-28` | `zephyr/subsys/bluetooth/host/id.c` | `high` | 1 | `caller_cohesion` |
| `COLLISION-29` | `zephyr/subsys/bluetooth/host/keys.c` | `medium` | 10 | `retain_reconstruction` |
| `COLLISION-30` | `zephyr/subsys/bluetooth/host/l2cap.c` | `medium` | 3 | `retain_reconstruction` |
| `COLLISION-31` | `zephyr/subsys/bluetooth/host/settings.c` | `low` | 1 | `adopt_sdk_whole_public_owner` |
| `COLLISION-32` | `zephyr/subsys/logging/log_core.c` | `medium` | 3 | `retain_reconstruction` |
| `COLLISION-33` | `zephyr/subsys/logging/log_output.c` | `high` | 2 | `adopt_sdk_whole_public_owner`, `caller_cohesion` |
| `COLLISION-34` | `zephyr/subsys/net/buf.c` | `medium` | 10 | `retain_reconstruction` |
| `COLLISION-35` | `zephyr/subsys/net/buf_simple.c` | `medium` | 3 | `retain_reconstruction` |
| `COLLISION-36` | `zephyr/subsys/settings/src/settings.c` | `medium` | 3 | `retain_reconstruction` |
| `COLLISION-37` | `zephyr/subsys/settings/src/settings_store.c` | `high` | 3 | `adopt_sdk_whole_public_owner`, `retain_reconstruction` |

Each source unit occurs in exactly one batch. Symbols remain individually
address-keyed in the JSON with retained source/VA, exact selected archive
and object hashes, configured-link proof, ABI, and instruction-shape evidence.
