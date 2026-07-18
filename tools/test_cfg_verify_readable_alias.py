#!/usr/bin/env python3
"""Regression for readable requests backed by raw canonical definitions."""

import unittest

import cfg_verify


class CfgVerifyReadableAliasTest(unittest.TestCase):
    def test_readable_alias_compiles_raw_canonical_owner(self):
        # The durable map names FUN_00051354 as mgmt_find_handler, while the
        # parity source deliberately retains the raw/address definition.  The
        # verifier must link the symbol actually defined by that source.
        result = cfg_verify.verify(
            "app", "mgmt_find_handler", trials_random=1)
        self.assertEqual("PASS", result["status"])

    def test_raw_request_compiles_collision_isolated_alias_owner(self):
        # The public presentation name is the stock nrfx spelling, while the
        # retained firmware body is deliberately namespaced to coexist with
        # that stock owner.  Its durable alias must still resolve when a CFG
        # sweep starts from the raw address identity.
        result = cfg_verify.verify(
            "app", "FUN_00064f48", trials_random=1)
        self.assertEqual("PASS", result["status"])


if __name__ == "__main__":
    unittest.main()
