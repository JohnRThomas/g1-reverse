"""VA<->file mapping and byte/literal extraction for app_update.bin (app core)."""
import struct

APP_BIN = "/Users/freedomcoder/Projects/G1disasm2/app_update.bin"
APP_LINK_BASE = 0xC200      # image linked here (slot0 + mcuboot header)
APP_HDR = 512               # mcuboot header size; file offset of link base

_data = None
def _blob():
    global _data
    if _data is None:
        _data = open(APP_BIN, "rb").read()
    return _data

def va_to_off(va):
    return va - APP_LINK_BASE + APP_HDR

def read(va, n):
    off = va_to_off(va)
    return _blob()[off:off + n]

def read_u32(va):
    return struct.unpack_from("<I", read(va, 4))[0]

def func_bytes(va, size):
    """Function code bytes. We also pull a few extra words so an embedded
    literal pool referenced by ldr [pc,#imm] just past `size` is available."""
    return read(va, size)

def func_bytes_padded(va, size, pad=64):
    return read(va, size + pad)

if __name__ == "__main__":
    import sys
    va = int(sys.argv[1], 0); n = int(sys.argv[2], 0) if len(sys.argv) > 2 else 16
    print("fileoff", hex(va_to_off(va)), read(va, n).hex())
