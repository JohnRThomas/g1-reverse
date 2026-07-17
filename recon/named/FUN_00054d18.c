/* readable reconstruction; identity: FUN_00054d18 @ 0x00054d18
 * public-name: FUN_00054d18
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   id_find                                  <= FUN_00054ce8 @ 0x00054ce8
 *   bt_addr_le_create_static                 <= FUN_00080dda @ 0x00080dda
 *   bt_addr_le_eq                            <= FUN_00080fa4 @ 0x00080fa4
 * address symbols (name @ address):
 *   rodata_f2b3a                             @ 0x000f2b3a
 *   g_ble_dev_state                          @ 0x20002000
 *   g_ble_dev_ncmd_sem                       @ 0x200020d4
 */
/* Reconstructed FUN_00054d18 @ 0x54d18 */

extern int FUN_000530b4(void);
extern int id_find(void *operation);
extern int FUN_00080d3a(void);
extern int bt_addr_le_create_static(void *operation);
extern int bt_addr_le_eq(int handle, unsigned int key);
extern int FUN_00080fb4(unsigned int state);
extern int FUN_00080fc4(int destination, int value);

struct operation_descriptor {
    int index;
    int handle;
    unsigned int value;
};

int FUN_00054d18(int index, int handle, unsigned int value)
{
    struct operation_descriptor operation = {index, handle, value};
    int result;

    if (handle != 0 && bt_addr_le_eq(handle, 0x000f2b3a) == 0) {
        FUN_00080fc4(0x20002000 + index * 7, handle);
    } else {
        do {
            result = bt_addr_le_create_static(&operation);
            if (result != 0)
                return result;
            result = id_find(&operation);
        } while (result >= 0);

        result = FUN_00080fc4(0x20002000 + index * 7,
                              (int)&operation);
        if (handle != 0)
            FUN_00080fc4(handle, result);
    }

    result = FUN_00080fb4(0x200020d4);
    if (((unsigned int)result & 4U) != 0) {
        FUN_000530b4();
        FUN_00080d3a();
    }
    return 0;
}
