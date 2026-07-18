import json
import subprocess
import sys
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build_app_readable_alias_resolutions as builder


class AppReadableAliasResolutionTest(unittest.TestCase):
    def test_catalog_is_complete_and_fail_closed(self):
        catalog = builder.validate()
        self.assertEqual({row["symbol"] for row in catalog["aliases"]}, {
            "dispatch_hci_event", "process_number_completed_packets",
            "version_string",
        })

    def test_fragment_is_deterministic(self):
        catalog = builder.validate()
        self.assertEqual(builder.render(catalog), builder.OUTPUT.read_text())
        self.assertEqual(builder.render_markdown(catalog),
                         builder.MARKDOWN.read_text())

    def test_every_alias_target_is_defined_by_retain_all_link(self):
        nm = ("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
              "arm-zephyr-eabi-nm")
        output = subprocess.run(
            [nm, "-g", str(ROOT / "build/app_full.elf")], check=True,
            capture_output=True, text=True).stdout
        defined = {line.split()[-1] for line in output.splitlines()
                   if len(line.split()) >= 3 and line.split()[-2] != "U"}
        catalog = json.loads(builder.CATALOG.read_text())
        self.assertEqual(sorted({row["target"] for row in catalog["aliases"]} - defined), [])


if __name__ == "__main__":
    unittest.main()
