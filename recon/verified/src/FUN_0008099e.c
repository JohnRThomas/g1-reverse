/* Reconstructed FUN_0008099e @ 0x8099e  (parity: 300/300 trials, PROVEN) */

extern void FUN_0008633e(unsigned int a, void *b);

struct work_item {
    unsigned int value;
    unsigned int context;
};

void FUN_0008099e(unsigned int queue, unsigned int value,
                  unsigned int context)
{
    struct work_item item = { value, context };
    FUN_0008633e(queue, &item);
}
