# CPUNET pseudo-symbol lowerings

The six `compiler_or_ghidra_pseudo` residues from the retain-all link are now
accounted for by original Thumb evidence. None is an unknown firmware function,
and none is implemented as a weak stub or binary blob.

| Residue | Exact classification | Resolution |
|---|---|---|
| `FUN_shadow_default` | CFG-boundary artifact | Strong owner returning zero, matching `0x0100d4cc` |
| `PHANTOM_BOUNDARY` | Interior continuation | Assert/error call followed by the original continuation |
| `PHANTOM_RETRY` | Artifact conflating two paths | Fatal assertion island plus the real rare-path callee |
| `g1_arch_runtime_exception` | ARM/Zephyr architecture macro | Inline `ARCH_EXCEPT`: clear BASEPRI, set reason, `svc 2` |
| `g1_irq_lock` | ARM PRIMASK intrinsic | Inline `mrs PRIMASK; cpsid i` |
| `g1_irq_unlock` | ARM PRIMASK intrinsic | Conditional inline `cpsie i` |

The machine-readable evidence, exact instruction addresses, affected owners,
and CFG verification results are in `net_pseudo_lowerings.json`.

The symbolized retain-all probe rebuilt all 805 reconstructed sources plus the
strong boundary owner. None of these six names remains unresolved; the final
link continues to stop on the separately tracked function/data residue.
