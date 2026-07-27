#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_7          => struct g1_layout_app_shared_ctx_blob__param_0007        [param_0007; G1-original]
 *   param_8          => struct g1_layout_battery_soc_curve_model__param_0008    [param_0008; G1-original]
 *   local_48         => struct g1_layout_soc_curve_point_local__stack_0776      [stack_0776; G1-original]
 * Raw function identity: 0x0000e53c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0000e53c @ 0x0000e53c
 * public-name: battery_soc_curve_model_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   battery_soc_curve_model_init             <= FUN_0000e53c @ 0x0000e53c
 *   float_is_nan                             <= FUN_0000e938 @ 0x0000e938
 *   array_max_skip_nan_a                     <= FUN_0000e954 @ 0x0000e954
 *   array_max_skip_nan_b                     <= FUN_0000e9b4 @ 0x0000e9b4
 *   strtod_scan_int_prefix                   <= FUN_0000ea18 @ 0x0000ea18
 *   spline_interp_3pt                        <= FUN_0000eb7c @ 0x0000eb7c
 *   floorf                                   <= FUN_000868fc @ 0x000868fc
 *   fmaxf                                    <= FUN_00086902 @ 0x00086902
 *   fminf                                    <= FUN_0008693c @ 0x0008693c
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   g_spline_nan_sentinel                    @ 0x20002d1c
 */
/* Reconstructed FUN_0000e53c @ 0x0000e53c, exact extent 1020 bytes. */
#include <stdint.h>

extern void memcpy(int, int, int);
extern int float_is_nan(float value);
extern float array_max_skip_nan_a(float *values);
extern float array_max_skip_nan_b(float *values);
extern float strtod_scan_int_prefix(const uint8_t *matches, int32_t *indices,
                          uint32_t *result);
extern float spline_interp_3pt(float value, float *points, float *samples);
extern float floorf(float value);
extern float fmaxf(float first, float second);
extern float fminf(float first, float second);

static float interpolate_segment(float x, float x0, float span,
                                 float y0, float y1)
{
    return (x - x0) * (y1 - y0) / span + y0;
}

