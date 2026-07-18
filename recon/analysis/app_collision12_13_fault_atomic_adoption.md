# COLLISION-12/13: atomic ARM fault-owner adoption

The pinned NCS 2.5.1 `fault.c` and `fault_s.S` translation units own this
closure exactly under the shipped CPUAPP assertion configuration.

The three reconstructed bodies previously named `z_arm_mpu_fault`,
`z_arm_bus_fault`, and `z_arm_usage_fault` are not the public exception-entry
aliases from `fault_s.S`. Their sizes and bytes identify the three
translation-unit-local `fault.c` helpers:

| Firmware VA | Corrected readable identity | Exact object symbol | Bytes |
|---:|---|---|---:|
| `0x000503d8` | `arm_mem_manage_fault_helper` | `mem_manage_fault.constprop.0` | 384 |
| `0x00050558` | `arm_bus_fault_helper` | `bus_fault.constprop.0` | 340 |
| `0x000506ac` | `arm_usage_fault_helper` | `usage_fault.constprop.0` | 296 |
| `0x000507d4` | `z_arm_fault` | `z_arm_fault` | 640 |

Every non-relocation byte in all four configured `fault.c` sections matches
the corresponding firmware bytes. The adjacent `z_arm_fault_init` is also an
exact 24-byte configured owner. The common `fault_s.S` exception entry at
`0x00050a6c` is an exact 20-byte section after masking its sole call
relocation; its public labels remain owned exclusively by the assembly unit.

Adoption fails closed unless `CONFIG_ASSERT=y`, `CONFIG_ASSERT_LEVEL=2`,
verbose file/condition/message assertion metadata is retained, and
`CONFIG_EXTRA_EXCEPTION_INFO` is disabled. The latter preserves the shipped
three-register MSP/PSP/EXC_RETURN exception entry rather than adding a callee
saved-register argument payload.

The four exclusions are atomic. The normal retain-all link moves from 91 to
87 strong collisions, removes exactly `z_arm_fault` and the three formerly
misidentified public aliases, adds no collision, and leaves the unresolved set
exactly `{FUN_0005463e, FUN_00054688}`. Canonical parity sources remain on disk
under their raw VA identities and the durable naming map preserves all
backmaps.
