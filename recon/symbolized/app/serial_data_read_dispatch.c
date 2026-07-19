#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d0e8 @ 0x0007d0e8
 * public-name: serial_data_read_dispatch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   transport_parameters_read                <= FUN_000258b4 @ 0x000258b4
 *   framed_serial_receive_parser             <= FUN_00033554 @ 0x00033554
 *   serial_data_read_dispatch                <= FUN_0007d0e8 @ 0x0007d0e8
 */
/* Reconstructed FUN_0007d0e8 @ 0x7d0e8.
 * Complete 56-byte dispatcher; 0x7d120 starts the next function. */
#include <stdint.h>
extern int transport_parameters_read(int, void *, void *);
extern int framed_serial_receive_parser(int, void *, void *);

unsigned serial_data_read_dispatch(int param_1, int param_2, void *param_3, void *param_4)
{
    if (param_2 == 0 || param_3 == 0 || param_4 == 0 || param_1 == 2)
        return 0xffffffff;
    if (param_1 == 0)
        return (unsigned)transport_parameters_read(param_2, param_3, param_4);
    if (param_1 == 1)
        return (unsigned)framed_serial_receive_parser(param_2, param_3, param_4);
    return 0;
}
