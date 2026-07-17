/* Reconstructed FUN_00075c2c @ 0x75c2c  (parity: 300/300 trials, PROVEN) */
extern float FUN_00075f88(void);
extern float FUN_000868ee(float);
extern int *FUN_000807f2(void);
extern float FUN_00076a88(unsigned int descriptor);

float FUN_00075c2c(float value)
{
    float fallback = FUN_00075f88();

    if (*(volatile signed char *)0x200035afUL != -1 && value == value) {
        float converted = FUN_000868ee(value);
        if (converted > 1.0f) {
            int *error_number = FUN_000807f2();
            *error_number = 0x21;
            return FUN_00076a88(0x000a8ea0u);
        }
    }
    return fallback;
}
