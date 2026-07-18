import tempfile
import unittest
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build_app_fixed_rodata as fixed


class FixedRodataTests(unittest.TestCase):
    def table(self, address, size=4, alignment=4, name="table"):
        return fixed.Table(Path(name + ".c"), name, address,
                           bytes(range(size)), alignment)

    def test_selection_is_fail_closed(self):
        tables = [self.table(0x100), self.table(0x204, name="safe"),
                  self.table(0x206, alignment=1, name="overlap"),
                  self.table(0x211, alignment=4, name="misaligned"),
                  self.table(0x300, size=8, name="past_payload")]
        selected, rejected = fixed.select_tables(tables, 0x200, 0x304)
        self.assertEqual([table.symbol for table in selected], ["safe"])
        self.assertEqual(rejected, {"below_baseline_rom_end": 1,
                                    "outside_payload": 1,
                                    "misaligned": 1,
                                    "overlap": 1,
                                    "multi_symbol_owner": 0})

    def test_generated_sections_are_unique_and_fixed(self):
        table = self.table(0x8B264, name="rodata_0x8b264")
        assembly = fixed.asm_text([table])
        linker = fixed.linker_text([table])
        self.assertIn(".g1_verified.rodata.0008b264", assembly)
        self.assertIn(".global rodata_0x8b264", assembly)
        self.assertIn(".g1_verified_rodata_0008b264 0x0008b264", linker)
        self.assertIn("KEEP(*(.g1_verified.rodata.0008b264))", linker)

    def test_baseline_end_uses_all_file_backed_sections(self):
        with tempfile.TemporaryDirectory() as directory:
            report = Path(directory) / "report.json"
            report.write_text('{"summary":{"overlaps":[]},"sections":['
                              '{"lma":"0x100","size":4},'
                              '{"lma":"0x180","size":16}]}')
            end, receipt = fixed.baseline_end(report)
            self.assertEqual(end, 0x190)
            self.assertEqual(receipt["rom_end_exclusive"], "0x00000190")


if __name__ == "__main__":
    unittest.main()
