"""Focused proof for FUN_01027974's caller contract and zero underflow path."""

import json
from pathlib import Path

import net_extract
from parity import emu, recon


ROOT = Path("/Users/freedomcoder/Projects/G1disasm2")
SCRATCH = Path(
    "/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/"
    "bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad"
)
VA = 0x01027974
SIZE = 114


def test_all_callers_enforce_a_nonzero_block_count():
    """The complete refgraph reduces the contract to four guarded byte fields."""
    functions = json.loads((SCRATCH / "refgraph_net.json").read_text())["functions"]
    assert functions["0x1027974"]["callers"] == ["0x10279e6"]
    assert set(functions["0x10279e6"]["callers"]) == {"0x1008a58", "0x100a664"}
    assert functions["0x100a664"]["callers"] == ["0x1008a58"]

    top = (ROOT / "recon/net/src/FUN_01008a58.c").read_text()
    for offset in (25, 26, 29):
        assert f"if (S[{offset}] != 0)" in top
        assert f"S[{offset}]," in top
    assert "if (S[27] == 0 || S[28] == 0)" in top
    assert "call_pos : 0, S[27], 0x104" in top
    assert "FUN_0100a664(S[28]" in top

    adapter = (ROOT / "recon/net/src/FUN_0100a664.c").read_text()
    assert "uint32_t id = (uint32_t)raw_id & 0xffu;" in adapter
    assert "FUN_010279e6(0, id, 0x10eu)" in adapter


def test_zero_count_underflow_matches_with_sufficient_instruction_budget():
    """Zero wraps to 65,535; compare the complete null-storage execution."""
    source = (ROOT / "recon/net/src/FUN_01027974.c").read_text()
    compiled, error = recon.compile_func(source, "FUN_01027974", VA)
    assert error is None, error
    candidate, tail, candidate_size, candidate_va = compiled
    original = net_extract.func_bytes_padded(VA, SIZE, 1024)

    result = emu.compare(
        original,
        VA,
        SIZE,
        candidate + tail,
        candidate_va,
        candidate_size,
        code_base=emu.NET_CODE_BASE,
        trials=1,
        nptr=0,
        arg_overrides=[{0: 0, 1: 8, 2: 0, 3: 16}],
        candidate_direct_target_map=dict(recon.LAST_DIRECT_TARGET_MAP),
        max_insns=2_500_000,
    )
    assert result["pass"], result
    assert result["checked"] == 1
