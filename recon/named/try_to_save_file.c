/* readable reconstruction; identity: FUN_00023634 @ 0x00023634
 * public-name: try_to_save_file
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   write_font_to_flash_with_verify          <= FUN_00022834 @ 0x00022834
 *   dequeue_file                             <= FUN_000235a4 @ 0x000235a4
 *   crc32_update                             <= FUN_0002360c @ 0x0002360c
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_9e873                             @ 0x0009e873
 *   rodata_9e88b                             @ 0x0009e88b
 *   rodata_9e8e5                             @ 0x0009e8e5
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_font_total_size                        @ 0x200079d4
 *   g_font_buf_len                           @ 0x200079d8
 *   g_font_flash_write_offset                @ 0x200079dc
 *   g_font_crc32                             @ 0x200079e0
 *   g_font_write_buf                         @ 0x20017062
 */
/* Reconstructed try_to_save_file @ 0x23634 */
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

extern void log_message(uint32_t format, ...);
extern int get_device_info(void);
extern void debug_print(void);
extern void write_font_to_flash_with_verify(uint32_t address, uint32_t buffer, ...);
extern void dequeue_file(void *packet);
extern uint32_t crc32_update(uint32_t checksum, uint32_t buffer, uint32_t length);
extern void memcpy(void *destination, const void *source, uint32_t length);
extern void FUN_00086c1e(void *destination, const void *source,
                         uint32_t length, uint32_t capacity);
extern void update_persist_task_status(uint32_t context, int type, int status);

#define FILE_ADDRESS (*(volatile uint32_t *)0x200079dcUL)
#define FILE_TYPE (*(volatile int *)0x200079d4UL)
#define BUFFERED_LENGTH (*(volatile uint32_t *)0x200079d8UL)
#define FILE_CHECKSUM (*(volatile uint32_t *)0x200079e0UL)
#define LOG_LEVEL (*(volatile int *)0x2000230cUL)
#define LOG_SINK (*(volatile int *)0x20007554UL)
#define FILE_BUFFER ((uint8_t *)0x20017062UL)

void try_to_save_file(int context)
{
    uint8_t packet[201];
    uint32_t packet_length;
    uint32_t buffered;
    uint32_t checksum;

    dequeue_file(packet);
    packet_length = packet[200];

    if (packet_length < 0x15 && packet[0] == 0x0d && packet[1] == 0x0e) {
        if (FILE_TYPE == 0x1c0000 && FILE_ADDRESS > 0x1fffff)
            return;
        if (BUFFERED_LENGTH < 0x1000) {
            write_font_to_flash_with_verify(FILE_ADDRESS, (uint32_t)FILE_BUFFER,
                         BUFFERED_LENGTH);
            checksum = crc32_update(FILE_CHECKSUM, (uint32_t)FILE_BUFFER,
                                    BUFFERED_LENGTH);
            FILE_CHECKSUM = checksum;
            if (LOG_LEVEL < 1)
                return;
            if (LOG_SINK != 0) {
                debug_print();
                return;
            }
            log_message(0x0009e88b, 0x0009e8e5, checksum);
            return;
        }
        goto save_block;
    }

    if (FILE_ADDRESS == 0) {
        uint32_t address = ((uint32_t)packet[1] << 24) |
                           ((uint32_t)packet[2] << 16) |
                           ((uint32_t)packet[3] << 8) | packet[4];
        FILE_ADDRESS = address;
        FILE_CHECKSUM = crc32_update(FILE_CHECKSUM,
                                     (uint32_t)(packet + 1), 4);
        if (address == 0x1c0000) {
            int system = get_device_info();
            FILE_TYPE = 0x1c0000;
            **(volatile uint8_t **)(system + 0x100c) = 0x0c;
            system = get_device_info();
            if (**(volatile int **)(system + 0x1054) != 0x10) {
                volatile uint8_t *status =
                    *(volatile uint8_t **)(context + 0x100c) + 7;
                if (*status == 0)
                    *status = 10;
                update_persist_task_status(get_device_info(), 0x10, 2);
            }
        }
        buffered = BUFFERED_LENGTH;
        memcpy(FILE_BUFFER + buffered, packet + 5, packet_length - 5);
        buffered = buffered + packet_length - 5;
        BUFFERED_LENGTH = buffered;
    } else {
        buffered = BUFFERED_LENGTH;
        memcpy(FILE_BUFFER + buffered, packet + 1, packet_length - 1);
        buffered = buffered + packet_length - 1;
        BUFFERED_LENGTH = buffered;
    }

    if (FILE_TYPE == 0x1c0000 && FILE_ADDRESS > 0x1fffff)
        return;
    if (buffered < 0x1000)
        return;

save_block:
    write_font_to_flash_with_verify(FILE_ADDRESS, (uint32_t)FILE_BUFFER, 0x1000);
    checksum = crc32_update(FILE_CHECKSUM, (uint32_t)FILE_BUFFER, 0x1000);
    FILE_CHECKSUM = checksum;
    if (LOG_LEVEL > 0) {
        if (LOG_SINK == 0)
            log_message(0x0009e873, 0x0009e8e5, checksum);
        else
            debug_print();
    }
    FILE_ADDRESS += 0x1000;
    buffered = BUFFERED_LENGTH;
    FUN_00086c1e(FILE_BUFFER, FILE_BUFFER + 0x1000,
                 buffered - 0x1000, 0x1400);
    BUFFERED_LENGTH = buffered - 0x1000;
}
