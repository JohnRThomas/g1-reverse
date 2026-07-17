/* readable reconstruction; identity: FUN_00033f24 @ 0x00033f24
 * public-name: message_table_contains_id
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_message_pool                           @ 0x20007dac
 */
/* Reconstructed message_table_contains_id @ 0x33f24.
 * Raw identity/back-map: FUN_00033f24 @ 0x00033f24.
 * Executable extent: 0x2a bytes; literal word begins at 0x00033f50. */
typedef unsigned char u8;
typedef unsigned int  u32;

struct message_slot {
    u8 reserved_00[8];
    u32 message_id;
    u8 reserved_0c[4];
    u8 occupied;
    u8 reserved_11[0x1b4 - 0x11];
};

_Static_assert(sizeof(struct message_slot) == 0x1b4,
               "message slot stride must match firmware");

#define g_message_pool ((volatile struct message_slot *)0x20007dac)

u32 message_table_contains_id(u32 slot_count, u32 message_id)
{
    u8 index = 0;

    for (;;) {
        if (slot_count <= index) {
            return 0;
        }
        if (g_message_pool[index].occupied != 0 &&
            g_message_pool[index].message_id == message_id) {
            return 1;
        }
        index++;
    }
}
