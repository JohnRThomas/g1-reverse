#!/usr/bin/env python3
"""Fail-closed parity checks for the 0x53580..0x548b8 APP cluster.

The generic verifier deliberately does not equate arbitrary stack addresses.
These functions pass fully initialized diagnostic records to the logger, so
the tests pair the exact original/readable stack objects and compare all bytes.
FUN_00054444 also checks the real fifth AAPCS argument of bt_smp_request_ltk;
that scalar exposed a formerly swapped output-pointer/diversifier argument.
"""
from contextlib import contextmanager

import cfg_verify


@contextmanager
def reviewed(key, *, state_cases=None, objects=None,
             target_arities=None, target_stack_arities=None):
    tables = (
        (cfg_verify.REVIEWED_STATE_CASES, state_cases),
        (cfg_verify.REVIEWED_PAIRED_STACK_OBJECTS, objects),
        (cfg_verify.REVIEWED_TARGET_CALL_ARITIES, target_arities),
        (cfg_verify.REVIEWED_TARGET_CALL_STACK_ARITIES,
         target_stack_arities),
    )
    saved = [(table, table.get(key), key in table) for table, _ in tables]
    try:
        for table, value in tables:
            if value is not None:
                table[key] = value
        yield
    finally:
        for table, value, existed in saved:
            if existed:
                table[key] = value
            else:
                table.pop(key, None)


def verify_pass(name):
    result = cfg_verify.verify("app", name)
    assert result["status"] == "PASS", (name, result)
    return result["checked"]


def main():
    checks = {}

    key = ("app", 0x00053580)
    with reviewed(key, objects=[
        ("hci-command-log-record", -40, -32, 22, None, (1,),
         (0x00080EA2,)),
    ]):
        checks["FUN_00053580"] = verify_pass("FUN_00053580")

    checks["FUN_000536b8"] = verify_pass("FUN_000536b8")

    key = ("app", 0x00054444)
    with reviewed(
        key,
        objects=[
            ("allocation-failure-log", -32, -40, 8, None, (3,),
             (0x00080EA2,)),
        ],
        target_arities={0x00083370: 4},
        # Compare the fifth scalar stack argument. The sixth argument is a
        # compiler-local output pointer whose produced bytes are not consumed
        # in this allocation-failure fixture.
        target_stack_arities={0x00083370: 1},
    ):
        checks["FUN_00054444"] = verify_pass("FUN_00054444")

    key = ("app", 0x000548B8)
    controller = bytearray(0x78)
    with reviewed(
        key,
        state_cases=[({}, [(0x20002000, bytes(controller))])],
        objects=[
            ("identity-log", -64, -96, 20, None, (2,), (0x00080EA2,)),
            ("host-version-log", -72, -52, 26, None, (4,),
             (0x00080EA2,)),
            ("radio-version-log", -64, -76, 22, None, (6,),
             (0x00080EA2,)),
        ],
    ):
        checks["FUN_000548b8_zero_addresses"] = verify_pass("FUN_000548b8")

    controller[7] = 2
    with reviewed(
        key,
        state_cases=[({}, [(0x20002000, bytes(controller))])],
        objects=[
            ("identity-log", -64, -96, 20, None, (2,), (0x00080EA2,)),
            ("secondary-address-log", -64, -52, 18, None, (4,),
             (0x00080EA2,)),
            ("host-version-log", -72, -52, 26, None, (6,),
             (0x00080EA2,)),
            ("radio-version-log", -64, -76, 22, None, (8,),
             (0x00080EA2,)),
        ],
    ):
        checks["FUN_000548b8_two_addresses"] = verify_pass("FUN_000548b8")

    print("PASS", checks)


if __name__ == "__main__":
    main()
