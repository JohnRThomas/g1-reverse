import importlib.util
import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "net_ipc_stock", ROOT / "tools/build_net_ipc_openamp_libmetal_stock_adoption.py")
BUILDER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(BUILDER)
RECEIPT = ROOT / "recon/ownership/net_ipc_openamp_libmetal_stock_adoption.json"


class NetIpcOpenampLibmetalStockAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_receipt_reproduces_from_exact_configured_objects(self):
        self.assertEqual(BUILDER.build(), self.receipt)

    def test_requested_identity_set_and_raw_backmaps(self):
        self.assertEqual({
            "0x010353ec": ("FUN_010353ec", "virtqueue_add_consumed_buffer"),
            "0x0103ab0e": ("FUN_0103ab0e", "metal_io_block_write"),
            "0x0103ac50": ("FUN_0103ac50", "virtqueue_get_available_buffer"),
            "0x0103a056": ("FUN_0103a056", "ipc_static_vrings_shm_size"),
        }, {row["va"]: (row["raw_identity"], row["resolved_identity"])
            for row in self.receipt["functions"]})
        self.assertTrue(all(row["preserve_raw_backmap"]
                            for row in self.receipt["functions"]))

    def test_relocations_close_only_over_proven_helpers(self):
        rows = self.receipt["functions"] + self.receipt["supporting_helper_closure"]
        self.assertTrue(all(not row["mutable_state_relocations"] for row in rows))
        relocs = {row.get("resolved_identity", row.get("identity")):
                  {rel["symbol"]: rel["resolved_target"]
                   for rel in row["executable_relocations"]}
                  for row in rows if row["executable_relocations"]}
        self.assertEqual({
            "metal_io_phys_to_virt": {"metal_io_phys": "0x0103ab86"},
            "virtqueue_get_available_buffer": {
                "metal_io_phys_to_virt": "0x0103abbe"},
        }, relocs)

    def test_all_recorded_callers_resolve_exactly(self):
        for row in self.receipt["functions"]:
            self.assertTrue(row["callers"])
            for caller in row["callers"]:
                for call in caller["direct_calls"]:
                    self.assertEqual(row["va"], call["resolved_target"])

    def test_configuration_and_version_claim_are_precise(self):
        self.assertTrue(self.receipt["units"]["openamp"]["compile_contract"]
                        ["virtio_device_only"])
        self.assertFalse(self.receipt["units"]["libmetal"]["compile_contract"]
                         ["virtio_device_only"])
        self.assertEqual("v3.4.99-ncs1-1",
                         self.receipt["configured_sdk"]["zephyr"])
        self.assertTrue(self.receipt["version_claim"]
                        ["module_revisions_are_shared_across_ncs_2_4_through_2_6"])

    def test_scope_does_not_remove_private_code_or_regenerate_shared_outputs(self):
        self.assertTrue(self.receipt["policy"]["no_private_or_sdc_removal"])
        self.assertTrue(self.receipt["policy"]["shared_generated_trees_not_regenerated"])


if __name__ == "__main__":
    unittest.main()
