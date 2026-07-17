/* Reconstructed FUN_00054d18 @ 0x54d18 */

extern int FUN_000530b4(void);
extern int FUN_00054ce8(void *operation);
extern int FUN_00080d3a(void);
extern int FUN_00080dda(void *operation);
extern int FUN_00080fa4(int handle, unsigned int key);
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

    if (handle != 0 && FUN_00080fa4(handle, 0x000f2b3a) == 0) {
        FUN_00080fc4(0x20002000 + index * 7, handle);
    } else {
        do {
            result = FUN_00080dda(&operation);
            if (result != 0)
                return result;
            result = FUN_00054ce8(&operation);
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
