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

The policy is fail-closed. Glue, generic SDK classifications, and ambiguous
ownership remain included. In particular, the current SDC benchmark is useful
archive-family evidence but only publishes aggregate unique/ambiguous counts in
Markdown. It does not provide a per-VA machine-readable uniqueness field.
Therefore all obfuscated/private SDC entries are report-only and remain
`exclude_reconstruction: false`. A future machine catalog may promote an SDC
row only by recording its exact archive/member/section/symbol identity and
per-VA uniqueness explicitly.

The schema is `adoption_manifest.schema.json`. The standard-library self-test
uses isolated fixtures:

```sh
cd /tmp
PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
  /Users/freedomcoder/Projects/G1disasm2/tools/test_build_adoption_manifest.py
```
