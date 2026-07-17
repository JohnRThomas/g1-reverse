/* Reconstructed smp_handle_reqs @ 0x80ab4 (raw FUN_00080ab4).
 * Reviewed executable extent: 0x2e bytes, ending before FUN_00080ae2. */
#include <stdint.h>

typedef struct {
    uint8_t storage[100];
} cbor_nb_reader_t;

typedef struct {
    uint8_t storage[56];
} cbor_nb_writer_t;

typedef struct {
    void *transport;
    cbor_nb_reader_t *reader;
    cbor_nb_writer_t *writer;
} smp_streamer_t;

extern void *net_buf_get(void *fifo, uint64_t timeout); /* FUN_000836e8 */
extern int smp_process_request_packet(smp_streamer_t *streamer,
                                      void *request_packet); /* FUN_000513e8 */

void smp_handle_reqs(void *work)
{
    void *transport = work;
    void *fifo = (uint8_t *)transport + 0x10;
    void *request_packet;

    while ((request_packet = net_buf_get(fifo, 0)) != 0) {
        cbor_nb_reader_t reader;
        cbor_nb_writer_t writer;
        smp_streamer_t streamer = {
            .transport = transport,
            .reader = &reader,
            .writer = &writer,
        };

        (void)smp_process_request_packet(&streamer, request_packet);
    }
}
