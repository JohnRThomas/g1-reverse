# CPUAPP veneer-resolution integration proof

Validated on 2026-07-18 against `app_update.bin` SHA-256
`e0614feb3609fc2f251a00c16ca66f01c9fb8153de81ca1818cab5f79b42fd3b`.

The source residue contains 119 symbols at 117 VAs. The fail-closed review in
`recon/catalogs/app_veneer_resolutions.json` resolves 26 symbols at 24 VAs:

- 20 symbols are emitted as non-owning linker aliases. Every one is either an
  exact four-byte unconditional Thumb tail branch or an exact same-entry
  historical spelling.
- 6 symbols already have strong owners after identity regeneration and are not
  redundantly emitted.
- 93 symbols remain blocked. They are standalone-looking gaps, interior/split
  entries, SDK/config ownership, or exact branches whose destination owner is
  absent. None is aliased by proximity.

Verification:

- `test_build_app_veneer_resolutions.py`: 6/6 pass.
- `test_app_identity_aliases.py`: 4/4 pass.
- `tools/full_link.py app`: 2877/2877 objects compile; relocatable link returns
  zero. Nineteen emitted aliases resolve against retained reconstructed objects;
  `FUN_00080294_i` remains module-dependent in this object-only probe because
  its exact target `tc_cmac_final` is supplied by pinned TinyCrypt, not by the
  reconstructed-object directory.
- Clean retain-all Zephyr build at
  `/private/tmp/g1_cpuapp_veneer_retain`: all recovered sources compile and the
  final integration link map activates 20/20 emitted `PROVIDE` aliases,
  including the TinyCrypt alias. The build reaches the expected global
  collision/unresolved closure gate; none of these 20 symbols remains in its
  undefined diagnostics, and no alias creates a new multiple definition.

The retain-all build still fails overall on pre-existing SDK ownership
collisions and unrelated missing functions. This proof does not weaken those
diagnostics or claim that the CPUAPP image is link-complete.
