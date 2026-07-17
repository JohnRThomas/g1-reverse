import hashlib
import json
import re
import unittest
from pathlib import Path

from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB


ROOT = Path(__file__).resolve().parents[1]
IMAGE = ROOT / "netcore_image.bin"
BASE = 0x01008000
CATALOG = ROOT / "recon/catalogs/net_data_alias_resolutions.json"


def decode(va, size):
    blob = IMAGE.read_bytes()
    start = va - BASE
    return list(Cs(CS_ARCH_ARM, CS_MODE_THUMB).disasm(
        blob[start:start + size], va))


def literal_u32(blob, instruction):
    match = re.search(r"#(0x[0-9a-f]+|\d+)", instruction.op_str)
    if not match:
        raise AssertionError("missing PC-relative immediate: %s" % instruction.op_str)
    address = ((instruction.address + 4) & ~3) + int(match.group(1), 0)
    start = address - BASE
    return int.from_bytes(blob[start:start + 4], "little")


class NetDataAliasResolutionTest(unittest.TestCase):
    def setUp(self):
        self.report = json.loads(CATALOG.read_text())
        self.row = self.report["resolutions"][0]
        self.blob = IMAGE.read_bytes()

    def test_catalog_is_bound_to_the_original_image_and_one_reviewed_alias(self):
        self.assertEqual(hashlib.sha256(self.blob).hexdigest(),
                         self.report["image_sha256"])
        self.assertEqual(len(self.report["resolutions"]), 1)
        self.assertEqual(self.row["symbol"], "g_21000ea7")
        self.assertEqual(self.row["base_address"], "0x21000ea6")
        self.assertEqual(self.row["offset"], 1)
        self.assertEqual(self.row["access_width"], 1)
        self.assertEqual(self.row["object_width"], 2)
        self.assertEqual(self.row["next_object_address"], "0x21000ea8")

    def test_original_thumb_accesses_prove_base_offset_width_and_boundary(self):
        first = decode(0x0100D738, 0x22)
        first_load = first[0]
        self.assertEqual((first_load.mnemonic, literal_u32(self.blob, first_load)),
                         ("ldr", 0x21000EA6))
        self.assertEqual((first[1].mnemonic, first[1].op_str),
                         ("ldrb", "r3, [r3]"))

        second = decode(0x0100D760, 0x48)
        base_load = next(i for i in second if i.address == 0x0100D77E)
        byte_load = next(i for i in second if i.address == 0x0100D784)
        self.assertEqual(literal_u32(self.blob, base_load), 0x21000EA6)
        self.assertEqual((byte_load.mnemonic, byte_load.op_str),
                         ("ldrb", "r0, [r2, #1]"))

        clear = decode(0x0100D7AC, 10)
        self.assertEqual(literal_u32(self.blob, clear[0]), 0x21000EA6)
        self.assertEqual([(i.mnemonic, i.op_str) for i in clear[2:4]],
                         [("strb", "r2, [r3]"),
                          ("strb", "r2, [r3, #1]")])

        following = decode(0x0100D7BC, 0x1E)
        self.assertEqual(literal_u32(self.blob, following[0]), 0x21000EA8)
        self.assertEqual((following[1].mnemonic, following[1].op_str),
                         ("ldrb", "r2, [r3]"))

    def test_alias_allocates_no_storage_and_base_type_cannot_overlap_next_object(self):
        aliases = (ROOT / "recon/symbols/g1_net_aliases.ld").read_text()
        globals_ld = (ROOT / "recon/symbols/g1_net_globals.ld").read_text()
        header = (ROOT / "recon/symbols/g1_net_symbols.h").read_text()
        self.assertIn(self.row["linker_expression"], aliases)
        self.assertNotRegex(globals_ld, r"PROVIDE\(g_21000ea7\s*=")
        self.assertIn("PROVIDE(g_net_rssi_cal_offset = 0x21000ea6);", globals_ld)
        self.assertIn("PROVIDE(g_net_esb_own_addr_valid = 0x21000ea8);", globals_ld)
        self.assertIn(
            "extern volatile unsigned char g_net_rssi_cal_offset;", header)
        self.assertNotIn(
            "extern volatile unsigned int g_net_rssi_cal_offset;", header)

    def test_refgraph_callers_and_direct_data_references_match_catalog(self):
        import gzip
        with gzip.open(ROOT / "recon/catalogs/refgraph_net.json.gz", "rt") as stream:
            graph = json.load(stream)["functions"]
        expected = self.row["callers"]
        for raw_name, callers in expected.items():
            entry = next(item for item in graph.values()
                         if item["name"] == raw_name)
            self.assertEqual(entry["callers"],
                             ["0x" + name.removeprefix("FUN_0").lower()
                              for name in callers])
        refs = self.row["direct_function_references"]
        for address, functions in refs.items():
            actual = sorted(item["name"] for item in graph.values()
                            if address in item.get("data_refs", []))
            self.assertEqual(actual, sorted(functions))


if __name__ == "__main__":
    unittest.main()
