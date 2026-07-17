#!/usr/bin/env python3
"""Prove and materialize the CPUAPP public k_sem_take veneer."""

import hashlib
import json
import os
import re
import tempfile

from capstone import Cs, CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB
from capstone.arm import ARM_OP_IMM


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NCS = "/Users/freedomcoder/ncs251"
IMAGE = os.path.join(ROOT, "app_update.bin")
LINK_BASE = 0xC200
IMAGE_HEADER = 512
WRAPPER_VA = 0x0007CB48
TARGET_VA = 0x00072908
ZEPHYR_COMMIT = "83980fe1679441be9b0e1db556a353f6118fe14f"


def sha256(path):
    with open(path, "rb") as stream:
        return hashlib.sha256(stream.read()).hexdigest()


def atomic_write(path, text):
    fd, temporary = tempfile.mkstemp(
        prefix=os.path.basename(path) + ".", dir=os.path.dirname(path), text=True)
    try:
        with os.fdopen(fd, "w") as stream:
            stream.write(text)
        os.replace(temporary, path)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)


def build():
    names_path = os.path.join(ROOT, "recon/catalogs/function_names_app.json")
    residue_path = os.path.join(ROOT, "recon/analysis/app_link_residue.json")
    retained_path = os.path.join(ROOT, "recon/generated/app_retained_sources.cmake")
    cmake_path = os.path.join(ROOT, "recon/application/app/CMakeLists.txt")
    kernel_h = os.path.join(NCS, "zephyr/include/zephyr/kernel.h")
    sem_c = os.path.join(NCS, "zephyr/kernel/sem.c")
    generated_h = os.path.join(
        NCS, "refapp/build/zephyr/include/generated/syscalls/kernel.h")
    config = os.path.join(NCS, "refapp/build/zephyr/.config")

    with open(IMAGE, "rb") as stream:
        image = stream.read()
    with open(names_path) as stream:
        names = json.load(stream)
    with open(residue_path) as stream:
        residue = json.load(stream)
    with open(retained_path) as stream:
        retained = stream.read()
    with open(cmake_path) as stream:
        cmake_text = stream.read()
    with open(kernel_h) as stream:
        kernel_text = stream.read()
    with open(sem_c) as stream:
        sem_text = stream.read()
    with open(generated_h) as stream:
        generated_text = stream.read()
    with open(config) as stream:
        config_text = stream.read()

    wrapper = names["by_address"].get("0x%08x" % WRAPPER_VA)
    target = names["by_address"].get("0x%08x" % TARGET_VA)
    if not wrapper or wrapper.get("name") != "k_sem_take":
        raise RuntimeError("public k_sem_take back-map changed")
    if not target or target.get("name") != "z_impl_k_sem_take":
        raise RuntimeError("z_impl_k_sem_take back-map changed")

    rows = [item for item in residue["entries"] if item["symbol"] == "k_sem_take"]
    if len(rows) != 1:
        raise RuntimeError("expected one k_sem_take residue row")
    row = rows[0]
    identity_vas = {int(item["va"], 16) for item in row.get("identities", [])}
    if {WRAPPER_VA, TARGET_VA} - identity_vas:
        raise RuntimeError("k_sem_take residue identities changed")
    if row["reference_count"] != 6 or len(row["reference_sites"]) != 6:
        raise RuntimeError("k_sem_take reference set changed")

    off = WRAPPER_VA - LINK_BASE + IMAGE_HEADER
    raw = image[off:off + 4]
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
    md.detail = True
    insn = next(md.disasm(raw, WRAPPER_VA, count=1), None)
    if (not insn or insn.size != 4 or insn.mnemonic not in ("b", "b.w") or
            len(insn.operands) != 1 or insn.operands[0].type != ARM_OP_IMM or
            (insn.operands[0].imm & ~1) != TARGET_VA):
        raise RuntimeError("shipped public veneer is no longer an exact tail branch")

    if "# CONFIG_USERSPACE is not set" not in config_text:
        raise RuntimeError("CONFIG_USERSPACE must remain disabled")
    if not re.search(
            r"__syscall\s+int\s+k_sem_take\(struct k_sem \*sem,\s*"
            r"k_timeout_t timeout\);", kernel_text):
        raise RuntimeError("public k_sem_take declaration changed")
    if not re.search(
            r"int\s+z_impl_k_sem_take\(struct k_sem \*sem,\s*"
            r"k_timeout_t timeout\)", sem_text):
        raise RuntimeError("z_impl_k_sem_take ABI changed")
    wrapper_pattern = (
        r"static inline int k_sem_take\(struct k_sem \* sem, k_timeout_t timeout\)"
        r".*?compiler_barrier\(\);\s*return z_impl_k_sem_take\(sem, timeout\);")
    if not re.search(wrapper_pattern, generated_text, re.S):
        raise RuntimeError("generated no-userspace wrapper body changed")
    if "symbolized/app/z_impl_k_sem_take.c\"" not in retained:
        raise RuntimeError("strong reconstructed z_impl owner is not retained")
    displacement = "z_impl_k_sem_take=g1_displaced_sdk_z_impl_k_sem_take"
    if displacement not in cmake_text:
        raise RuntimeError("non-selected SDK z_impl owner is not displaced")

    return {
        "schema": 1,
        "core": "app",
        "symbol": "k_sem_take",
        "decision": "materialize_directional_alias",
        "alias": "k_sem_take",
        "owner": "z_impl_k_sem_take",
        "wrapper_va": "0x%08x" % WRAPPER_VA,
        "owner_va": "0x%08x" % TARGET_VA,
        "firmware": {
            "image_sha256": hashlib.sha256(image).hexdigest(),
            "bytes": raw.hex(),
            "decode": (insn.mnemonic + " " + insn.op_str).strip(),
            "relationship": "exact four-byte unconditional Thumb tail branch",
        },
        "abi": {
            "return": "int in r0",
            "parameter_0": "struct k_sem * in r0",
            "parameter_1": "k_timeout_t (int64_t) aligned in r2:r3",
            "r1": "AAPCS32 alignment padding; not a semantic parameter",
            "tail_safe": True,
        },
        "upstream": {
            "version": "NCS v2.5.1 / Zephyr 3.4.99",
            "zephyr_commit": ZEPHYR_COMMIT,
            "config": "CONFIG_USERSPACE=n",
            "declaration": "zephyr/include/zephyr/kernel.h:3137",
            "generated_wrapper": "refapp/build/zephyr/include/generated/syscalls/kernel.h:1093",
            "implementation": "zephyr/kernel/sem.c:124",
            "files": {
                "kernel_h_sha256": sha256(kernel_h),
                "generated_kernel_h_sha256": sha256(generated_h),
                "sem_c_sha256": sha256(sem_c),
                "config_sha256": sha256(config),
            },
        },
        "ownership": {
            "kind": "retained reconstruction",
            "source": "recon/symbolized/app/z_impl_k_sem_take.c",
            "one_strong_owner_required": True,
            "sdk_z_impl_adopted": False,
            "sdk_symbol_displacement": displacement,
            "reason": "pinned SDK z_impl code shape does not match the shipped configured body",
        },
        "references": {
            "count": row["reference_count"],
            "sites": row["reference_sites"],
        },
        "policy": {
            "weak_stub": False,
            "absolute_address_alias": False,
            "raw_address_backmap_preserved": True,
            "semantic_guess": False,
        },
    }


