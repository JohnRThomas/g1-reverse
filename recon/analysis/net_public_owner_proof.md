# CPUNET public-owner retain-all proof

The CPUNET integration shell was reconfigured with the shipped deferred
logging selection recorded in `net_sdk_public_ownership.json` and rebuilt with
all retained reconstruction sections enabled. The selected NCS v2.5.1 archive
contains exactly one strong definition for each adopted public owner:

| Firmware VA | Raw identity | Public owner | Selected archive member |
|---|---|---|---|
| `0x0102e284` | `FUN_0102e284` | `z_impl_z_log_msg_static_create` | `zephyr/libzephyr.a(log_msg.c.obj)` |
| `0x01039722` | `FUN_01039722` | `printk` | `zephyr/libzephyr.a(printk.c.obj)` |
| `0x01039bbe` | `FUN_01039bbe` | `assert_print` | `zephyr/libzephyr.a(assert.c.obj)` |

None of the three is undefined or multiply defined. The retain-all shell
reached the final link and still stops on 264 unique unresolved symbols from
the separately tracked reconstruction residue; it reported zero multiple
definitions overall. Therefore the logging configuration introduces no new
ownership regression, while making the exclusion of the reconstructed
`FUN_0102e284.c` fail-closed in the real build configuration.

Machine-readable object hashes, configuration, counts, and build-log hash are
in `net_public_owner_proof.json`.
