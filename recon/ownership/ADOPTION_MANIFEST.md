# Upstream adoption manifest

`adoption_manifest.json` is the deterministic, address-keyed boundary between
ownership research and a future build-system source-selection pass. Generate it
with:

```sh
cd /tmp
PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
  /Users/freedomcoder/Projects/G1disasm2/tools/build_adoption_manifest.py
```

Use `--check` in CI or before a commit. The command hashes every ownership
input, sorts entries by core and virtual address, and writes no timestamp, so
identical inputs produce identical bytes.

Each row retains the stable `core + even VA` identity and its raw
`FUN_xxxxxxxx` symbol. `kind` distinguishes directly compiled upstream source,
archive members, file-static helpers adopted with their source unit, data
tables, and integration glue. `exclude_reconstruction` is permission for a
later build-selection layer to omit the hand reconstruction; it is not a claim
of byte parity and this tool does not modify CMake or canonical C.

For CPUAPP SDK collisions, the manifest consumes
`app_build_collision_ownership.json`. Its retain-all link found 151 strong
same-name definitions; 58 passed the selected-object, DWARF ABI, and firmware
instruction-signature gates, while 93 remain fail-closed. A post-exclusion
link reproduced exactly the predicted 93-symbol retained set. See
`app_build_collision_ownership.md` for the thresholds and regeneration flow.

The policy is fail-closed. Glue, generic SDK classifications, and ambiguous
ownership remain included. The aggregate SDC benchmark alone has no exclusion
authority. `net_sdc_archive_ownership.json` now supplies per-VA identities, but
private and ambiguous SDC rows remain report-only. The sole promotion is the
public `sdc_default_tx_power_set` at `0x010091cc`: its published header ABI and
unique identity are CFG-verified, and a real net-shell link selected the pinned
archive member and reported the expected strong-symbol collision with the
deliberately retained reconstruction. Removing that one reconstruction makes
the shell link successfully. No obfuscated private SDC symbol is excluded.

The schema is `adoption_manifest.schema.json`. The standard-library self-test
uses isolated fixtures:

```sh
cd /tmp
PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
  /Users/freedomcoder/Projects/G1disasm2/tools/test_build_adoption_manifest.py
```

## Retained build-source lists

`tools/gen_retained_sources.py` consumes this manifest and the validated
`recon/symbolized/app` and `recon/symbolized/net` build trees. It writes:

- `recon/generated/app_retained_sources.cmake`
- `recon/generated/net_retained_sources.cmake`

Each artifact defines `G1_RETAINED_SOURCES`. Regenerate normally, or use
`--check` in CI to verify that committed output is current. The generator maps
every symbolized C file to one firmware VA and strictly verifies its generated
identity header, durable filename mapping, and global VA uniqueness. Only
manifest rows with `exclude_reconstruction: true` are omitted; report-only SDC
rows are explicitly rejected as exclusion authority. `--source-tree canonical`
is available only as an explicit diagnostic fallback and is never selected
silently.