void battery_soc_curve_model_init(float base, float scale, float limit,
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
    memcpy((void *)(workspace + 2), table, 0x40);
    workspace[0x12] = charge_high;
    workspace[0x13] = charge_low;
    workspace[0x15] = 0.0f;
    workspace[0x14] = 5.0f;
    workspace[0x16] = 0.0f;
    workspace[0x17] = 0.0f;

    for (i = 0; i != 25; ++i) {
        workspace[0x18 + i] = *(volatile float *)((unsigned long)&g_spline_nan_sentinel) /*=0x20002d1c*/;
        workspace[0x31 + i] = *(volatile float *)((unsigned long)&g_spline_nan_sentinel) /*=0x20002d1c*/;
    }
    workspace[0x4b] = *(volatile float *)((unsigned long)&g_spline_nan_sentinel) /*=0x20002d1c*/;
    workspace[0x4c] = *(volatile float *)((unsigned long)&g_spline_nan_sentinel) /*=0x20002d1c*/;
    workspace[0x4d] = *(volatile float *)((unsigned long)&g_spline_nan_sentinel) /*=0x20002d1c*/;
    workspace[0x50] = *(volatile float *)((unsigned long)&g_spline_nan_sentinel) /*=0x20002d1c*/;
    workspace[0x4a] = 1.0f;
    workspace[0x4e] = 0.0f;
    workspace[0x4f] = 0.0f;
    memcpy((void *)(workspace + 0x51), source, 0x1600);

    /* ITERATION 40 DEFECT FIX -- the temperature break-point selection.
     * Shipped, 0xe5d8..0xe644 plus the out-of-line arms 0xe874 / 0xe892 /
     * 0xe924 / 0xe930 (the last two live at 0xe924..0xe936, i.e. BEYOND the
     * catalogued 0x3ec extent; the true extent is 0x3fc, ending where
     * float_is_nan's `push {r3, lr}` starts at 0xe938):
     *
     *   s14 = t0 = source[0x324/4]   s13 = t1 = source[0x328/4]
     *   0000e5e0 vcmpe s14,s13
     *   0000e5e8 bge.w  #0xe924   ; t0 >= t1 ORDERED -> s15 = t0, s18 = t0,
     *                             ;   r2 = 1, and 0000e92e branches STRAIGHT to
     *                             ;   the store, skipping the clamp entirely
     *   0000e5ec bmi.w  #0xe874   ; t0 <  t1 ORDERED -> s12 = t1
     *   0000e5f0 vmov s12,s14     ; unordered        -> s12 = t0
     *   s15 = t2 = source[0x32c/4]
     *   0000e5fe vcmpe s13,s15 ; bge.w #0xe930 ; t1 >= t2 -> s15 = s12, r2 = 2
     *   0000e60a vcmpe s12,s15 ; bmi.w #0xe896 ; s12 < t2 -> r2 = 3, s15 KEEPS t2
     *   0000e616 vcmpe s14,s15 ; ble.w #0xe892 ; !(s14 > t2) -> s15 = s12, r2 = 3
     *   0000e622 vmov s14,s15   ; else s14 = t2, s15 = s12, r2 = 3
     *   0000e62c vcmpe s18,s14 ; bmi.w #0xe8a6 ; limit < s14 -> s18 = s14
     *   0000e638 vcmp  s18,s15 ; 0000e640 vselgt.f32 s18,s15,s18
     *                                          ; else s18 = (limit > s15) ? s15 : limit
     *   0000e64c vstr s15,[r7+0x744]  0000e658 vstr s14,[r7+0x748]
     *   0000e65e strb r2,[r7+0x74c]
     *
     * `s14` is t0 on EVERY arm that does not overwrite it, and the clamp
     * assigns to `limit` (s18), never to s14.  The previous body left s14 at t1
     * on the t0 < t1 path and wrote `upper = limit` instead of `limit = upper`,
     * which is the pair of workspace words cfg_verify still reported as
     * differing after the iteration-39 fixes (events 67/68 at workspace+0x1744
     * and +0x1748, shifted by one against the original). */
    lower = source[0x324 / 4];
    {
        const float t1 = source[0x328 / 4];
        const float t2 = source[0x32c / 4];
        float peak;

        upper = lower;
        if (lower >= t1) {
            selected = lower;
            limit = lower;
            selected_index = 1;
        } else {
            peak = (lower < t1) ? t1 : lower;
            selected = t2;
            if (t1 >= t2) {
                selected = peak;
                selected_index = 2;
            } else if (peak < t2) {
                selected_index = 3;
            } else if (!(upper > t2)) {
                selected = peak;
                selected_index = 3;
            } else {
                upper = t2;
                selected = peak;
                selected_index = 3;
            }
            if (limit < upper) {
                limit = upper;
            } else if (limit > selected) {
                limit = selected;
            }
        }
    }

    workspace[0x5d1] = selected;
    workspace[0x5d2] = upper;
    ((uint8_t *)workspace)[0x5d3 * 4] = selected_index;

    curve = array_max_skip_nan_a((float *)(source + 0x324 / 4));
    curve = fminf(limit, curve);
    curve = fmaxf(curve, array_max_skip_nan_b((float *)(source + 0x324 / 4)));

    matches[0] = source[0x324 / 4] == curve;
    matches[1] = source[0x328 / 4] == curve;
    matches[2] = source[0x32c / 4] == curve;
    strtod_scan_int_prefix(matches, indices, find_result);
    if (find_result[1] == 0) {
        curve = spline_interp_3pt(curve, (float *)(source + 0x324 / 4),
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
        /* ITERATION 40 DEFECT FIX -- the three-way range test, the sign of the
         * upper extrapolation and the two table indices of the interpolation
         * were all wrong.  Shipped control flow, read instruction by
         * instruction from 0xe714 down:
         *
         *   0000e714 vcmpe s0,s17 ; 0000e72c bpl.w #0xe87a   ; lower >= base OR UNORDERED
         *   0000e730 vcmpe s15,s17; 0000e738 ble.w #0xe87a   ; upper <= base OR UNORDERED
         *   -- fall through means  lower < base < upper -- and it goes straight
         *      to 0000e796, the floorf/table arm, WITHOUT running either
         *      extrapolation block (0000e794 `cbz r2` is jumped over).
         *   0000e87a vcmpe s0,s17 ; 0000e882 bge #0xe8ac     ; lower >= base, ordered
         *           vcmpe s15,s17; 0000e88c bhi #0xe91a      ; upper > base OR UNORDERED
         *           -> 0000e91a  vldr s16,#0.0               ; the NaN arm
         *           else r2 = 0 -> 0000e754                  ; base >= upper
         *   0000e8ac r2 = 0 ; 0000e8ae vcmpe s15,s17 ; bls.w #0xe754
         *           -> 0000e8ba                              ; base <= lower
         *   and on BOTH extrapolation arms r2 is 0, so 0000e794 `cbz r2`
         *   skips 0000e796 entirely: floorf runs ONLY in range.
         *
         * The previous body ran the LOW extrapolation for the in-range case,
         * then ran the floorf arm for the same case as well, which is the
         * `direct-target (8, 0xe938, 0x868fc)` mismatch cfg_verify reports:
         * the candidate called floorf where the shipped function goes straight
         * to float_is_nan. */
        float span = source[0x334 / 4] - lower;

        if (base != base) {
            /* 0000e91a: the unordered arm -- `bhi` after VCMPE is true for
             * unordered, so a NaN input lands here and yields exactly 0. */
            selected = 0.0f;
        } else if (lower < base && base < upper) {
            /* 0000e796: q = floorf((base - lower) / span), then a linear blend
             * of the two neighbouring table rows.  The row bases are
             *   0000e7de vldr s16,[r5,#0x38c]  with r5 = source + 4*right + 0x1000
             *   0000e7e2 vldr s11,[r5,#0x1a4]
             *   0000e7f2 vldr s12,[r3,#0x38c]  with r3 = source + 4*left  + 0x1000
             *   0000e7f6 vldr s14,[r3,#0x1a4]
             * i.e. BYTE offsets 0x138c and 0x11a4, float indices 0x4e3 and
             * 0x469.  The previous body used 0x38c and 0x1a4 as float indices,
             * reading 0xe30 / 0x690 bytes in instead of 0x138c / 0x11a4. */
            float whole = floorf((base - lower) / span);
            int32_t left = (int32_t)(whole + 1.0f);
            int32_t right = (int32_t)(whole + 2.0f);
            float fraction = (base - lower) / span - whole;
            float inverse = 1.0f - fraction;
            selected = fraction * source[right + 0x138c / 4] +
                       inverse * source[left + 0x138c / 4] +
                       limit * (fraction * source[right + 0x11a4 / 4] +
                                inverse * source[left + 0x11a4 / 4]);
        } else if (base >= upper) {
            /* 0000e754: upper extrapolation.  s14 = source[0x1574/4] +
             * source[0x138c/4]*limit is the value AT the knot and s13 =
             * source[0x1570/4] + source[0x1388/4]*limit is the one below it;
             * 0000e780 `vsub s14, s14, s13` therefore forms (at - below), and
             * 0000e78c/0000e790 add s11 + s12*limit = the AT value back.  The
             * previous body passed the pair to interpolate_segment in the
             * order that forms (below - at), i.e. with the slope negated. */
            float at = source[0x1574 / 4] + source[0x138c / 4] * limit;
            float below = source[0x1570 / 4] + source[0x1388 / 4] * limit;
            selected = (base - upper) * (at - below) / span + at;
        } else {
            /* 0000e8ba: lower extrapolation. */
            float at = source[0x1390 / 4] + source[0x11a8 / 4] * limit;
            float above = source[0x1394 / 4] + source[0x11ac / 4] * limit;
            selected = (base - lower) * (above - at) / span + at;
        }
    }

    base_is_special = float_is_nan(base);
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
