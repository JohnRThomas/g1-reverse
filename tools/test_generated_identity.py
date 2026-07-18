import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(__file__))
import generated_identity
import function_names
import apply_names


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

    def test_raw_owner_alias_survives_readable_name_generation(self):
        source = (
            "/* net-core FUN_0100d6e8 @ 0x0100d6e8 */\n"
            "bool sdc_conn_recovery_window_update(void) { return true; }\n"
            "extern __typeof(sdc_conn_recovery_window_update) FUN_0100d6e8\n"
            "  __attribute__((alias(\"sdc_conn_recovery_window_update\")));\n"
        )
        rendered = apply_names.render_named_body(
            source, "net", 0x0100D6E8,
            "sdc_conn_recovery_window_update")
        self.assertIn(
            "extern __typeof(sdc_conn_recovery_window_update) FUN_0100d6e8",
            rendered)
        self.assertNotIn(
            "extern __typeof(sdc_conn_recovery_window_update) "
            "sdc_conn_recovery_window_update", rendered)
        self.assertIn(
            'alias("sdc_conn_recovery_window_update")', rendered)

    def test_raw_callees_still_receive_readable_names(self):
        source = (
            "/* net-core FUN_0100d6e8 @ 0x0100d6e8 */\n"
            "extern void FUN_01039e4e(void);\n"
            "void sdc_conn_recovery_window_update(void) { FUN_01039e4e(); }\n"
        )
        rendered = apply_names.render_named_body(
            source, "net", 0x0100D6E8,
            "sdc_conn_recovery_window_update")
        self.assertIn("rtc_pretick_rtc1_isr_hook", rendered)
        self.assertNotIn("extern void FUN_01039e4e", rendered)

    def test_distinct_public_name_retargets_raw_owner_alias(self):
        source = (
            "/* FUN_010269ce @ 0x010269ce: packet helper. */\n"
            "void *controller_packet_payload_reserve(void *packet) {\n"
            "  return packet;\n"
            "}\n"
            "extern __typeof(controller_packet_payload_reserve) FUN_010269ce\n"
            "  __attribute__((alias(\"controller_packet_payload_reserve\")));\n"
        )
        rendered = apply_names.render_named_body(
            source, "net", 0x010269CE,
            "controller_packet_payload_claim_begin")
        self.assertIn(
            "void *controller_packet_payload_claim_begin(void *packet)",
            rendered)
        self.assertIn(
            "extern __typeof(controller_packet_payload_claim_begin) "
            "FUN_010269ce", rendered)
        self.assertIn(
            'alias("controller_packet_payload_claim_begin")', rendered)
        self.assertNotIn(
            "void *controller_packet_payload_reserve(void *packet)", rendered)

    def test_packet_payload_helpers_have_distinct_address_owners(self):
        self.assertEqual(
            0x010269CE,
            function_names.address_for_name(
                "net", "controller_packet_payload_claim_begin"))
        self.assertEqual(
            0x01026E48,
            function_names.address_for_name(
                "net", "controller_packet_payload_reserve"))

    def test_raw_primary_drops_only_redundant_gcc_alias(self):
        source = (
            "/* FUN_01019ef8 @ 0x01019ef8: metadata predicate. */\n"
            "bool sdc_buffer_metadata_matches(void) { return true; }\n"
            "/* Raw identity/back-map: FUN_01019ef8 @ 0x01019ef8. */\n"
            "extern __typeof(sdc_buffer_metadata_matches) FUN_01019ef8\n"
            "  __attribute__((alias(\"sdc_buffer_metadata_matches\")));\n"
        )
        rendered = apply_names.render_named_body(
            source, "net", 0x01019EF8, "FUN_01019ef8")
        self.assertIn("bool FUN_01019ef8(void)", rendered)
        self.assertNotIn("extern __typeof", rendered)
        self.assertNotIn("__attribute__((alias", rendered)
        self.assertIn(
            "Raw identity/back-map: FUN_01019ef8 @ 0x01019ef8",
            rendered)


if __name__ == "__main__":
    unittest.main()
