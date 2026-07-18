#!/usr/bin/env python3
"""Unit tests for the CPUAPP candidate root-topology map parser."""

import unittest

from tools import check_app_root_topology as gate


MAP = """
  0x1000 __init_PRE_KERNEL_1_start
  0x1088 __init_PRE_KERNEL_2_start
  0x1090 __init_POST_KERNEL_start
  opt3001.c.obj
  npm1300_charger.c.obj
  app/libapp.a(g1_lsm6dso_device.c.obj)
  sync_rtc.c.obj
  0x1170 __init_APPLICATION_start
  0x1180 __init_SMP_start
device_area
  0x2000 _device_list_start
  dmic_nrfx_pdm.c.obj
  app/libapp.a(g1_lsm6dso_device.c.obj)
  npm1300_charger.c.obj
  opt3001.c.obj
  0x2270 _device_list_end
"""


class AppRootTopologyGateTest(unittest.TestCase):
    def test_exact_counts(self):
        counts, devices = gate.topology_from_map(MAP)
        self.assertEqual(gate.EXPECTED_INIT_COUNTS, counts)
        self.assertEqual(26, devices)

    def test_firmware_order(self):
        self.assertTrue(gate.ordered(MAP, (
            "opt3001.c.obj", "npm1300_charger.c.obj", gate.LSM_OBJECT,
            "sync_rtc.c.obj")))
        self.assertTrue(gate.ordered(MAP[MAP.index("device_area"):], (
            "dmic_nrfx_pdm.c.obj", gate.LSM_OBJECT,
            "npm1300_charger.c.obj", "opt3001.c.obj")))

    def test_count_drift_is_visible(self):
        counts, _ = gate.topology_from_map(MAP.replace(
            "0x1170 __init_APPLICATION_start",
            "0x1168 __init_APPLICATION_start"))
        self.assertNotEqual(gate.EXPECTED_INIT_COUNTS, counts)


if __name__ == "__main__":
    unittest.main()
