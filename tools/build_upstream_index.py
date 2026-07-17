#!/usr/bin/env python3
"""Build an evidence-rich, object-qualified NCS upstream function index.

The index is a hypothesis source, never a naming/proof ledger.  Duplicate
static symbols are preserved as ``object::section::symbol`` records.  Defaults
use the exact local NCS 2.5.1 refapp/netref compile databases; extra object and
source roots may be supplied explicitly.

Examples (run from /tmp: the repository has a local struct.py):
  cd /tmp
  PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
      /Users/freedomcoder/Projects/G1disasm2/tools/build_upstream_index.py --core app
  PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
      /Users/freedomcoder/Projects/G1disasm2/tools/build_upstream_index.py --core net \
      --object-root /tmp/another-build --source-root /tmp/another-tree \
      --output /tmp/net-upstream.json
  PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python \
      /Users/freedomcoder/Projects/G1disasm2/tools/build_upstream_index.py --self-test
"""
import argparse
import collections
import hashlib
import json
import os
import re

from capstone import (Cs, CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB,
                      CS_GRP_CALL, CS_GRP_JUMP)
from capstone.arm import (ARM_OP_IMM, ARM_OP_MEM, ARM_OP_REG, ARM_REG_LR,
                          ARM_REG_PC, ARM_REG_SP)
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

BASE = "/Users/freedomcoder/Projects/G1disasm2"
DEFAULT_BUILD = {
    "app": "/Users/freedomcoder/ncs251/refapp/build",
    "net": "/Users/freedomcoder/ncs251/netref_build",
}

MD = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
MD.detail = True


def _reg_class(insn, reg):
    if reg == ARM_REG_SP:
        return "SP"
    if reg == ARM_REG_LR:
        return "LR"
    if reg == ARM_REG_PC:
        return "PC"
    name = insn.reg_name(reg) or "?"
    if re.fullmatch(r"r(?:1[0-2]|[0-9])", name):
        return "R"
    if re.fullmatch(r"s(?:[12]?[0-9]|3[01])", name):
        return "S"
    if re.fullmatch(r"d(?:[12]?[0-9]|3[01])", name):
        return "D"
    if re.fullmatch(r"q(?:1[0-5]|[0-9])", name):
        return "Q"
    return name.upper()


def _imm_class(value):
    value = int(value)
    magnitude = abs(value)
    if value in (-1, 0, 1):
        return str(value)
    if magnitude and magnitude & (magnitude - 1) == 0:
        return "POW2"
    if -16 <= value <= 16:
        return "SMALL"
    if -256 <= value <= 255:
        return "BYTE"
    if -65536 <= value <= 65535:
        return "HALF"
    return "IMM"


def _value_class(value):
    value &= 0xffffffff
    if value < 0x10000:
        return "scalar:%s" % _imm_class(value)
    if 0x20000000 <= value < 0x22000000:
        return "ram"
    if 0x40000000 <= value < 0x60000000:
        return "mmio"
    if value < 0x02000000:
        return "flash"
    return "word"


def _reloc_symbol(relocs, start, size):
    for offset in range(start, start + max(1, size)):
        rows = relocs.get(offset)
        if rows:
            return rows[0]
    return None


