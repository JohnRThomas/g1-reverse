# CPUAPP hci_tx_thread embedded SVC resolution

The apparent functions `FUN_0005463e` and `FUN_00054688` were the
final `svc #2` instructions of two identical, in-body stock Zephyr
`ARCH_EXCEPT(3)` sequences. They are now expressed inside
`hci_tx_thread`; no veneer, alias, or invented callable ABI remains.

| sequence | SVC | bytes |
|---|---|---|
| `0x00054634` | `0x0005463e` | `404080f311884ff0030002df` |
| `0x0005467e` | `0x00054688` | `404080f311884ff0030002df` |

Authoritative CFG verification: **PASS, 8 cases**. The readable name
maps back to raw owner `FUN_000545f0 @ 0x000545f0`.
