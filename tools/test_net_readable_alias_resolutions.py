import json
import subprocess
import sys
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build_net_readable_alias_resolutions as builder


class NetReadableAliasResolutionTest(unittest.TestCase):
    def test_catalog_is_complete_and_fail_closed(self):
        catalog = builder.validate()
        self.assertEqual(len(catalog["retained_aliases"]), 42)
        self.assertEqual(len(catalog["sdk_owners"]), 6)
        self.assertEqual(
            {row["symbol"] for row in catalog["unresolved"]},
            {"controller_default_bounds_build", "controller_timing_defaults_apply"},
        )

    def test_fragment_is_deterministic(self):
        catalog = builder.validate()
        self.assertEqual(
            builder.render(catalog),
            (ROOT / "recon/symbols/g1_net_readable_aliases.ld").read_text(),
        )
        self.assertEqual(
            builder.render_markdown(catalog),
            (ROOT / "recon/catalogs/net_readable_alias_resolutions.md").read_text(),
        )

    def test_every_alias_target_is_defined_by_retain_all_link(self):
        nm = ("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
              "arm-zephyr-eabi-nm")
        output = subprocess.run(
            [nm, "-g", str(ROOT / "build/net_full.elf")], check=True,
            capture_output=True, text=True).stdout
        defined = {line.split()[-1] for line in output.splitlines()
                   if len(line.split()) >= 3 and line.split()[-2] != "U"}
        catalog = json.loads(
            (ROOT / "recon/catalogs/net_readable_alias_resolutions.json").read_text())
        missing = sorted({row["target"] for row in catalog["retained_aliases"]}
                         - defined)
        self.assertEqual(missing, [])


if __name__ == "__main__":
    unittest.main()
