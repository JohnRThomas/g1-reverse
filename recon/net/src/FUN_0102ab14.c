/* P4 iteration 26/27 - structural CPUNET RAM relocation.  Self-contained
   so tools/parity keeps compiling this canonical body unchanged: the
   #else arm is the shipped literal.  See recon/application/
   gen_net_ram_relocs.py and recon/symbols/g1_net_ram_reloc.h. */
#ifdef G1_COHESIVE_BUILD
extern unsigned char g1_net_ram_blk_210045e0[];
#define G1N_21004604 ((unsigned long)(g1_net_ram_blk_210045e0 + 0x24))
#else
#define G1N_21004604 0x21004604ul
#endif
/* net-core FUN_0102ab14 @ 0x0102ab14 (CFG-directed PASS) */
#include <stddef.h>
#include <stdint.h>

typedef void (*ipc0_handler_fn)(void *owner, const uint8_t *payload,
                                size_t payload_size);

struct ipc0_handler {
    uint8_t message_id;
    uint8_t reserved[7];
    ipc0_handler_fn receive;
};

/* P4 iteration 30 - MEASURED DEFECT, fixed: the registry stride was wrong.
 *
 * The shipped loop (runtime 0x0102b314..0x0102b34c) reads the entry count ONCE
 * into r6 before the loop and then walks the entry array with a single
 * pre-indexed 4-byte step per iteration:
 *
 *     mov  r3, r5              ; r3 = registry
 *     ldr  r6, [r3, #4]!       ; r3 = registry + 4 ; r6 = count        (ONCE)
 *   loop:
 *     cmp  r6, r4 ; ble return
 *     ldr  r2, [r3, #4]!       ; r3 += 4 ; r2 = entries[index]
 *     ... compare r2->id ...
 *     adds r4, #1 ; b loop
 *
 * The previous rendering advanced the cursor by TWO words per iteration and
 * re-read `cursor[0]` as the loop bound every time, so from index 1 onward it
 * used an ENTRY POINTER as the count and read `entries[2*index]` as the entry.
 * Consequence, measured in iterations 22-29: registry slot 0 is the id-1
 * "cpunet-hw-id" service (which is why the role/config handshake worked), but
 * slot 1 -- the id-2 "cpunet-esbm" ESB service registered by FUN_0102b2ac,
 * whose receive callback FUN_0102b15c stages the app's 32-byte sync frame --
 * was NEVER matched.  FUN_0102a468 therefore always reported 0 staged bytes,
 * FUN_0102b3f0 always built the 0x11 announcement instead of the staged data
 * frame, and every master ESB PTX on the air was an announce (our tx#3 was an
 * announce where the oracle's is the 0x40 sync-data frame).
 */
void FUN_0102ab14(const uint8_t *data, size_t size, void *priv)
{
    (void)priv;

    uint8_t *registry = *(uint8_t *volatile *)G1N_21004604;
    const uint8_t message_id = data[0];
    const uint32_t *cursor = (const uint32_t *)(registry + 4);
    const int32_t count = (int32_t)cursor[0];

    for (int32_t index = 0; count > index; ++index) {
        const struct ipc0_handler *handler =
            (const struct ipc0_handler *)(uintptr_t)(*++cursor);

        if (handler != NULL && handler->message_id == message_id) {
            handler->receive(registry - 0x48, data + 1, size - 1);
            return;
        }
    }
}
