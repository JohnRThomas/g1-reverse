/* readable reconstruction; identity: FUN_0102def4 @ 0x0102def4
 * public-name: FUN_0102def4
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   mpsc_pbuf_alloc                          <= FUN_0102cc34 @ 0x0102cc34
 * address symbols (name @ address):
 *   g_net_periodic_work_obj                  @ 0x2100086c
 */
/* net-core FUN_0102def4 @ 0x102def4  (parity 300 trials PROVEN) */
extern int mpsc_pbuf_alloc(int,int,int,int);
int FUN_0102def4(unsigned int param_1)
{
    return mpsc_pbuf_alloc(0x2100086c, (int)param_1, 0, 0);
}
