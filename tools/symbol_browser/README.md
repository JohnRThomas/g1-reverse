# Trace — G1 Symbol Workbench

Trace is a local, dependency-free web application for reviewing and correcting
CPUAPP and CPUNET function names. It reads the persistent naming catalogs,
canonical recovered C, Ghidra function inventories, reference graphs, and
address-name catalogs directly from the repository.

## Run

```sh
tools/symbol_browser/run.sh
```

Open <http://127.0.0.1:8765>. Use `--port` to choose another port:

```sh
tools/symbol_browser/run.sh --port 8877
```

## Capabilities

- Search the G1 application corpus by default. The **G1 application only**
  checkbox exposes or hides catalog-proven SDK, toolchain, and bundled-library
  bodies without affecting direct GoToRef navigation.
- Inspect reconstructed C with linked function and address references.
- Review callers, callees, data references, source usages, aliases, ABI details,
  raw identities, addresses, and naming evidence.
- Use **GoToRef** with a readable name, `FUN_*` identity, function entry,
  interior code address, global/data address, or still-unnamed reference.
- Follow any reference in-app without losing the original address context.
- Apply a canonical rename while permanently retaining the raw identity.
- Use `G`, `/`, and `R` for GoToRef, filtering, and rename respectively.

## Canonical rename behavior

The application is designed for use after the active naming sweep lands. A
rename acquires a repository-local lock, updates
`recon/catalogs/function_name_overrides.json` atomically, and runs:

1. `tools/build_function_names.py <core>`
2. `tools/apply_names.py <core>`
3. `tools/symbolize.py <core> --write`
4. `tools/validate_name_maps.py`

If the pipeline fails, the override file is restored and the error is shown in
the dialog. While `recon/SESSION_COORDINATION.md` contains an active `HELD`
marker, canonical writes are refused; browsing and GoToRef remain fully usable.
The app does not use a shadow proposal catalog.

## Ownership filter

CPUAPP ownership comes from
`recon/application/application_sources.json`, including its explicit product
overrides and library evidence. CPUNET hides every upstream-owned function in
the adoption manifest plus the independently proven SDK functions in
`net_function_ownership.json`. Unclassified functions remain visible so the
filter cannot silently discard unresolved product code. Unchecking the box
restores the complete canonical corpus; GoToRef always resolves hidden library
functions directly.

## Design and accessibility

The interface is responsive, keyboard navigable, uses visible focus states,
semantic landmarks and dialogs, high-contrast text, restrained motion, and a
`prefers-reduced-motion` fallback. No fonts, scripts, analytics, or assets are
loaded from the network.

The server binds to `127.0.0.1` by default and only serves its three bundled
static assets plus the JSON API.
