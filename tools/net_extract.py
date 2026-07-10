"""Net-core byte/literal reads. Ghidra loaded the image at base 0, so a net-core
VA is directly an offset into netcore_image.bin (the 512-byte MCUboot header was
already stripped). Real-firmware address = VA + 0x01008000."""
import struct
NET_BIN = "/Users/freedomcoder/Projects/G1disasm2/netcore_image.bin"
NET_REAL_BASE = 0x01008000
_data = None
def _blob():
    global _data
    if _data is None:
        _data = open(NET_BIN, "rb").read()
    return _data
def _off(va):
    # Ghidra loaded at base 0x01008000; netcore_image.bin (header stripped)
    # starts there, so file offset = VA - base.
    return va - NET_REAL_BASE
def read(va, n):
    o = _off(va)
    return _blob()[o:o + n] if o >= 0 else b""
def read_u32(va):
    b = read(va, 4)
    return struct.unpack("<I", b)[0] if len(b) == 4 else None
def func_bytes(va, size):
    return read(va, size)
def func_bytes_padded(va, size, pad=64):
    return read(va, size + pad)
