/* Full hard-float reconstruction FUN_00026624 @ 0x26624, exact extent 388 bytes. */
#include <stdint.h>
extern float FUN_000265e8(float);

struct fusion_state {
    float unused0;
    float proportional_gain;
    float integral_gain;
    float q0, q1, q2, q3;
    float integral_x, integral_y, integral_z;
    uint8_t dirty;
};

void FUN_00026624(float gx, float gy, float gz,
                  float ax, float ay, float az, float dt,
                  volatile struct fusion_state *state)
{
    float q0 = state->q0;
    float q1 = state->q1;
    float q2 = state->q2;
    float q3 = state->q3;
    float half = 0.5f;

    if (ax != 0.0f || ay != 0.0f || az != 0.0f) {
        float reciprocal = FUN_000265e8(ay * ay + ax * ax + az * az);
        az *= reciprocal;
        ax *= reciprocal;
        ay *= reciprocal;

        float a = q3 * q2 + q1 * q0;
        float b = q0 * q2 - q1 * q3;
        float c = (half - q0 * q0) + q3 * q3;
        float ex = az * a - ay * c;
        float ey = ay * b - ax * a;
        float ez = ax * c - az * b;

        float ki = state->integral_gain;
        if (ki > 0.0f) {
            state->integral_x += ki * ex * dt;
            state->integral_y += ki * ez * dt;
            state->integral_z += ki * ey * dt;
            gx += state->integral_x;
            gy += state->integral_y;
            gz += state->integral_z;
        } else {
            state->integral_x = 0.0f;
            state->integral_y = 0.0f;
            state->integral_z = 0.0f;
        }
        float kp = state->proportional_gain;
        gx += kp * ex;
        gy += kp * ez;
        gz += kp * ey;
    }

    float scale = dt * half;
    gz *= scale;
    gx *= scale;
    gy *= scale;
    float n1 = ((gz * q2 + gx * q0) - q3 * gy) + q1;
    float n0 = ((-(gy * q2) - q1 * gx) - q3 * gz) + q0;
    float n2 = (gy * q0 - gz * q1) + q3 * gx + q2;
    float n3 = ((gy * q1 + gz * q0) - gx * q2) + q3;
    float reciprocal = FUN_000265e8(n1 * n1 + n0 * n0 + n2 * n2 + n3 * n3);
    state->q0 = n0 * reciprocal;
    state->q1 = n1 * reciprocal;
    state->q2 = n2 * reciprocal;
    state->q3 = n3 * reciprocal;
    state->dirty = 0;
}
