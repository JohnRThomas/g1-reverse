"""Net-core byte/literal reads with explicit coordinate spaces.

Ghidra/CFG function positions use analysis base 0x01008000.  Absolute flash
pointers stored in the shipped image use runtime base 0x01008800.  ``read``
remains an analysis-space compatibility alias for the parity pipeline; new
code must select ``read_analysis`` or ``read_runtime`` explicitly.
"""
import struct
from net_address_space import AnalysisAddress, RuntimeAddress

NET_BIN = "/Users/freedomcoder/Projects/G1disasm2/netcore_image.bin"
NET_ANALYSIS_BASE = 0x01008000
NET_RUNTIME_BASE = 0x01008800
# Historical compatibility name.  It described the analysis import base, not
# the runtime base; retain it only so external scripts fail neither import nor
# parity while they migrate to the explicit constants above.
NET_REAL_BASE = NET_ANALYSIS_BASE
_data = None
def _blob():
    global _data
    if _data is None:
        with open(NET_BIN, "rb") as stream:
            _data = stream.read()
    return _data
def _read_offset(offset, size):
    return _blob()[offset:offset + size] if offset >= 0 else b""


def read_analysis(va, n):
    o = AnalysisAddress(va).to_offset()
    return _read_offset(o, n)


def read_runtime(va, n):
    o = RuntimeAddress(va).to_offset()
    return _read_offset(o, n)


def read(va, n):
    """Backward-compatible analysis-space read used by CFG/parity tools."""
    return read_analysis(va, n)


def read_u32_analysis(va):
    b = read_analysis(va, 4)
    return struct.unpack("<I", b)[0] if len(b) == 4 else None


def read_u32_runtime(va):
    b = read_runtime(va, 4)
    return struct.unpack("<I", b)[0] if len(b) == 4 else None


def read_u32(va):
    """Backward-compatible analysis-space word read."""
    b = read_analysis(va, 4)
    return struct.unpack("<I", b)[0] if len(b) == 4 else None


def func_bytes(va, size):
    return read_analysis(va, size)


def func_bytes_padded(va, size, pad=64):
    return read_analysis(va, size + pad)
