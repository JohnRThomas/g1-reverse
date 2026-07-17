"""Stable identity checks shared by generated reconstruction source passes.

Human-readable filenames are presentation only.  A generated C source is
owned by ``(core, even entry address)`` as recorded in its provenance header.
Generators must finish building this plan before opening any output file so a
name collision can never silently overwrite another function.
"""

import os
import re


IDENTITY = re.compile(
    r"readable reconstruction; identity:\s+"
    r"(?P<raw>(?:FUN_|sub_)[0-9a-fA-F]+)\s+@\s+"
    r"(?P<address>0x[0-9a-fA-F]+)")
PUBLIC_NAME = re.compile(r"public-name:\s+(?P<name>[A-Za-z_$][\w$]*)")


def parse(text, path="<memory>"):
    """Return the durable identity embedded in a readable generated source."""
    identity = IDENTITY.search(text[:4096])
    public = PUBLIC_NAME.search(text[:4096])
    if not identity or not public:
        raise ValueError("missing readable identity header in %s" % path)
    address = int(identity.group("address"), 16) & ~1
    return {
        "address": address,
        "raw_name": identity.group("raw"),
        "public_name": public.group("name"),
    }


def add(planned, identities, filename, address, source, rendered):
    """Add one output to a write plan, rejecting path and identity aliases."""
    filename = os.path.basename(filename)
    if filename in planned:
        previous = planned[filename]
        raise ValueError(
            "generated filename collision %s: 0x%08x from %s / 0x%08x from %s"
            % (filename, previous["address"], previous["source"], address, source))
    if address in identities:
        previous = identities[address]
        raise ValueError(
            "duplicate generated identity 0x%08x: %s / %s"
            % (address, previous, source))
    planned[filename] = {
        "address": address,
        "source": source,
        "rendered": rendered,
    }
    identities[address] = source


def atomic_write(path, text):
    """Replace a generated file only after its complete contents are durable."""
    temporary = path + ".tmp"
    with open(temporary, "w") as stream:
        stream.write(text)
        stream.flush()
        os.fsync(stream.fileno())
    os.replace(temporary, path)
