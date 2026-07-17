import json
import re
import unittest
from pathlib import Path

from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB


ROOT = Path(__file__).resolve().parents[1]
IMAGE = ROOT / "netcore_image.bin"
BASE = 0x01008000
CATALOG = ROOT / "recon/catalogs/net_identity_alias_resolutions.json"


def decode(va, size):
    blob = IMAGE.read_bytes()
    start = va - BASE
    return list(Cs(CS_ARCH_ARM, CS_MODE_THUMB).disasm(
        blob[start:start + size], va))


class NetIdentityAliasResolutionTest(unittest.TestCase):
    def test_catalog_is_exactly_the_nine_reviewed_residues(self):
        report = json.loads(CATALOG.read_text())
        self.assertEqual(report["image_sha256"],
                         "ec4e4b60f3efa5c830084c9dd3ca516f70cfeb81620306e2ebd8a2af158f7ca4")
        self.assertEqual(len(report["resolutions"]), 9)
        self.assertEqual(
            {item["symbol"] for item in report["resolutions"]},
            {
                "FUN_01008fc0", "FUN_01008fc6", "FUN_0100b5f8",
                "FUN_0101077c_after", "controller_assert",
                "controller_radio_timer_capture_get", "controller_time_now",
                "rtc_pretick_rtc1_isr_hook", "sdc_timing_compensation_get",
            },
        )

    def test_original_interior_labels_decode_on_thumb_boundaries(self):
        insns = decode(0x01008FC0, 12)
        self.assertEqual(
            [(i.address, i.mnemonic, i.op_str) for i in insns],
            [
                (0x01008FC0, "mvn", "r0, #0x2c"),
                (0x01008FC4, "b", "#0x1008eca"),
                (0x01008FC6, "mvn", "r0, #0xb"),
                (0x01008FCA, "b", "#0x1008eca"),
            ],
        )
        source = (ROOT / "recon/symbolized/net/FUN_01008e74.c").read_text()
        self.assertIn("static int FUN_01008fc0(void) { return -45; }", source)
        self.assertIn("static int FUN_01008fc6(void) { return -12; }", source)
        self.assertNotRegex(source, r"extern\s+int\s+FUN_01008fc[06]")

    def test_original_tail_veneer_targets_retained_entry(self):
        insns = decode(0x0100B5F8, 4)
        self.assertEqual(len(insns), 1)
        self.assertEqual((insns[0].address, insns[0].mnemonic, insns[0].op_str),
                         (0x0100B5F8, "b.w", "#0x100ac34"))
        fragment = (ROOT / "recon/symbols/g1_net_aliases.ld").read_text()
        self.assertIn("PROVIDE(FUN_0100b5f8 = FUN_0100ac34);", fragment)
        target = (ROOT / "recon/symbolized/net/FUN_0100ac34.c").read_text()
        self.assertRegex(target, r"\bvoid\s+FUN_0100ac34\s*\(")
        rtc = decode(0x01039E4E, 4)
        self.assertEqual(len(rtc), 1)
        self.assertEqual((rtc[0].address, rtc[0].mnemonic, rtc[0].op_str),
                         (0x01039E4E, "b.w", "#0x102cfec"))

    def test_naming_defects_are_closed_without_stale_exports(self):
        expected = {
            "controller_radio_timer_capture_get": "uint32_t",
            "controller_time_now": "uint64_t",
            "rtc_pretick_rtc1_isr_hook": "void",
            "sdc_timing_compensation_get": "uint32_t",
        }
        for name, result_type in expected.items():
            source = (ROOT / ("recon/symbolized/net/%s.c" % name)).read_text()
            self.assertRegex(source, r"\b%s\s+%s\s*\(" %
                             (re.escape(result_type), re.escape(name)))
        all_sources = "\n".join(
            path.read_text() for path in (ROOT / "recon/symbolized/net").glob("*.c")
        )
        self.assertNotIn("FUN_0101077c_after", all_sources)
        self.assertNotIn("controller_assert", all_sources)
        retained = (ROOT / "recon/generated/net_retained_sources.cmake").read_text()
        self.assertNotIn("/rtc_pretick_rtc1_isr_hook.c", retained)
        manifest = json.loads(
            (ROOT / "recon/ownership/adoption_manifest.json").read_text())
        row = next(item for item in manifest["cores"]["net"]["entries"]
                   if item["va"] == "0x01039e4e")
        self.assertTrue(row["exclude_reconstruction"])
        self.assertEqual(row["upstream_symbol"], "rtc_pretick_rtc1_isr_hook")


if __name__ == "__main__":
    unittest.main()
