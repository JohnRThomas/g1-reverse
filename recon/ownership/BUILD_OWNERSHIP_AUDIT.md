# Build ownership and collision audit

`tools/audit_build_ownership.py` checks a configured app or net build against
`adoption_manifest.json`. It reports reconstructed/upstream symbol collisions,
excluded reconstruction bodies that still participate, missing upstream owners,
wrong archive members or source units, and unresolved raw `FUN_*`/`DAT_*` names.

The tool is read-only. Before build artifacts exist its status is `unavailable`;
incomplete evidence is `partial`, and neither state misreports every expected
owner as missing. Use `--strict-artifacts` when a CI stage is expected to have
produced a complete map, nm listing, or full compile-object set already.

Typical configured-build invocation:

```sh
cd /tmp
PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
  /Users/freedomcoder/Projects/G1disasm2/tools/audit_build_ownership.py \
  --core app \
  --compile-commands /path/to/build/compile_commands.json \
  --map /path/to/build/zephyr/zephyr.map \
  --object /path/to/build/zephyr/zephyr.elf \
  --output /path/to/build/app_ownership_audit.json
```

For deterministic fixture or CI input, pass one or more pre-generated
`nm -A -a -S` listings through `--nm-file`. Linker maps are particularly useful
because they retain archive-member provenance that a final merged ELF loses.
Existing object outputs listed by `compile_commands.json` are inspected
automatically. A partial object set can expose collisions, but does not authorize
"owner missing" findings. A merged ELF without a map reports owner provenance as
inconclusive rather than guessing an object.

Standard output is a concise, bounded summary. `--output report.json` writes the
complete machine-readable report; use `--json` only when the full report is
explicitly wanted on standard output. The internal object scan uses global nm
symbols only, excluding local, section, debug, and file pseudo-symbols.

Run the standard-library fixture tests with:

```sh
cd /tmp
PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
  /Users/freedomcoder/Projects/G1disasm2/tools/test_audit_build_ownership.py
```
