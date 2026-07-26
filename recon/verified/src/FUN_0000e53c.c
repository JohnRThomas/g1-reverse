/* Reconstructed FUN_0000e53c @ 0x0000e53c, exact extent 1020 bytes. */
#include <stdint.h>

extern /* ITERATION 39 DEFECT FIX -- WRONG PARAMETER.  Everything below the
 * `workspace[0x13] = charge_low` store operates on the THIRD float argument
 * (s2, the temperature `limit`), NOT on the fifth (s4, `charge_low`).  The
 * shipped prologue moves s2 into s18 (`0000e572 vmov.f32 s18, s2`) and s4 into
 * s16 (`0000e552 vmov.f32 s16, s4`); s16 is dead after `0000e580 vstr s16,
 * [r4,#0x4c]` (workspace[0x13]) and is immediately reused as scratch at
 * `0000e674 vmov.f32 s16, s0`.  Every later site reads s18:
 *     0000e62c vcmpe.f32 s18, s14  / 0000e638 vcmp.f32 s18, s15
 *     0000e640 vselgt.f32 s18, s15, s18      <- the clamp
 *     0000e66a vmov.f32  s0, s18   ; 0000e66e bl #0x8693c   <- fminf's 1st arg
 *     0000e774 / 0000e778 / 0000e790 / 0000e806 vfma.f32 ..., s18, ...
 * The reconstruction read `charge_low` at all of them, so with the shipped
 * runtime values (limit = 25.0 degC, charge_low = 0.3) it clamped and
 * interpolated with 0.3 where the firmware uses 25.0 clamped to the curve's
 * temperature break-points {17.0, 0.0, 0.0} -> 0.0.  Measured end to end:
 * `battery_soc_curve_model_init` wrote NaN into `*result` where the shipped
 * firmware writes 4.4985 (the pack voltage), the EKF started from NaN and the
 * reported state of charge never rose above 5 %% against the shipped 100 %%.
 * The differential that pinned it: a Renode hook on the instruction after each
 * image's own `bl battery_soc_curve_model_init` read `[sp+4]` --
 * ours 0x7fc00000, shipped 0x408fe76d.
 */
void FUN_00086c04(void *destination, const void *source, uint32_t size);
extern int FUN_0000e938(float value);
extern float FUN_0000e954(float *values);
extern float FUN_0000e9b4(float *values);
extern float FUN_0000ea18(const uint8_t *matches, int32_t *indices,
                          uint32_t *result);
extern float FUN_0000eb7c(float value, float *points, float *samples);
extern float FUN_000868fc(float value);
extern float FUN_00086902(float first, float second);
extern float FUN_0008693c(float first, float second);

static float interpolate_segment(float x, float x0, float span,
                                 float y0, float y1)
{
    return (x - x0) * (y1 - y0) / span + y0;
}

