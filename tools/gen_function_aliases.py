"""Generate only provably-eligible raw/readable aliases from a partial ELF.

An alias is emitted when exactly one side of a bijective function-name manifest
record is defined and the other is undefined.  Missing/missing and defined/
defined pairs are reported but never guessed.  Explicit SDK/tail aliases remain
separate in g1_<core>_aliases.ld.
"""

import json
import glob
import os
import re
import subprocess
import sys
import tempfile


BASE = "/Users/freedomcoder/Projects/G1disasm2"
NM = ("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
      "arm-zephyr-eabi-nm")


def symbols(elf):
    defined = set()
    undefined = set()
    for line in subprocess.run([NM, "-g", elf], capture_output=True,
                               text=True, check=True).stdout.splitlines():
        fields = line.split()
        if len(fields) == 2 and fields[0] == "U":
            undefined.add(fields[1])
        elif len(fields) >= 3 and fields[-2] != "U":
            defined.add(fields[-1])
    return defined, undefined


def require_fresh_complete_elf(core, elf, manifest_path):
    """Reject stale/partial link evidence before touching the durable output."""
    if not os.path.exists(elf):
        raise SystemExit("missing partial ELF: %s (run full_link.py %s)" %
                         (elf, core))
    object_dir = BASE + "/build/%s_full_obj" % core
    sources = glob.glob(BASE + "/recon/symbolized/%s/*.c" % core)
    sources += glob.glob(BASE + ("/recon/data/*.c" if core == "app" else
                                 "/recon/net/data/*.c"))
    sources += glob.glob(BASE + "/recon/blobs/%s/*.S" % core)
    missing = []
    stale_objects = []
    for source in sources:
        obj = os.path.join(object_dir,
                           os.path.basename(source).rsplit(".", 1)[0] + ".o")
        if not os.path.exists(obj):
            missing.append(os.path.relpath(source, BASE))
        elif os.path.getmtime(obj) < os.path.getmtime(source):
            stale_objects.append(os.path.relpath(source, BASE))
    if missing or stale_objects:
        detail = ((" missing objects: " + ", ".join(missing[:5])) if missing else "")
        detail += ((" stale objects: " + ", ".join(stale_objects[:5]))
                   if stale_objects else "")
        raise SystemExit("refusing aliases from incomplete/stale object set;" + detail)

    newest_input = max([os.path.getmtime(manifest_path)] +
                       [os.path.getmtime(path) for path in sources] +
                       [os.path.getmtime(path) for path in
                        glob.glob(object_dir + "/*.o")])
    if os.path.getmtime(elf) < newest_input:
        raise SystemExit("refusing aliases from stale partial ELF; rerun full_link.py %s" %
                         core)


def main():
    core = sys.argv[1] if len(sys.argv) > 1 else "app"
    if core not in ("app", "net"):
        raise SystemExit("usage: gen_function_aliases.py <app|net>")
    elf = BASE + "/build/%s_full.elf" % core
    manifest_path = BASE + "/recon/catalogs/function_names_%s.json" % core
    require_fresh_complete_elf(core, elf, manifest_path)
    manifest = json.load(open(manifest_path))
    defined, undefined = symbols(elf)
    aliases = []
    rejected = {"both_defined": [], "neither_defined": []}
    for address, record in sorted(manifest["by_address"].items()):
        raw = record["raw_name"]
        readable = record["name"]
        if raw == readable or not record.get("human"):
            continue
        raw_defined = raw in defined
        readable_defined = readable in defined
        if raw in undefined and readable_defined and not raw_defined:
            aliases.append((raw, readable, address))
        elif readable in undefined and raw_defined and not readable_defined:
            aliases.append((readable, raw, address))
        elif raw_defined and readable_defined:
            rejected["both_defined"].append((raw, readable, address))
        elif ((raw in undefined or readable in undefined) and
              not raw_defined and not readable_defined):
            rejected["neither_defined"].append((raw, readable, address))

    targets = {}
    for alias, target, address in aliases:
        previous = targets.setdefault(alias, (target, address))
        if previous != (target, address):
            raise SystemExit("conflicting alias %s: %r / %r" %
                             (alias, previous, (target, address)))
    out = BASE + "/recon/symbols/g1_%s_function_aliases.ld" % core
    lines = ["/* Generated from defined/undefined symbols + reversible manifest.",
             " * Do not add SDK, pseudo-op, interior-tail, or guessed aliases here. */", ""]
    for alias, (target, address) in sorted(targets.items(),
                                            key=lambda item: int(item[1][1], 16)):
        lines.append("PROVIDE(%s = %s); /* %s */" % (alias, target, address))
    # Replace atomically only after every validation and conflict check has
    # succeeded.  A stale ELF or interrupted run must leave the last proven
    # fragment byte-for-byte intact.
    fd, temporary = tempfile.mkstemp(prefix=os.path.basename(out) + ".",
                                     dir=os.path.dirname(out), text=True)
    try:
        with os.fdopen(fd, "w") as stream:
            stream.write("\n".join(lines) + "\n")
        os.replace(temporary, out)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)
    print("[%s] generated aliases=%d both-defined=%d neither-defined=%d -> %s" %
          (core, len(targets), len(rejected["both_defined"]),
           len(rejected["neither_defined"]), out))


if __name__ == "__main__":
    main()
