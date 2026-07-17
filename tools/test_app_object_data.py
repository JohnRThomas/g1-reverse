import importlib.util
from pathlib import Path
import unittest


MODULE_PATH = Path(__file__).with_name("app_object_data.py")
SPEC = importlib.util.spec_from_file_location("app_object_data", MODULE_PATH)
app_object_data = importlib.util.module_from_spec(SPEC)
assert SPEC.loader is not None
SPEC.loader.exec_module(app_object_data)


class AppObjectDataTest(unittest.TestCase):
    def test_static_message_queue_initializers(self):
        queues = app_object_data.decode()["queues"]
        self.assertEqual(
            {
                name: (entry["msg_size"], entry["max_msgs"])
                for name, entry in queues.items()
            },
            {
                "g_audio_msgq": (204, 18),
                "g_display_msgq": (24, 30),
                "g_quicknote_flash_msgq": (6, 20),
                "g_flash_store_cmd_msgq": (6, 5),
            },
        )


if __name__ == "__main__":
    unittest.main()
