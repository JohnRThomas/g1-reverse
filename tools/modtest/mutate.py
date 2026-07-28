"""Source mutation engine -- the anti-vacuity control.

This repository has produced FOUR fixtures that passed vacuously (a quaternion
(1,0,0,0) that made five sign errors cancel; a mutation that passed 17/17
because another term already set the bit; a fixture that passed the BROKEN body
and failed the correct one; a positive control returning 0/110).  A test suite
whose tests have never been shown to fail is not evidence.

So every generated vector set is graded by MUTATION KILL RATE: take the
reconstruction the vectors are supposed to constrain, break it in a small,
semantically meaningful way, and require the vectors to notice.  Mutants that
survive are reported by name; they are the concrete statement of what the
vectors do not see.

A mutant that does not compile is not a mutant and is discarded, not counted as
survived (which would flatter the rate) and not counted as killed (which would
flatter it more).

MUTANTS ARE APPLIED TO THE CANDIDATE SOURCE, NOT TO THE GOLDEN SIDE.  The
golden side is the shipped image and cannot be mutated -- which is exactly why
the oracle is non-circular.
"""

from __future__ import annotations

import re

#: (name, pattern, replacement-or-callable).  Each is a real defect class seen
#: in this project's own history:
#:   relational flip      -> battery_soc_from_curve (float compare vs sign test)
#:   constant perturbation-> FUN_0000e53c's 16-byte-short extent, table indices
#:   sign inversion       -> imu_mahony_ahrs_update's five VNMLS->VMLS
#:   argument transposition-> update_imu_mode's transposed log format pointer
#:   dropped statement    -> a missing volatile MMIO access
_RELATIONAL = [("<", ">="), (">", "<="), ("<=", ">"), (">=", "<"),
               ("==", "!="), ("!=", "==")]


def _hex_constants(text):
    return list(re.finditer(r'\b0x[0-9a-fA-F]{2,8}(?=[uU]?\b)', text))


def _decimal_constants(text):
    return list(re.finditer(r'(?<![\w.])(\d+)(?![\w.])', text))


def _body_start(text):
    """Skip the provenance banner so mutations land in code, not in comments."""
    end = 0
    while True:
        head = text.find("/*", end)
        if head < 0 or head > 4000:
            break
        close = text.find("*/", head)
        if close < 0:
            break
        end = close + 2
        if text[end:end + 40].strip().startswith(("/*", "*")):
            continue
        break
    return end


def _inert_mask(text):
    """True at every offset inside a comment, a string, or a char literal.

    MEASURED NECESSITY.  The symbolized sources carry the original address
    beside every global access as an inline comment:

        *(volatile unsigned char *)(...) /*=0x20018da1*/;

    Without this mask the constant-perturbation mutants land on those comments,
    compile to byte-identical code, and are counted as SURVIVORS -- reporting a
    test weakness that does not exist.  Two of the five survivors in the first
    `opt3001_read_lux_raw` / `mark_master_or_low_battery_flag` grading were
    exactly that (`hex:0x20018da1+1`, `hex:0x2000302f+1`).
    """
    mask = bytearray(len(text))
    index = 0
    length = len(text)
    while index < length:
        char = text[index]
        if char == "/" and index + 1 < length and text[index + 1] == "*":
            end = text.find("*/", index + 2)
            end = length if end < 0 else end + 2
            for position in range(index, end):
                mask[position] = 1
            index = end
            continue
        if char == "/" and index + 1 < length and text[index + 1] == "/":
            end = text.find("\n", index)
            end = length if end < 0 else end
            for position in range(index, end):
                mask[position] = 1
            index = end
            continue
        if char in "\"'":
            quote = char
            end = index + 1
            while end < length:
                if text[end] == "\\":
                    end += 2
                    continue
                if text[end] == quote:
                    end += 1
                    break
                end += 1
            for position in range(index, min(end, length)):
                mask[position] = 1
            index = end
            continue
        index += 1
    return mask


import re as _re

_BANNER = _re.compile(r'identity:\s*FUN_[0-9a-fA-F]+\s*@\s*0x[0-9a-fA-F]+')


