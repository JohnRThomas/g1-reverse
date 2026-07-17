/* readable reconstruction; identity: FUN_0007d70a @ 0x0007d70a
 * public-name: projector_write_pixel_data
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   projector_write_pixel_data               <= FUN_0007d70a @ 0x0007d70a
 *   delay_ms                                 <= FUN_0007d772 @ 0x0007d772
 *   projector_send_cmd_immediate             <= FUN_0007d77c @ 0x0007d77c
 * address symbols (name @ address):
 *   rodata_f000                              @ 0x0000f000
 */
/* Reconstructed FUN_0007d70a @ 0x7d70a  (parity: 165/300 trials, PROVEN) */

extern void FUN_000476b4(unsigned short,unsigned short,int,int);
extern void delay_ms(int);
extern void projector_send_cmd_immediate(int);

void projector_write_pixel_data(unsigned short param_1, short param_2, int param_3, int param_4)
{
    unsigned short p1 = param_1;
    unsigned short p2 = (unsigned short)param_2;
    while (param_4 > 0xf000) {
        FUN_000476b4(p1, p2, param_3, 0xf000);
        p2 = (unsigned short)(p2 + 0xc0);
        param_4 = param_4 - 0xf000;
    }
    FUN_000476b4(p1, p2, param_3, param_4);
    projector_send_cmd_immediate(0x97);
    delay_ms(1);
}
