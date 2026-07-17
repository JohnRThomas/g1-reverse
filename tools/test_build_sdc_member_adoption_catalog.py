#!/usr/bin/env python3
"""Tests for complete-object SDC adoption's fail-closed gates."""
import importlib.util
import os
import unittest


PATH = os.path.join(os.path.dirname(__file__), "build_sdc_member_adoption_catalog.py")
SPEC = importlib.util.spec_from_file_location("sdc_member", PATH)
S = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(S)


def stats(functions=1, exec_sections=1, data_sections=0):
    return {
        "defined_functions": functions,
        "executable_sections": exec_sections,
        "allocated_data_sections": data_sections,
    }


def extraction(selected=True):
    return {"archive": {"sha256": S.EXPECTED_ARCHIVE_SHA256,
                        "selected_by_link": selected}}


def match(address="0x01000000", abi="published_header_declaration"):
    return {"address": address, "match_kind": "exact", "unique_identity": True,
            "abi_status": abi}


def proof(**overrides):
    value = {"build_completed": True, "collision_free": True,
             "hidden_state_preserved": True}
    value.update(overrides)
    return value


class MemberDecisionTest(unittest.TestCase):
    def test_complete_member_can_pass_only_all_gates(self):
        result = S.evaluate_member(
            stats(), [match()], [{"va": "0x01000000"}], extraction(),
            data_owner_mappings=0, retain_all_proof=proof())
        self.assertTrue(result["safe_to_adopt_complete_member"])
        self.assertEqual("adopt_complete_archive_member", result["decision"])

    def test_one_unmatched_target_fails_closed(self):
        result = S.evaluate_member(
            stats(), [match()], [{"va": "0x01000004"}], extraction(),
            retain_all_proof=proof())
        self.assertFalse(result["safe_to_adopt_complete_member"])
        self.assertIn("every_target_residue_mapped", result["blockers"])

    def test_partial_executable_mapping_fails_closed(self):
        result = S.evaluate_member(
            stats(functions=2, exec_sections=2), [match()],
            [{"va": "0x01000000"}], extraction(), retain_all_proof=proof())
        self.assertIn("every_executable_owner_exact_unique", result["blockers"])

    def test_unpublished_private_abi_fails_closed(self):
        result = S.evaluate_member(
            stats(), [match(abi="private_unpublished")],
            [{"va": "0x01000000"}], extraction(), retain_all_proof=proof())
        self.assertIn("every_private_abi_accounted", result["blockers"])

    def test_unmapped_data_state_fails_closed(self):
        result = S.evaluate_member(
            stats(data_sections=2), [match()], [{"va": "0x01000000"}],
            extraction(), data_owner_mappings=1, retain_all_proof=proof())
        self.assertIn("every_allocated_data_section_owned", result["blockers"])

    def test_normal_gc_or_collision_probe_is_not_retain_all_proof(self):
        result = S.evaluate_member(
            stats(), [match()], [{"va": "0x01000000"}], extraction(),
            retain_all_proof={"build_completed": True})
        self.assertIn("retain_all_collision_free", result["blockers"])
        self.assertIn("retain_all_hidden_state_preserved", result["blockers"])

    def test_unpinned_or_unselected_archive_fails_closed(self):
        wrong = extraction(selected=False)
        wrong["archive"]["sha256"] = "0" * 64
        result = S.evaluate_member(
            stats(), [match()], [{"va": "0x01000000"}], wrong,
            retain_all_proof=proof())
        self.assertIn("archive_hash_pinned", result["blockers"])
        self.assertIn("member_selected_by_link", result["blockers"])


if __name__ == "__main__":
    unittest.main()