def member_span(text, symbol):
    """(start, end) of `symbol`'s own block inside a possibly MERGED TU.

    THIS IS NOT OPTIONAL.  A stage-09 unit holds up to 39 functions, and
    mutating the whole file means most mutants land in a SIBLING that the
    target's vectors cannot possibly constrain -- they are then counted as
    survivors and the kill rate reads as a test weakness that does not exist.
    Measured: `ipc_read_u16_field` and `st25dv_write_reg_pair`, both at 100 %
    coverage, both graded 0/16 killed, with mutation offsets up to 17,215 in a
    file whose target function is a few dozen bytes long.

    The block runs from the target's provenance banner to the next banner (or
    to EOF).  Returns None when the symbol has no banner, in which case the
    caller must fall back to the whole file AND SAY SO.
    """
    banners = [(m.start(), m.end()) for m in _BANNER.finditer(text)]
    if not banners:
        return None
    for index, (start, end) in enumerate(banners):
        stop = banners[index + 1][0] if index + 1 < len(banners) else len(text)
        window = text[end:stop]
        name = _re.search(r'public-name:\s*([A-Za-z_$][\w$]*)', window)
        if (name and name.group(1) == symbol) or _re.search(
                r'\b' + _re.escape(symbol) + r'\s*\(', window):
            return (start, stop)
    return None


def generate(text, symbol, limit=40, span=None):
    """Yield (mutant_name, mutated_text).  Deterministic and ordered."""
    start = _body_start(text)
    head, body = text[:start], text[start:]
    mask = _inert_mask(body)
    if span is None:
        span = member_span(text, symbol)
    low = max(0, (span[0] - start)) if span else 0
    high = (span[1] - start) if span else len(body)

    def live(match):
        if not (low <= match.start() and match.end() <= high):
            return False
        return not any(mask[i] for i in range(match.start(), match.end()))

    out = []

    # 1. relational operator flips, one site at a time
    for old, new in _RELATIONAL:
        for match in [m for m in re.finditer(re.escape(" %s " % old), body)
                      if live(m)][:3]:
            out.append(("rel:%s->%s@%d" % (old, new, match.start()),
                        head + body[:match.start()] + " %s " % new +
                        body[match.end():]))

    # 2. hex constant perturbation (+1) -- catches a wrong mask, wrong table
    #    index, wrong register address, wrong log-format pointer
    for match in [m for m in _hex_constants(body) if live(m)][:12]:
        value = int(match.group(0), 16)
        out.append(("hex:%s+1@%d" % (match.group(0), match.start()),
                    head + body[:match.start()] +
                    ("0x%x" % (value + 1)) + body[match.end():]))

    # 3. decimal constant perturbation (+1)
    for match in [m for m in _decimal_constants(body) if live(m)][:8]:
        if match.group(1) in ("0", "1") and body[match.start() - 1:match.start()] == "_":
            continue
        out.append(("dec:%s+1@%d" % (match.group(1), match.start()),
                    head + body[:match.start()] +
                    str(int(match.group(1)) + 1) + body[match.end():]))

    # 4. arithmetic sign inversion on binary + / -
    for old, new in (("+", "-"), ("-", "+")):
        for match in [m for m in re.finditer(r'(?<=[\w\) ]) \%s ' % old, body)
                      if live(m)][:3]:
            out.append(("sign:%s->%s@%d" % (old, new, match.start()),
                        head + body[:match.start()] + " %s " % new +
                        body[match.end():]))

    # 5. statement deletion -- a whole simple statement, chosen only when it is
    #    a single line ending in `;` at statement level.  Catches a dropped
    #    volatile write / dropped call.
    lines = body.split("\n")
    offset = 0
    for index, line in enumerate(lines):
        line_start, offset = offset, offset + len(line) + 1
        if not (low <= line_start < high):
            continue
        stripped = line.strip()
        if (stripped.endswith(";") and not stripped.startswith(("return", "//",
                                                                "*", "extern",
                                                                "static", "#"))
                and "=" in stripped or stripped.endswith(");")):
            if stripped.startswith(("return", "extern", "typedef", "#")):
                continue
            mutant = lines[:index] + lines[index + 1:]
            out.append(("del:line%d" % index, head + "\n".join(mutant)))
        if len(out) > limit * 3:
            break

    # Deduplicate by text, keep order, cap.
    seen = set()
    result = []
    for name, mutant in out:
        digest = hash(mutant)
        if digest in seen or mutant == text:
            continue
        seen.add(digest)
        result.append((name, mutant))
        if len(result) >= limit:
            break
    return result
