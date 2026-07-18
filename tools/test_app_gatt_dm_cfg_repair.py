import pathlib
import unittest

import cfg_verify
import extract
from parity import emu, recon


BASE = pathlib.Path("/Users/freedomcoder/Projects/G1disasm2")
APP_SRC = BASE / "recon/app/src"
VERIFIED_SRC = BASE / "recon/verified/src"


class AppGattDmCfgRepairTest(unittest.TestCase):
    def test_uuid_store_cfg_and_mirror(self):
        source = (APP_SRC / "FUN_0004ea28.c").read_text()
        self.assertEqual(source, (VERIFIED_SRC / "FUN_0004ea28.c").read_text())
        self.assertIn("int uuid_store(", source)
        self.assertIn("user_data_alloc(uVar1)", source)
        verdict = cfg_verify.verify("app", "FUN_0004ea28")
        self.assertEqual("PASS", verdict.get("status"), verdict)

    def test_discovery_callback_all_parameter_types(self):
        source = (APP_SRC / "FUN_0004ea78.c").read_text()
        self.assertEqual(source, (VERIFIED_SRC / "FUN_0004ea78.c").read_text())
        self.assertIn("undefined4 discovery_callback(", source)
        self.assertIn("bt_gatt_dm_attr_chrc_val(iVar3)", source)

        compiled, error = recon.compile_func(
            source, "discovery_callback", 0x0004EA78)
        self.assertIsNone(error, error)
        body, tail, candidate_size, candidate_va = compiled
        candidate_target_map = dict(recon.LAST_DIRECT_TARGET_MAP)

        connection = emu.SCRATCH + 0x100
        params = emu.SCRATCH + 0x1000
        overrides = [{0: connection, 1: 0, 2: params} for _ in range(7)]
        relative_memory = [[(2, 0x10, bytes((kind,)))] for kind in range(7)]
        absolute_memory = [[
            (0x2000A154, connection.to_bytes(4, "little")),
            (0x2000A288, (2).to_bytes(4, "little")),
        ] for _ in range(7)]

        # These are the concrete pinned-NCS ABIs, including printk's four
        # register arguments and the zero-argument fatal/discovery helpers.
        arities = {
            0x0004E964: 0, 0x0004E9A0: 2, 0x0004EA28: 1,
            0x0005B9CC: 2, 0x0007E2EC: 2, 0x0007E2FA: 4,
            0x0007F386: 2, 0x0007F406: 3, 0x0007F40C: 2,
            0x0007F438: 1, 0x0007F460: 1, 0x0007F4A0: 1,
            0x00080D3E: 2,
        }
        original_size = cfg_verify.core_ctx("app")["sizes"][0x0004EA78]
        verdict = emu.compare(
            extract.func_bytes_padded(0x0004EA78, original_size, pad=1024),
            0x0004EA78,
            original_size,
            body + tail,
            candidate_va,
            candidate_size,
            trials=7,
            nptr=3,
            arg_overrides=overrides,
            memory_overrides=relative_memory,
            absolute_memory_overrides=absolute_memory,
            terminal_targets={0x0007E2EC},
            call_arity_by_target=arities,
            candidate_direct_target_map=candidate_target_map,
        )
        self.assertTrue(verdict["pass"], verdict.get("detail"))
        self.assertEqual(7, verdict["checked"])

        # Keep the general corpus verifier green as a separate randomized
        # guard for the connection-mismatch path.
        general = cfg_verify.verify("app", "FUN_0004ea78")
        self.assertEqual("PASS", general.get("status"), general)


if __name__ == "__main__":
    unittest.main()
