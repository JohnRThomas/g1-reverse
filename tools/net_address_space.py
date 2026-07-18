"""Typed CPUNET analysis/runtime address conversions.

The stripped ``netcore_image.bin`` was imported for analysis at 0x01008000,
while the shipped image executes at 0x01008800.  Function identities, CFGs,
and direct relative call targets use analysis addresses.  Absolute flash
pointers stored in the image use runtime addresses.  The numeric ranges
overlap, so callers must carry the address-space type rather than infer it
from the integer value.
"""

from dataclasses import dataclass


ANALYSIS_BASE = 0x01008000
RUNTIME_BASE = 0x01008800
ANALYSIS_TO_RUNTIME_DELTA = RUNTIME_BASE - ANALYSIS_BASE
FLASH_WINDOW_SIZE = 0x00040000


class AddressSpaceError(ValueError):
    """Raised when a CPUNET address is used in the wrong coordinate space."""


class AmbiguousAddressSpaceError(AddressSpaceError):
    """Raised when an untyped integer belongs to both overlapping windows."""


def _validate(value, base, label):
    value = int(value)
    if not base <= value < base + FLASH_WINDOW_SIZE:
        raise AddressSpaceError(
            "%s address 0x%08x is outside [0x%08x,0x%08x)" %
            (label, value, base, base + FLASH_WINDOW_SIZE))
    return value


@dataclass(frozen=True, order=True)
class AnalysisAddress:
    value: int

    def __post_init__(self):
        object.__setattr__(self, "value", _validate(
            self.value, ANALYSIS_BASE, "analysis"))

    def to_runtime(self):
        return RuntimeAddress(self.value + ANALYSIS_TO_RUNTIME_DELTA)

    def to_offset(self):
        return self.value - ANALYSIS_BASE


@dataclass(frozen=True, order=True)
class RuntimeAddress:
    value: int

    def __post_init__(self):
        object.__setattr__(self, "value", _validate(
            self.value, RUNTIME_BASE, "runtime"))

    def to_analysis(self):
        return AnalysisAddress(self.value - ANALYSIS_TO_RUNTIME_DELTA)

    def to_offset(self):
        return self.value - RUNTIME_BASE


def analysis_to_runtime(address):
    if not isinstance(address, AnalysisAddress):
        raise TypeError("analysis_to_runtime requires AnalysisAddress")
    return address.to_runtime()


def runtime_to_analysis(address):
    if not isinstance(address, RuntimeAddress):
        raise TypeError("runtime_to_analysis requires RuntimeAddress")
    return address.to_analysis()


def classify_untyped_flash_address(value):
    """Classify only numerically unambiguous addresses.

    Most CPUNET flash integers lie in both coordinate windows.  Refusing those
    values is intentional: provenance (CFG position versus stored pointer) is
    the only sound discriminator.
    """
    value = int(value)
    analysis = ANALYSIS_BASE <= value < ANALYSIS_BASE + FLASH_WINDOW_SIZE
    runtime = RUNTIME_BASE <= value < RUNTIME_BASE + FLASH_WINDOW_SIZE
    if analysis and runtime:
        raise AmbiguousAddressSpaceError(
            "0x%08x is valid in both CPUNET address spaces" % value)
    if analysis:
        return AnalysisAddress(value)
    if runtime:
        return RuntimeAddress(value)
    raise AddressSpaceError("0x%08x is outside CPUNET flash" % value)


def format_address(address):
    if isinstance(address, AnalysisAddress):
        return "analysis:0x%08x" % address.value
    if isinstance(address, RuntimeAddress):
        return "runtime:0x%08x" % address.value
    raise TypeError("format_address requires a typed CPUNET address")
