/* rodata_0x88570: battery state-of-charge EKF process-noise matrix Q,
 * 4 x 4 binary32 diagonal = diag(1e-6, 1e-6, 1e-8, 2e-4).
 * app-core VA 0x88570, 64 bytes (16 x uint32).  The next pin in the ledger is
 * rodata_885b0, so the extent 0x88570..0x885b0 is exactly this object.
 * Reader: batt_soc_curve_estimate (FUN_0000e2b4 @ 0xe2b4) copies the whole
 * 64-byte struct out of it and hands it to battery_soc_curve_model_init
 * (0xe53c), which bakes it into the estimator workspace that
 * battery_soc_from_curve / battery_model_state_update use for the rest of the
 * run.  Left as a bare `PROVIDE(rodata_88570 = 0x00088570)` the build read its
 * OWN rodata section at that address (an unrelated pointer table, ~8.8e-40 and
 * ~1.1e-19 read as floats), i.e. a near-zero Q, and the reported battery
 * percentage never rose.  Kept as uint32 words so the file is byte-exact under
 * tools/verify_data.py regardless of float literal rounding.
 */
#include <stdint.h>
const uint32_t rodata_0x88570[16] = {
    0x358637bd, 0x00000000, 0x00000000, 0x00000000,  /* 1e-6 */
    0x00000000, 0x358637bd, 0x00000000, 0x00000000,  /* 1e-6 */
    0x00000000, 0x00000000, 0x322bcc77, 0x00000000,  /* 1e-8 */
    0x00000000, 0x00000000, 0x00000000, 0x3951b717,  /* 2e-4 */
};