def extract_features(code, address=0, section_data=None, section_address=0,
                     function_offset=0, relocs=None, symbols_by_address=None):
    """Return deterministic opcode/shape/call/literal features for Thumb code."""
    relocs = relocs or {}
    symbols_by_address = symbols_by_address or {}
    section_data = code if section_data is None else section_data
    mnemonics, shapes, calls, literals = [], [], [], []
    instructions = list(MD.disasm(code, address))
    executable_count = len(instructions)
    for ordinal, insn in enumerate(instructions):
        mnemonic = insn.mnemonic.split(".")[0]
        mnemonics.append(mnemonic)
        operands = []
        for operand in insn.operands:
            if operand.type == ARM_OP_REG:
                operands.append(_reg_class(insn, operand.reg))
            elif operand.type == ARM_OP_IMM:
                if insn.group(CS_GRP_CALL) or insn.group(CS_GRP_JUMP):
                    operands.append("TGT")
                else:
                    operands.append(_imm_class(operand.imm))
            elif operand.type == ARM_OP_MEM:
                base = _reg_class(insn, operand.mem.base) if operand.mem.base else "-"
                index = _reg_class(insn, operand.mem.index) if operand.mem.index else "-"
                operands.append("MEM[%s,%s,%s]" %
                                (base, index, _imm_class(operand.mem.disp)))
            else:
                operands.append("OP%d" % operand.type)
        shapes.append(mnemonic + ":" + ",".join(operands))

        section_off = function_offset + (insn.address - address)
        relocation = _reloc_symbol(relocs, section_off, insn.size)
        immediate = next((op.imm for op in insn.operands
                          if op.type == ARM_OP_IMM), None)
        external_tail = (mnemonic == "b" and relocation and
                         relocation.get("symbol"))
        firmware_tail = (mnemonic == "b" and immediate is not None and
                         not (address <= int(immediate) < address + len(code)))
        if insn.group(CS_GRP_CALL) or mnemonic in ("bl", "blx") or external_tail or firmware_tail:
            target_name = relocation.get("symbol") if relocation else None
            if not target_name:
                if immediate is not None:
                    target_name = symbols_by_address.get(int(immediate) & ~1)
            calls.append({"ordinal": ordinal, "mnemonic": mnemonic,
                          "target": target_name or "?",
                          "address": ((int(immediate) & ~1)
                                      if immediate is not None else None)})
        if external_tail or firmware_tail:
            executable_count = min(executable_count, ordinal + 1)

        for operand in insn.operands:
            if operand.type != ARM_OP_MEM or operand.mem.base != ARM_REG_PC:
                continue
            pc = (insn.address + 4) & ~3
            target = pc + operand.mem.disp
            target_off = target - section_address
            width = 1 if mnemonic.endswith("b") else (2 if mnemonic.endswith("h") else 4)
            raw = None
            if 0 <= target_off and target_off + width <= len(section_data):
                raw = bytes(section_data[target_off:target_off + width])
            literal_reloc = _reloc_symbol(relocs, target_off, width)
            value = int.from_bytes(raw, "little") if raw else None
            literals.append({
                "ordinal": ordinal,
                "width": width,
                "class": ("reloc:" + literal_reloc["symbol"]
                          if literal_reloc and literal_reloc.get("symbol")
                          else (_value_class(value) if value is not None else "unreadable")),
                "value": value,
            })
    normalized = "\n".join(shapes).encode()
    return {
        "instruction_count": len(mnemonics),
        "executable_instruction_count": executable_count,
        "mnemonics": mnemonics,
        "operand_shapes": shapes,
        "normalized_sha256": hashlib.sha256(normalized).hexdigest(),
        "calls": calls,
        "literals": literals,
    }


def _compile_database(build_root):
    mapping, commands = {}, []
    paths = []
    direct = os.path.join(build_root, "compile_commands.json")
    if os.path.exists(direct):
        paths.append(direct)
    for path in paths:
        try:
            rows = json.load(open(path))
        except (OSError, ValueError):
            continue
        for row in rows:
            directory = row.get("directory") or os.path.dirname(path)
            output = row.get("output")
            if output:
                output = output if os.path.isabs(output) else os.path.join(directory, output)
                mapping[os.path.realpath(output)] = os.path.realpath(row.get("file", ""))
            commands.append(row)
    return mapping, commands


def _source_fallback(roots):
    candidates = collections.defaultdict(list)
    for root in roots:
        for directory, _, files in os.walk(root):
            for name in files:
                if name.endswith((".c", ".cc", ".cpp", ".S")):
                    candidates[os.path.splitext(name)[0]].append(
                        os.path.realpath(os.path.join(directory, name)))
    return {stem: paths[0] for stem, paths in candidates.items() if len(paths) == 1}


def _type_name(die):
    if die is None:
        return "void"
    name = die.attributes.get("DW_AT_name")
    if name:
        value = name.value
        return value.decode("utf-8", "replace") if isinstance(value, bytes) else str(value)
    if die.tag == "DW_TAG_pointer_type":
        try:
            return _type_name(die.get_DIE_from_attribute("DW_AT_type")) + "*"
        except Exception:
            return "void*"
    try:
        return _type_name(die.get_DIE_from_attribute("DW_AT_type"))
    except Exception:
        return die.tag.replace("DW_TAG_", "")


def _dwarf_signatures(elf):
    result = collections.defaultdict(list)
    if not elf.has_dwarf_info():
        return result
    try:
        dwarf = elf.get_dwarf_info()
        for cu in dwarf.iter_CUs():
            for die in cu.iter_DIEs():
                if die.tag != "DW_TAG_subprogram":
                    continue
                attr = die.attributes.get("DW_AT_linkage_name") or die.attributes.get("DW_AT_name")
                if not attr:
                    continue
                value = attr.value
                name = value.decode("utf-8", "replace") if isinstance(value, bytes) else str(value)
                params, variadic = [], False
                for child in die.iter_children():
                    if child.tag == "DW_TAG_formal_parameter":
                        try:
                            params.append(_type_name(child.get_DIE_from_attribute("DW_AT_type")))
                        except Exception:
                            params.append("?")
                    elif child.tag == "DW_TAG_unspecified_parameters":
                        variadic = True
                try:
                    return_type = _type_name(die.get_DIE_from_attribute("DW_AT_type"))
                except Exception:
                    return_type = "void"
                line = die.attributes.get("DW_AT_decl_line")
                result[name].append({"return": return_type, "params": params,
                                     "variadic": variadic,
                                     "decl_line": int(line.value) if line else None})
    except Exception:
        pass
    return result


