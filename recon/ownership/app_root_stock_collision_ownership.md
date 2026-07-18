# CPUAPP retain-all collision ownership

Deterministic report-only audit of the current real retain-all link.
It does not authorize source removal, aliases, CMake changes, or weak owners.

## Current snapshot

| Metric | Count |
|---|---:|
| Strong duplicate symbols | 18 |
| Diagnostic occurrences | 18 |
| Selected source units / batches | 13 |
| Exact-threshold SDK adoption candidates | 17 |
| Automatically authorized exclusions | 0 |
| Fail-closed retained/other | 18 |

## Safe-action partition

| Action | Symbols |
|---|---:|
| `adopt_sdk_whole_public_owner` | 17 |
| `blocked` | 0 |
| `caller_cohesion` | 0 |
| `retain_reconstruction` | 1 |

`adopt_sdk_whole_public_owner` is only a candidate when the selected
global object has DWARF ABI evidence and clears every configured shape
threshold. `caller_cohesion` keeps local SDK helpers scoped to callers;
`blocked` has missing or ambiguous indexed ownership.

## Non-overlapping implementation batches

| Batch | Source unit | Risk | Symbols | Actions |
|---|---|---|---:|---|
| `COLLISION-01` | `/Users/freedomcoder/ncs251/bootloader/mcuboot/boot/bootutil/src/bootutil_public.c` | `low` | 1 | `adopt_sdk_whole_public_owner` |
| `COLLISION-02` | `/Users/freedomcoder/ncs251/modules/lib/zcbor/src/zcbor_common.c` | `low` | 1 | `adopt_sdk_whole_public_owner` |
| `COLLISION-03` | `/Users/freedomcoder/ncs251/modules/lib/zcbor/src/zcbor_encode.c` | `low` | 1 | `adopt_sdk_whole_public_owner` |
| `COLLISION-04` | `zephyr/lib/os/fdtable.c` | `low` | 1 | `adopt_sdk_whole_public_owner` |
| `COLLISION-05` | `zephyr/lib/posix/pthread.c` | `medium` | 1 | `retain_reconstruction` |
| `COLLISION-06` | `zephyr/subsys/mgmt/mcumgr/grp/img_mgmt/src/img_mgmt.c` | `low` | 1 | `adopt_sdk_whole_public_owner` |
| `COLLISION-07` | `zephyr/subsys/mgmt/mcumgr/grp/img_mgmt/src/img_mgmt_state.c` | `low` | 3 | `adopt_sdk_whole_public_owner` |
| `COLLISION-08` | `zephyr/subsys/mgmt/mcumgr/grp/img_mgmt/src/img_mgmt_util.c` | `low` | 1 | `adopt_sdk_whole_public_owner` |
| `COLLISION-09` | `zephyr/subsys/mgmt/mcumgr/grp/img_mgmt/src/zephyr_img_mgmt.c` | `low` | 1 | `adopt_sdk_whole_public_owner` |
| `COLLISION-10` | `zephyr/subsys/mgmt/mcumgr/mgmt/src/mgmt.c` | `low` | 1 | `adopt_sdk_whole_public_owner` |
| `COLLISION-11` | `zephyr/subsys/mgmt/mcumgr/smp/src/smp.c` | `low` | 2 | `adopt_sdk_whole_public_owner` |
| `COLLISION-12` | `zephyr/subsys/mgmt/mcumgr/transport/src/smp.c` | `low` | 3 | `adopt_sdk_whole_public_owner` |
| `COLLISION-13` | `zephyr/subsys/storage/stream/stream_flash.c` | `low` | 1 | `adopt_sdk_whole_public_owner` |

Each source unit occurs in exactly one batch. Symbols remain individually
address-keyed in the JSON with retained source/VA, exact selected archive
and object hashes, configured-link proof, ABI, and instruction-shape evidence.