void FUN_0000e53c(float base, float scale, float limit,
                  float charge_high, float charge_low,
                  const void *table, const float *source,
                  volatile float *workspace, float *result)
{
    uint8_t matches[3];
    int32_t indices[3];
    float found_values[3];
    uint32_t find_result[2];
    float lower;
    float upper;
    float selected;
    float curve;
    int base_is_special;
    uint8_t selected_index;
    int32_t i;

    workspace[1] = 2.0f;
    workspace[0] = 1.0f;
    FUN_00086c04((void *)(workspace + 2), table, 0x40);
    workspace[0x12] = charge_high;
    workspace[0x13] = charge_low;
    workspace[0x15] = 0.0f;
    workspace[0x14] = 5.0f;
    workspace[0x16] = 0.0f;
    workspace[0x17] = 0.0f;

    for (i = 0; i != 25; ++i) {
        workspace[0x18 + i] = *(volatile float *)0x20002d1cu;
        workspace[0x31 + i] = *(volatile float *)0x20002d1cu;
    }
    workspace[0x4b] = *(volatile float *)0x20002d1cu;
    workspace[0x4c] = *(volatile float *)0x20002d1cu;
    workspace[0x4d] = *(volatile float *)0x20002d1cu;
    workspace[0x50] = *(volatile float *)0x20002d1cu;
    workspace[0x4a] = 1.0f;
    workspace[0x4e] = 0.0f;
    workspace[0x4f] = 0.0f;
    FUN_00086c04((void *)(workspace + 0x51), source, 0x1600);

    lower = source[0x324 / 4];
    upper = source[0x328 / 4];
    if (lower >= upper) {
        selected_index = 1;
        selected = lower;
        upper = lower;
        /* ITERATION 39: `0000e924 vmov.f32 s15,s14` is followed by
         * `0000e928 vmov.f32 s18,s14` -- this branch also REPLACES the
         * temperature argument with the single break-point, and the
         * reconstruction dropped that second move.  It is the branch the
         * shipped firmware actually takes at runtime (break-points
         * {17.0, 0.0, 0.0} => t0 >= t1). */
        limit = lower;
    } else {
        selected = lower;
        if (lower > upper)
            upper = lower;

        if (upper >= source[0x32c / 4]) {
            selected_index = 2;
        } else {
            float third = source[0x32c / 4];
            if (selected < third) {
                selected = third;
            } else if (upper <= third) {
                upper = third;
            }
            selected_index = 3;
        }

        if (limit < upper)
            upper = limit;
        else if (limit > selected)
            limit = selected;
    }

    workspace[0x5d1] = selected;
    workspace[0x5d2] = upper;
    ((uint8_t *)workspace)[0x5d3 * 4] = selected_index;

    curve = FUN_0000e954((float *)(source + 0x324 / 4));
    curve = FUN_0008693c(limit, curve);
    curve = FUN_00086902(curve, FUN_0000e9b4((float *)(source + 0x324 / 4)));

    matches[0] = source[0x324 / 4] == curve;
    matches[1] = source[0x328 / 4] == curve;
    matches[2] = source[0x32c / 4] == curve;
    FUN_0000ea18(matches, indices, find_result);
    if (find_result[1] == 0) {
        curve = FUN_0000eb7c(curve, (float *)(source + 0x324 / 4),
                            (float *)(source + 0x1578 / 4));
    } else {
        for (i = 0; i < (int32_t)find_result[1]; ++i)
            found_values[i] = source[indices[i] + 0x55d];
        curve = found_values[0];
    }

    workspace[0x5d4] = 3.0f;
    base += scale * curve;
    lower = source[0x330 / 4];
    upper = source[0x514 / 4];
    {
        float span = source[0x334 / 4] - lower;

        if (base >= lower && base <= upper) {
            float y0 = source[0x1390 / 4] + source[0x11a8 / 4] * limit;
            float y1 = source[0x1394 / 4] + source[0x11ac / 4] * limit;
            selected = interpolate_segment(base, lower, span, y0, y1);
        } else if (base >= upper) {
            float y0 = source[0x1574 / 4] + source[0x138c / 4] * limit;
            float y1 = source[0x1570 / 4] + source[5000 / 4] * limit;
            selected = interpolate_segment(base, upper, span, y0, y1);
        } else {
            selected = 0.0f;
        }

        if (base >= lower && base <= upper) {
            float whole = FUN_000868fc((base - lower) / span);
            int32_t left = (int32_t)(whole + 1.0f);
            int32_t right = (int32_t)(whole + 2.0f);
            float fraction = (base - lower) / span - whole;
            float inverse = 1.0f - fraction;
            selected = fraction * source[right + 0x38c] +
                       inverse * source[left + 0x38c] +
                       limit * (fraction * source[right + 0x1a4] +
                                inverse * source[left + 0x1a4]);
        }
    }

    base_is_special = FUN_0000e938(base);
    workspace[0x5d5] = 4.0f;
    workspace[0x5d6] = 0.0f;
    workspace[0x5d7] = 0.0f;
    workspace[0x5d8] = 0.0f;
    workspace[0x5d9] = base_is_special == 0 ? selected : 0.0f;
    workspace[0x5da] = curve;
    workspace[0x5db] = curve;
    workspace[0x5dc] = curve;
    workspace[0x5dd] = curve;
    *result = base;
}
