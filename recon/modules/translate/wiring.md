# translate — RTOS wiring

Input to the wiring reconstruction. Read out of this module's proven bodies.

## RTOS objects this module DEFINES

**None.**

The `translate` module contains exactly one function, `cleanAppLanguageInfo`
@0x23b78. It has no `init` function and issues no `k_*_init` /
`K_THREAD_DEFINE` / `K_MSGQ_DEFINE` / `K_SEM_DEFINE` / `K_MUTEX_DEFINE` /
`K_WORK*` calls. It therefore defines no threads, message queues, semaphores,
mutexes, or work items.

## RTOS objects this module REFERENCES (defined elsewhere)

From `cleanAppLanguageInfo` @0x23b78 (recon/verified/src/cleanAppLanguageInfo.c):

| Object addr    | Used as                              | Call site                                   | Owner (defining module) |
|----------------|--------------------------------------|---------------------------------------------|-------------------------|
| `0x20003994`   | message queue — `k_msgq_put` target  | `FUN_000720d0(0x20003994, buf, 0, 0)` (k_msgq_put @0x720d0) | flash-store / app-language cluster (shared by 6 funcs: 0x23af0, 0x23bfc, 0x23c88, 0x23f04, 0x23acc, 0x23b78) |
| `0x200079e4`   | wait-queue / poll object — signalled | `FUN_00072880(0x200079e4)` (unpend-first / poll-notify @0x72880) | shared kernel object (referenced by 12 funcs incl. 0x244a8, 0x2f6b0, 0x2f764, 0x23c88) |

Message posted to msgq @0x20003994: 8-byte stack buffer, `buf[0]=2` (opcode),
`buf[1..5]=0`. The `K_MSGQ_DEFINE(msg_size, count)` parameters for @0x20003994
must be recovered from the defining function in the flash-store/app-language
cluster (the init that runs `k_msgq_init`/`K_MSGQ_DEFINE` for 0x20003994 — not
present in this module).

## Globals referenced (not RTOS objects; shared, not owned)

| Addr         | Name                | Role                                    |
|--------------|---------------------|-----------------------------------------|
| `0x2000230c` | `g_log_level`       | log-level threshold (>0 / >2 gates)     |
| `0x20007554` | `g_log_use_alt_sink`| selects DEBUG_PRINT vs alt log sink     |

## Note for wiring reconstruction
No wiring edges originate from `translate` as a *definer*. The only edges are:
- caller edge in: `touch_key` (FUN_0002316c @0x2316c) → cleanAppLanguageInfo.
- producer edge out: cleanAppLanguageInfo → msgq @0x20003994 (k_msgq_put) and
  wake @0x200079e4. Consumers of that msgq live in the flash-store/app-language
  cluster and must be wired there.
