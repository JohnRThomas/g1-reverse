import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(__file__))
import generated_identity
import function_names


class GeneratedIdentityTest(unittest.TestCase):
    def test_parse(self):
        value = generated_identity.parse(
            "/* readable reconstruction; identity: FUN_0004bfc8 @ 0x0004bfc8\n"
            " * public-name: mpsc_pbuf_free\n */")
        self.assertEqual(value["address"], 0x4bfc8)
        self.assertEqual(value["public_name"], "mpsc_pbuf_free")

    def test_parse_reviewed_raw_identifier(self):
        value = generated_identity.parse(
            "/* readable reconstruction; identity: tail_61200 @ 0x00061200\n"
            " * public-name: flash_nrf_read_invalid_address\n */")
        self.assertEqual(value["address"], 0x61200)
        self.assertEqual(value["raw_name"], "tail_61200")

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

    def test_net_historical_thunk_aliases_become_public_names(self):
        source = (
            "extern unsigned long long thunk_FUN_01025034(void);\n"
            "unsigned long long thunk_FUN_01025034(void) {\n"
            "  return thunk_FUN_01025034();\n"
            "}\n"
            "/* thunk_FUN_01025034 remains provenance text */\n"
        )
        rendered = function_names.substitute(source, "net")
        self.assertIn("controller_time_now(void)", rendered)
        self.assertNotIn("extern unsigned long long thunk_FUN_01025034", rendered)
        self.assertIn("/* thunk_FUN_01025034 remains provenance text */", rendered)

    def test_alias_map_is_bijective(self):
        aliases = function_names.records_by_alias("net")
        self.assertEqual(
            aliases["thunk_FUN_01025028"]["name"],
            "controller_radio_timer_capture_get",
        )
        self.assertEqual(
            aliases["thunk_FUN_0102cfec"]["address"], "0x01039e4e"
        )
        # CPUAPP has two historical owners for this spelling.  It must stay
        # unsubstituted until an address-specific repair selects an identity.
        self.assertNotIn("thunk_FUN_00086c78",
                         function_names.records_by_alias("app"))
        ambiguous = "void thunk_FUN_00086c78(void);"
        self.assertEqual(function_names.substitute(ambiguous, "app"), ambiguous)

    def test_verified_interior_labels_are_local_and_fail_closed(self):
        source = (
            "extern int FUN_01008fc0(void);\n"
            "extern int FUN_01008fc6(void);\n"
            "int FUN_01008e74(void) { return FUN_01008fc0(); }\n"
        )
        repaired = function_names.repair_internal_control_flow_labels(
            source, "net", 0x01008E74)
        self.assertIn("static int FUN_01008fc0(void) { return -45; }", repaired)
        self.assertIn("static int FUN_01008fc6(void) { return -12; }", repaired)
        self.assertNotIn("extern int FUN_01008fc0", repaired)
        with self.assertRaisesRegex(ValueError, "declarations drifted"):
            function_names.repair_internal_control_flow_labels(
                "extern int FUN_01008fc0(void);\n", "net", 0x01008E74)


if __name__ == "__main__":
    unittest.main()
