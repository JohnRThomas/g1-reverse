#!/usr/bin/env python3
import json
import os
import sys
import tempfile
import unittest

TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
import build_app_sdk_public_ownership as ownership


class AppSdkPublicOwnershipTest(unittest.TestCase):
    def test_all_gates_and_fail_closed_collision(self):
        with tempfile.TemporaryDirectory() as root:
            residue = os.path.join(root, "residue.json")
            names = os.path.join(root, "names.json")
            link_map = os.path.join(root, "zephyr.map")
            env = {"revisions": {"zephyr": "a" * 40}}
            rows = [{
                "symbol": "FUN_00001000", "semantic_owner": "public_ok",
                "signature_ratio": 1.0, "firmware_identities": ["0x00001000"],
                "archive_evidence": {"member": "ok.c.obj", "nm_type": "T",
                                     "linkage": "public", "archive": "lib.a"},
                "owning_config": ["CONFIG_OK=y"],
                "safe_automatic_link_owner": True,
                "adoption_evidence_gate": "exact_signature", "reference_count": 3,
            }, {
                "symbol": "z_log_dropped_read_and_clear_0",
                "semantic_owner": "public_collision", "signature_ratio": None,
                "firmware_identities": ["0x00002000"],
                "archive_evidence": {"member": "log.c.obj", "nm_type": "T",
                                     "linkage": "public", "archive": "lib.a"},
                "owning_config": ["CONFIG_LOG=y"],
                "safe_automatic_link_owner": False,
                "adoption_evidence_gate": "not_a_public_link_candidate",
                "reference_count": 1,
            }]
            with open(residue, "w") as stream:
                json.dump({"pinned_environment": env, "entries": rows}, stream)
            with open(names, "w") as stream:
                json.dump({"by_name": {"public_ok": "0x00001000",
                                       "public_collision": "0x00003000"}}, stream)
            with open(link_map, "w") as stream:
                stream.write(" .text.public_ok\n"
                             "  0x00001000 0x10 lib.a(ok.c.obj)\n"
                             " .text.public_collision\n"
                             "  0x00002000 0x10 lib.a(log.c.obj)\n")
            data = ownership.build(residue, names, link_map)
            by_name = {row["upstream_symbol"]: row for row in data["functions"]}
            self.assertTrue(by_name["public_ok"]["safe_to_adopt"])
            self.assertFalse(by_name["public_collision"]["safe_to_adopt"])
            self.assertIn("public_name_owned_by_distinct_firmware_va",
                          by_name["public_collision"]["blockers"])
            self.assertEqual(3, data["summary"]["resolved_reference_count"])


if __name__ == "__main__":
    unittest.main()
