import json
import pathlib
import unittest


BASE = pathlib.Path(__file__).resolve().parents[1]
EVIDENCE = BASE / "recon/analysis/net_pseudo_lowerings.json"


class NetPseudoLoweringsTest(unittest.TestCase):
    def test_all_six_residues_have_exact_non_stub_resolutions(self):
        data = json.loads(EVIDENCE.read_text())
        symbols = [entry["symbol"] for entry in data["entries"]]
        self.assertEqual(symbols, [
            "FUN_shadow_default", "PHANTOM_BOUNDARY", "PHANTOM_RETRY",
            "g1_arch_runtime_exception", "g1_irq_lock", "g1_irq_unlock",
        ])
        self.assertEqual(data["summary"], {
            "input_symbols": 6, "resolved_symbols": 6,
            "explicit_blockers": 0,
        })
        self.assertFalse(data["policy"]["weak_stubs"])
        self.assertFalse(data["policy"]["binary_blobs"])
        for entry in data["entries"]:
            self.assertTrue(entry["evidence"])
            self.assertIn("PASS", entry["cfg_verify"])

    def test_synthetic_tokens_are_removed_from_canonical_owners(self):
        owners = [
            "FUN_01029d76.c", "FUN_01017f7c.c", "FUN_0102b900.c",
            "FUN_01031928.c", "FUN_01008ddc.c",
        ]
        forbidden = (
            "PHANTOM_BOUNDARY", "PHANTOM_RETRY",
            "g1_arch_runtime_exception", "g1_irq_lock", "g1_irq_unlock",
        )
        text = "\n".join(
            (BASE / "recon/net/src" / name).read_text() for name in owners
        )
        for token in forbidden:
            self.assertNotIn(token, text)

    def test_cfg_boundary_has_one_strong_retained_owner(self):
        owner = BASE / "recon/application/net/src/cfg_boundary_lowerings.c"
        self.assertIn("unsigned int FUN_shadow_default(void)", owner.read_text())
        cmake = (BASE / "recon/application/net/CMakeLists.txt").read_text()
        self.assertIn("src/cfg_boundary_lowerings.c", cmake)


if __name__ == "__main__":
    unittest.main()
