"""Regression tests for durable function-name catalog construction."""

import collections
import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(__file__))
import build_function_names as names
import function_names


class SourceHeaderTests(unittest.TestCase):
    def test_repaired_l2cap_identity_does_not_cascade_through_stale_alias(self):
        self.assertEqual(
            "void bt_l2cap_le_lookup_tx_cid(void);",
            function_names.substitute(
                "void FUN_00081a4e(void);", "app"))

    def test_long_generated_provenance_does_not_truncate_entry_address(self):
        original_base = names.BASE
        try:
            with tempfile.TemporaryDirectory() as root:
                names.BASE = root
                source = os.path.join(root, "recon/net/src")
                named = os.path.join(root, "recon/net/named")
                os.makedirs(source)
                os.makedirs(named)
                text = (
                    "/* readable reconstruction; identity: FUN_010144e4 "
                    "@ 0x010144e4\n" + " * provenance padding\n" * 80 + " */\n"
                    "/* net-core FUN_010144e4 @ 0x10144e4 */\n"
                    "void FUN_010144e4(void) {}\n"
                )
                with open(os.path.join(named, "FUN_010144e4.c"), "w") as stream:
                    stream.write(text)

                candidates = collections.defaultdict(list)
                names.source_headers("net", candidates)

                self.assertIn(0x010144E4, candidates)
                self.assertNotIn(0x0010144E, candidates)
        finally:
            names.BASE = original_base


if __name__ == "__main__":
    unittest.main()
