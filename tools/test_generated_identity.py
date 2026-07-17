import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(__file__))
import generated_identity


class GeneratedIdentityTest(unittest.TestCase):
    def test_parse(self):
        value = generated_identity.parse(
            "/* readable reconstruction; identity: FUN_0004bfc8 @ 0x0004bfc8\n"
            " * public-name: mpsc_pbuf_free\n */")
        self.assertEqual(value["address"], 0x4bfc8)
        self.assertEqual(value["public_name"], "mpsc_pbuf_free")

    def test_rejects_filename_collision_before_write(self):
        planned, identities = {}, {}
        generated_identity.add(planned, identities, "same.c", 0x1000, "a.c", "a")
        with self.assertRaisesRegex(ValueError, "filename collision"):
            generated_identity.add(planned, identities, "same.c", 0x2000, "b.c", "b")

    def test_rejects_duplicate_address_before_write(self):
        planned, identities = {}, {}
        generated_identity.add(planned, identities, "a.c", 0x1000, "a.c", "a")
        with self.assertRaisesRegex(ValueError, "duplicate generated identity"):
            generated_identity.add(planned, identities, "b.c", 0x1000, "b.c", "b")


if __name__ == "__main__":
    unittest.main()