def _relocations(elf):
    by_section = collections.defaultdict(lambda: collections.defaultdict(list))
    for section in elf.iter_sections():
        if not isinstance(section, RelocationSection):
            continue
        target_index = int(section["sh_info"])
        symbols = elf.get_section(section["sh_link"])
        for relocation in section.iter_relocations():
            symbol = symbols.get_symbol(relocation["r_info_sym"])
            symbol_name = symbol.name
            if not symbol_name and isinstance(symbol["st_shndx"], int):
                target = elf.get_section(symbol["st_shndx"])
                symbol_name = target.name if target is not None else ""
            by_section[target_index][int(relocation["r_offset"])].append({
                "symbol": symbol_name,
                "type": int(relocation["r_info_type"]),
                "addend": int(relocation.entry.get("r_addend", 0)),
            })
    return by_section


def index_object(path, source=None):
    records = []
    with open(path, "rb") as stream:
        elf = ELFFile(stream)
        symtab = elf.get_section_by_name(".symtab")
        if symtab is None:
            return records
        relocations = _relocations(elf)
        dwarf = _dwarf_signatures(elf)
        section_symbols = collections.defaultdict(dict)
        for symbol in symtab.iter_symbols():
            index = symbol["st_shndx"]
            if isinstance(index, int) and symbol.name:
                section_symbols[index][int(symbol["st_value"]) & ~1] = symbol.name
        for symbol in symtab.iter_symbols():
            if symbol["st_info"]["type"] != "STT_FUNC" or not symbol.name:
                continue
            size = int(symbol["st_size"])
            section_index = symbol["st_shndx"]
            if size < 2 or not isinstance(section_index, int):
                continue
            section = elf.get_section(section_index)
            if section is None:
                continue
            data = section.data()
            start = (int(symbol["st_value"]) & ~1) - int(section["sh_addr"])
            if start < 0 or start + size > len(data):
                continue
            code = data[start:start + size]
            features = extract_features(
                code, int(symbol["st_value"]) & ~1,
                section_data=data, section_address=int(section["sh_addr"]),
                function_offset=start, relocs=relocations.get(section_index, {}),
                symbols_by_address=section_symbols.get(section_index, {}))
            relative_object = os.path.realpath(path)
            identifier = "%s::%s::%s" % (relative_object, section.name, symbol.name)
            signatures = dwarf.get(symbol.name, [])
            record = {
                "id": identifier,
                "name": symbol.name,
                "object": relative_object,
                "section": section.name,
                "source": source,
                "symbol_size": size,
                "binding": str(symbol["st_info"]["bind"]),
                "signature": signatures[0] if len(signatures) == 1 else None,
                "signature_variants": signatures if len(signatures) > 1 else [],
            }
            record.update(features)
            records.append(record)
    return records


def build_index(core, build_root, object_roots, source_roots):
    provenance, commands = _compile_database(build_root)
    objects = set(provenance)
    for root in object_roots:
        for directory, _, files in os.walk(root):
            objects.update(os.path.realpath(os.path.join(directory, name))
                           for name in files if name.endswith((".obj", ".o")))
    fallback = _source_fallback(source_roots)
    records = []
    for path in sorted(objects):
        if not os.path.exists(path):
            continue
        source = provenance.get(path)
        if not source:
            stem = os.path.basename(path).split(".")[0]
            source = fallback.get(stem)
        try:
            records.extend(index_object(path, source))
        except Exception as error:
            print("warning: skipped %s: %s" % (path, error))
    records.sort(key=lambda row: row["id"])
    return {"schema": 1, "core": core, "build_root": os.path.realpath(build_root),
            "compile_commands": len(commands), "object_count": len(objects),
            "function_count": len(records), "records": records}


def self_test():
    # movs r0,#1; cbz r0,+0; bx lr -- stable expected features.
    code = bytes.fromhex("012000b100477047")
    first = extract_features(code, 0x1000)
    second = extract_features(code, 0x9000)
    assert first == second
    assert first["mnemonics"][:3] == ["movs", "cbz", "str"] or first["instruction_count"] >= 3
    ids = ["a.o::.text.foo::same", "b.o::.text.foo::same"]
    assert len(set(ids)) == 2
    print("build_upstream_index self-test: PASS")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--core", choices=("app", "net"))
    parser.add_argument("--build-root")
    parser.add_argument("--object-root", action="append", default=[])
    parser.add_argument("--source-root", action="append", default=[])
    parser.add_argument("--output")
    parser.add_argument("--self-test", action="store_true")
    args = parser.parse_args()
    if args.self_test:
        self_test()
        if not args.core:
            return
    if not args.core:
        parser.error("--core is required unless only --self-test is used")
    build_root = args.build_root or DEFAULT_BUILD[args.core]
    output = args.output or "/tmp/g1_upstream_index_%s.json" % args.core
    data = build_index(args.core, build_root, args.object_root,
                       args.source_root or ["/Users/freedomcoder/ncs251"])
    with open(output, "w") as stream:
        json.dump(data, stream, indent=1, sort_keys=False)
        stream.write("\n")
    print("indexed %d functions from %d objects -> %s" %
          (data["function_count"], data["object_count"], output))


if __name__ == "__main__":
    main()
