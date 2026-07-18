#!/usr/bin/env python3
"""Regression checks for the clean cohesive-build entry point."""

import os
from pathlib import Path
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
WRAPPER = ROOT / "recon/application/build_cohesive.sh"


class CohesiveBuildWrapperTest(unittest.TestCase):
    def test_shell_syntax(self):
        subprocess.run(["bash", "-n", str(WRAPPER)], check=True)

    def test_exports_complete_clean_configure_environment(self):
        with tempfile.TemporaryDirectory() as temporary:
            temp = Path(temporary)
            ncs = temp / "ncs"
            for relative in (
                    "zephyr", "nrf/scripts", "zephyr/scripts/kconfig",
                    "bootloader/mcuboot/scripts"):
                (ncs / relative).mkdir(parents=True, exist_ok=True)

            fake_west = temp / "west"
            fake_west.write_text(
                "#!/usr/bin/env bash\n"
                "echo PYTHONSAFEPATH=$PYTHONSAFEPATH\n"
                "echo PYTHONPATH=$PYTHONPATH\n"
                "echo ZEPHYR_BASE=$ZEPHYR_BASE\n"
                "printf 'ARG=%s\\n' \"$@\"\n",
                encoding="utf-8")
            fake_west.chmod(0o755)

            env = os.environ.copy()
            env.update({"NCS_ROOT": str(ncs), "G1_WEST": str(fake_west)})
            result = subprocess.run(
                [str(WRAPPER), "app", str(temp / "build"), "--", "-DFOO=1"],
                check=True, capture_output=True, text=True, env=env)

            self.assertIn("PYTHONSAFEPATH=1", result.stdout)
            for expected in (
                    ROOT / ".venv", ncs / "bootloader/mcuboot/scripts",
                    ncs / "zephyr/scripts/kconfig", ncs / "nrf/scripts"):
                self.assertIn(str(expected), result.stdout)
            self.assertIn(f"ZEPHYR_BASE={ncs / 'zephyr'}", result.stdout)
            for argument in (
                    "ARG=build", "ARG=-p", "ARG=always",
                    "ARG=nrf5340dk_nrf5340_cpuapp",
                    f"ARG={ROOT / 'recon/application/app'}", "ARG=-DFOO=1"):
                self.assertIn(argument, result.stdout)

    def test_rejects_unknown_core(self):
        result = subprocess.run(
            [str(WRAPPER), "combined"], capture_output=True, text=True)
        self.assertEqual(2, result.returncode)
        self.assertIn("<app|net>", result.stderr)


if __name__ == "__main__":
    unittest.main()
