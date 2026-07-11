/* net-core FUN_0103533c @ 0x103533c */
#include <stdint.h>
extern int FUN_0103ac0c(void *, uint16_t, uint32_t, void *, uint32_t,
                        uint32_t, uint32_t);

int FUN_0103533c(uint8_t *object, uint32_t unused, uint32_t count,
                 const uint32_t *first_values, const uint32_t *second_values)
{
    (void)unused;
    if (object == 0) return -22;
    uint8_t *operations = *(uint8_t **)(object + 0x20);
    if (operations != 0 && *(void **)operations != 0) {
        int (*override)(uint8_t *, uint32_t, uint32_t,
                        const uint32_t *, const uint32_t *) =
            *(int (**)(uint8_t *, uint32_t, uint32_t,
                       const uint32_t *, const uint32_t *))operations;
        return override(object, unused, count, first_values, second_values);
    }
    if (count > *(uint32_t *)(object + 0x28)) return (int)0xfffff440;

    uint8_t *records = *(uint8_t **)(object + 0x2c);
    for (uint32_t i = 0; i < count; ++i) {
        int status = FUN_0103ac0c(object, (uint16_t)i, first_values[i],
                                  records + i * 24 + 4, second_values[i],
                                  *(uint32_t *)(operations + 0x28),
                                  *(uint32_t *)(records + i * 24));
        if (status != 0) return status;
    }
    return 0;
}
