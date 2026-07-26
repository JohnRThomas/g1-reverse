/* readable reconstruction; identity: FUN_00026624 @ 0x00026624
 * public-name: imu_mahony_ahrs_update
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fast_inverse_sqrt                        <= FUN_000265e8 @ 0x000265e8
 *   imu_mahony_ahrs_update                   <= FUN_00026624 @ 0x00026624
 */
/* Full hard-float reconstruction FUN_00026624 @ 0x26624, exact extent 388 bytes. */
#include <stdint.h>
extern float fast_inverse_sqrt(float);

struct fusion_state {
    float unused0;
    float proportional_gain;
    float integral_gain;
    float q0, q1, q2, q3;
    float integral_x, integral_y, integral_z;
    uint8_t dirty;
};

void imu_mahony_ahrs_update(float gx, float gy, float gz,
                  float ax, float ay, float az, float dt,
                  volatile struct fusion_state *state)
{
    float q0 = state->q0;
    float q1 = state->q1;
    float q2 = state->q2;
    float q3 = state->q3;
    float half = 0.5f;

    if (ax != 0.0f || ay != 0.0f || az != 0.0f) {
        float reciprocal = fast_inverse_sqrt(ay * ay + ax * ax + az * az);
        az *= reciprocal;
        ax *= reciprocal;
        ay *= reciprocal;

        /* iteration 37: 0x26684/0x26688/0x2669c/0x266a8/0x266ac are VNMLS.F32
         * (Sd = -Sd + Sn*Sm), NOT VMLS.F32 (Sd = Sd - Sn*Sm).  Reading them as
         * VMLS negated the whole accelerometer error vector and turned the
         * complementary filter's feedback POSITIVE -- the fused pitch entered a
         * +-77 deg limit cycle instead of converging.  Byte-verified below. */
        float a = q3 * q2 + q1 * q0;        /* s14  0x26670/0x26678            */
        float b = q1 * q3 - q0 * q2;        /* s13  0x26680 vmul, 0x26688 vnmls */
        float c = (q0 * q0 - half) + q3 * q3; /* s15  0x26684 vnmls, 0x26694 vmla */
        float ex = ay * c - az * a;         /* s12  0x26698 vmul, 0x2669c vnmls */
        float ez = ax * a - ay * b;         /* s4   0x266a0 vmul, 0x266a8 vnmls */
        float ey = az * b - ax * c;         /* s15  0x266a4 vmul, 0x266ac vnmls */

        float ki = state->integral_gain;
        if (ki > 0.0f) {
            state->integral_x += ki * ex * dt;   /* 0x266c2/0x266ce  s12 */
            state->integral_y += ki * ey * dt;   /* 0x266d2/0x266da  s15 */
            state->integral_z += ki * ez * dt;   /* 0x266d6/0x266e2  s4  */
            gx += state->integral_x;
            gy += state->integral_y;
            gz += state->integral_z;
        } else {
            state->integral_x = 0.0f;
            state->integral_y = 0.0f;
            state->integral_z = 0.0f;
        }
        float kp = state->proportional_gain;
        gx += kp * ex;                       /* 0x26702  s11 += kp*s12 */
        gy += kp * ey;                       /* 0x26706  s1  += kp*s15 */
        gz += kp * ez;                       /* 0x2670a  s2  += kp*s4  */
    }

    float scale = dt * half;
    gz *= scale;
    gx *= scale;
    gy *= scale;
    float n1 = ((gz * q2 + gx * q0) - q3 * gy) + q1;
    float n0 = ((-(gy * q2) - q1 * gx) - q3 * gz) + q0;
    float n2 = (gy * q0 - gz * q1) + q3 * gx + q2;
    float n3 = ((gy * q1 + gz * q0) - gx * q2) + q3;
    float reciprocal = fast_inverse_sqrt(n1 * n1 + n0 * n0 + n2 * n2 + n3 * n3);
    state->q0 = n0 * reciprocal;
    state->q1 = n1 * reciprocal;
    state->q2 = n2 * reciprocal;
    state->q3 = n3 * reciprocal;
    state->dirty = 0;
}
