"""Fail-closed proofs for the three reviewed CPUNET read-only link gaps."""
import hashlib
import json
import re
import unittest
from pathlib import Path

from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB


ROOT = Path(__file__).resolve().parents[1]
IMAGE = ROOT / "netcore_image.bin"
BASE = 0x01008000
CATALOG = ROOT / "recon/catalogs/net_rodata_gap_resolutions.json"


def decode(blob, va, size):
    start = va - BASE
    return list(Cs(CS_ARCH_ARM, CS_MODE_THUMB).disasm(
        blob[start:start + size], va))


def literal_u32(blob, instruction):
    match = re.search(r"#(0x[0-9a-f]+|\d+)", instruction.op_str)
    if not match:
        raise AssertionError("not a PC-relative load: %s" % instruction.op_str)
    address = ((instruction.address + 4) & ~3) + int(match.group(1), 0)
    start = address - BASE
    return address, int.from_bytes(blob[start:start + 4], "little")


class NetRodataGapResolutionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.blob = IMAGE.read_bytes()
        cls.report = json.loads(CATALOG.read_text())
        cls.rows = {row["symbol"]: row for row in cls.report["resolutions"]}

    def test_catalog_is_image_bound_and_complete(self):
        self.assertEqual(hashlib.sha256(self.blob).hexdigest(),
                         self.report["image_sha256"])
        self.assertEqual(set(self.rows), {
            "rodata_103a749", "rodata_103c190", "rodata_103c4cc"})
        self.assertTrue(self.report["policy"]["never_duplicate_overlapping_storage"])

    def test_103a749_is_seventh_argument_thumb_value_not_storage(self):
        ins = decode(self.blob, 0x0102D69C, 0x40)
        load = next(item for item in ins if item.address == 0x0102D6A0)
        self.assertEqual(literal_u32(self.blob, load),
                         (0x0102D6DC, 0x0103A749))
        self.assertEqual((ins[4].mnemonic, ins[4].op_str),
                         ("str", "r1, [sp, #8]"))
        self.assertEqual(0x0103A749 & 1, 1)
        containing = decode(self.blob, 0x0103A746, 4)[0]
        self.assertEqual((containing.mnemonic, containing.size), ("bl", 4))
        self.assertLess(containing.address, 0x0103A748)
        self.assertGreater(containing.address + containing.size, 0x0103A748)
        self.assertEqual(self.rows["rodata_103a749"]["storage_span"], 0)

    def test_103c190_both_users_bound_index_to_42(self):
        first = decode(self.blob, 0x0100E610, 0x20)
        self.assertEqual((first[2].mnemonic, first[2].op_str),
                         ("ldrb", "r2, [r0, #3]"))
        self.assertEqual((first[3].mnemonic, first[3].op_str),
                         ("cmp", "r2, #0x2a"))
        load = next(item for item in first if item.address == 0x0100E61A)
        self.assertEqual(literal_u32(self.blob, load)[1], 0x0103C190)
        self.assertEqual((first[6].mnemonic, first[6].op_str),
                         ("ldrb", "r0, [r1, r2]"))

        second = decode(self.blob, 0x0100E634, 0x24)
        self.assertEqual((second[0].mnemonic, second[0].op_str),
                         ("cmp", "r1, #0x2a"))
        load = next(item for item in second if item.address == 0x0100E63C)
        self.assertEqual(literal_u32(self.blob, load),
                         (0x0100E658, 0x0103C190))
        indexed = next(item for item in second if item.address == 0x0100E63E)
        self.assertEqual((indexed.mnemonic, indexed.op_str),
                         ("ldrb", "r3, [r3, r1]"))

    def test_103c190_definition_is_exact_and_does_not_claim_next_table(self):
        row = self.rows["rodata_103c190"]
        expected = self.blob[0x0103C190 - BASE:0x0103C190 - BASE + 43]
        self.assertEqual(len(expected), row["storage_span"])
        self.assertEqual(hashlib.sha256(expected).hexdigest(), row["sha256"])
        source = (ROOT / row["source"]).read_text()
        initializer = source.split("= {", 1)[1].split("};", 1)[0]
        actual = bytes(int(token, 16) for token in
                       re.findall(r"0x([0-9a-fA-F]{2})", initializer))
        self.assertEqual(actual, expected)
        self.assertIn("aligned(4)", source)
        self.assertEqual(0x0103C190 + len(actual), 0x0103C1BB)
        self.assertEqual(0x0103C1BC - (0x0103C190 + len(actual)), 1)

    def test_103c4cc_is_three_byte_interior_string_alias(self):
        row = self.rows["rodata_103c4cc"]
        start = 0x0103C468 - BASE
        end = self.blob.index(0, start) + 1
        whole = self.blob[start:end]
        self.assertEqual(whole[:-1].decode(), row["containing_string"])
        self.assertEqual(self.blob[0x0103C4CC - BASE:0x0103C4CF - BASE],
                         bytes.fromhex(row["accessed_bytes_hex"]))
        ins = decode(self.blob, 0x0101FDD0, 0xC8)
        self.assertEqual((next(i for i in ins if i.address == 0x0101FE30).mnemonic,
                          next(i for i in ins if i.address == 0x0101FE30).op_str),
                         ("cmp", "r7, #2"))
        load = next(i for i in ins if i.address == 0x0101FE34)
        self.assertEqual(literal_u32(self.blob, load),
                         (0x0101FE90, 0x0103C4CC))
        indexed = next(i for i in ins if i.address == 0x0101FE3A)
        self.assertEqual((indexed.mnemonic, indexed.op_str),
                         ("ldrb", "r1, [r1, r7]"))

    def test_aliases_allocate_no_storage_and_shell_selects_one_table_owner(self):
        aliases = (ROOT / "recon/symbols/g1_net_aliases.ld").read_text()
        globals_ld = (ROOT / "recon/symbols/g1_net_globals.ld").read_text()
        cmake = (ROOT / "recon/application/net/CMakeLists.txt").read_text()
        for name in ("rodata_103a749", "rodata_103c4cc"):
            self.assertIn(self.rows[name]["linker_expression"], aliases)
            self.assertNotRegex(globals_ld, r"PROVIDE\(%s\s*=" % name)
            definitions = []
            for path in (ROOT / "recon/net/data").glob("*.c"):
                if re.search(r"\b%s\s*\[" % name, path.read_text()):
                    definitions.append(path)
            self.assertEqual(definitions, [])
        self.assertIn("PROVIDE(rodata_103c4d0 = 0x0103c4d0);", globals_ld)
        self.assertEqual(cmake.count("rodata_0x103c190.c"), 1)


if __name__ == "__main__":
    unittest.main()
