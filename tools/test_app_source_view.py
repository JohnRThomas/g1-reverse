#!/usr/bin/env python3
"""Regression checks for the G1-only CPUAPP source view."""

import json
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
VIEW = ROOT / "recon" / "application" / "src"
MANIFEST = ROOT / "recon" / "application" / "application_sources.json"


def main() -> None:
    subprocess.run(
        [str(ROOT / ".venv" / "bin" / "python"), str(ROOT / "tools" / "build_app_source_view.py"), "--check"],
        cwd="/tmp",
        check=True,
        env={"PYTHONSAFEPATH": "1"},
    )
    data = json.loads(MANIFEST.read_text())
    included = {row["readable_name"] for row in data["functions"] if row["status"].startswith("included_")}
    excluded = {row["readable_name"] for row in data["functions"] if row["status"] == "excluded_library"}

    assert "app_codec_lc3_test" in included
    for name in (
        "lc3_encode",
        "cjson_parse_value",
        "bt_att_recv",
        "k_msgq_get",
        "__ieee754_exp",
        "md5_init",
        "nvs_ate_id_matches",
        "vfprintf_core",
    ):
        assert name in excluded, name
        assert not (VIEW / f"{name}.c").exists(), name
    assert all(path.is_symlink() and path.resolve().parent == ROOT / "recon" / "named" for path in VIEW.glob("*.c"))
    assert len(list(VIEW.glob("*.c"))) == data["summary"]["included_g1_application"]
    print(json.dumps(data["summary"], sort_keys=True))


if __name__ == "__main__":
    main()