def render_ld(catalog):
    return (
        "/* Generated by tools/build_app_k_sem_take_ownership.py.\n"
        " * Exact public Zephyr veneer; retained z_impl is the sole owner. */\n\n"
        "PROVIDE(k_sem_take = z_impl_k_sem_take); /* 0x0007cb48 -> 0x00072908 */\n"
    )


def render_md(catalog):
    return """# CPUAPP `k_sem_take` ownership

The shipped public entry at `0x0007cb48` is the exact four-byte Thumb tail
branch `f5f7debe` to retained `z_impl_k_sem_take` at `0x00072908`.

The pinned NCS v2.5.1 / Zephyr 3.4.99 build has `CONFIG_USERSPACE=n`, so the
generated public wrapper performs only a compiler barrier and returns the
implementation result. Its ABI is `struct k_sem *` in `r0`, alignment padding
in `r1`, and the 64-bit `k_timeout_t` in `r2:r3`. Therefore the directional
link alias preserves both behavior and ABI; it does not replace the distinct
configured implementation with the non-matching SDK body.

- References resolved: 6
- Strong owner: `recon/symbolized/app/z_impl_k_sem_take.c`
- Non-selected SDK body: renamed locally to `g1_displaced_sdk_z_impl_k_sem_take`
- Weak stubs, absolute-address aliases, and guessed semantics: none
- Raw back-map retained: `k_sem_take` `0x0007cb48` -> `z_impl_k_sem_take` `0x00072908`
"""


def main():
    catalog = build()
    base = os.path.join(ROOT, "recon/ownership/app_k_sem_take_ownership")
    atomic_write(base + ".json", json.dumps(catalog, indent=2) + "\n")
    atomic_write(base + ".md", render_md(catalog))
    atomic_write(os.path.join(ROOT, "recon/symbols/g1_app_public_sdk_aliases.ld"),
                 render_ld(catalog))
    print("k_sem_take: 0x0007cb48 -> z_impl_k_sem_take@0x00072908 (6 refs)")


if __name__ == "__main__":
    main()
