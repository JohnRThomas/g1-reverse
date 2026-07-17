#!/usr/bin/env python3
"""Regression coverage for tx_notify's reviewed IRQ normalization."""

import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(__file__))

import cfg_verify
import extract


ROOT = os.path.dirname(os.path.dirname(__file__))
SOURCE = os.path.join(ROOT, "recon", "app", "src", "tx_notify.c")


class TxNotifyCfgVerifyTests(unittest.TestCase):
    def test_exact_irq_patterns_are_the_only_normalized_bytes(self):
        original = extract.read(0x00056020, 92)
        normalized = cfg_verify._normalize_tx_notify_irq_masking(
            original, require_reviewed_pattern=True)
        self.assertEqual(len(normalized), len(original))
        for pattern, _count, _description in cfg_verify._TX_NOTIFY_IRQ_PATTERNS:
            self.assertNotIn(pattern, normalized)

        unrelated = bytes.fromhex("0123456789abcdef")
        self.assertEqual(
            cfg_verify._normalize_tx_notify_irq_masking(unrelated), unrelated)

    def test_file_backed_reconstruction_passes_all_queue_fixtures(self):
        verdict = cfg_verify.verify("app", "tx_notify", trials_random=1)
        self.assertEqual(verdict.get("status"), "PASS", verdict)
        self.assertEqual(verdict.get("checked"), 3, verdict)

    def test_missing_tail_update_fails(self):
        with open(SOURCE) as source_file:
            source = source_file.read()
        original = "*(uint8_t **)(connection + 0x24u) = next;"
        self.assertIn(original, source)
        mutated = source.replace(original, "(void)next;", 1)
        verdict = cfg_verify.verify(
            "app", "tx_notify", trials_random=1, source_override=mutated)
        self.assertEqual(verdict.get("status"), "FAIL", verdict)

    def test_callback_before_free_fails(self):
        with open(SOURCE) as source_file:
            source = source_file.read()
        ordered = ("        k_fifo_put((void *)0x20003a60u, tx);\n"
                   "        callback(connection, user_data, 0);")
        reordered = ("        callback(connection, user_data, 0);\n"
                     "        k_fifo_put((void *)0x20003a60u, tx);")
        self.assertIn(ordered, source)
        verdict = cfg_verify.verify(
            "app", "tx_notify", trials_random=1,
            source_override=source.replace(ordered, reordered, 1))
        self.assertEqual(verdict.get("status"), "FAIL", verdict)


if __name__ == "__main__":
    unittest.main()
