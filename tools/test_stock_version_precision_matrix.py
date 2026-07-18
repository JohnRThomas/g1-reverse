import importlib.util
import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "stock_version_precision",
    ROOT / "tools/build_stock_version_precision_matrix.py")
BUILDER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(BUILDER)


class StockVersionPrecisionMatrixTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.catalog = json.loads((
            ROOT / "recon/catalogs/stock_version_precision_matrix.json"
        ).read_text())

    def test_catalog_is_reproducible_from_local_tags_and_archives(self):
        self.assertEqual(BUILDER.build(), self.catalog)

    def test_private_dirty_zephyr_is_not_public_baseline(self):
        identity = self.catalog["firmware_identity"]
        self.assertEqual(
            "1b8581519f7aaeef086c6a3d3df59479b2a337d2-dirty",
            identity["zephyr_reported_revision"])
        self.assertFalse(identity["zephyr_reported_commit_available_locally"])
        self.assertNotIn(
            identity["public_ncs_2_5_1_zephyr_baseline"],
            identity["zephyr_reported_revision"])

    def test_nrfxlib_archive_families_are_exact_and_narrow(self):
        families = self.catalog["binary_equivalence_families"]
        for key in ("mpsl_net_exact_archive",
                    "sdc_multirole_net_exact_archive"):
            self.assertEqual(
                ["v2.5.0", "v2.5.1"], families[key]["ncs_releases"])
            self.assertIn("v2.5.2", families[key]["excludes_sampled"])
        self.assertEqual(
            "report_only_private_sdc",
            families["sdc_multirole_net_exact_archive"][
                "adoption_authority"])

    def test_adjacent_manifests_distinguish_stable_and_changing_modules(self):
        rows = {row["ncs_release"]: row
                for row in self.catalog["adjacent_ncs_manifests"]}
        modules = lambda release: rows[release]["zephyr_imported_modules"]
        self.assertEqual(modules("v2.5.0")["liblc3"]["commit"],
                         modules("v2.6.0")["liblc3"]["commit"])
        self.assertEqual(modules("v2.5.0")["tinycrypt"]["commit"],
                         modules("v2.6.0")["tinycrypt"]["commit"])
        self.assertNotEqual(modules("v2.5.0")["hal_nordic"]["commit"],
                            modules("v2.5.1")["hal_nordic"]["commit"])
        self.assertNotEqual(modules("v2.5.1")["zcbor"]["commit"],
                            modules("v2.6.0")["zcbor"]["commit"])

    def test_libc_proof_is_per_core_and_different_strength(self):
        cores = self.catalog["toolchain_by_core"]
        self.assertIn("newlib-nano", cores["app"]["libc"])
        self.assertIn("exact archive members", cores["app"]["proof"])
        self.assertIn("picolibc", cores["net"]["libc"].lower())
        self.assertIn("no firmware whole-archive proof",
                      cores["net"]["proof"])
        self.assertNotEqual(cores["app"]["libc_archive_sha256"],
                            cores["net"]["reference_libc_archive_sha256"])

    def test_claim_model_prevents_common_overclaims(self):
        model = set(self.catalog["claim_model"])
        self.assertIn("archive_blob_identity", model)
        self.assertIn("selected_member_or_section_identity", model)
        self.assertIn("source_body_interval", model)
        policy = self.catalog["policy"]
        self.assertTrue(policy["manifest_pin_is_not_binary_unique"])
        self.assertTrue(policy["body_match_is_not_whole_archive_identity"])


if __name__ == "__main__":
    unittest.main()
