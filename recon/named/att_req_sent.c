/* readable reconstruction; identity: FUN_000822fc @ 0x000822fc
 * public-name: att_req_sent
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_reschedule                        <= FUN_0007350c @ 0x0007350c
 *   att_req_sent                             <= FUN_000822fc @ 0x000822fc
 * address symbols (name @ address):
 *   rodata_f0000                             @ 0x000f0000
 */
/* Reconstructed FUN_000822fc @ 0x822fc  (parity: 300/300 trials, PROVEN) */

extern void FUN_000822ae(void);
extern void k_work_reschedule(int,int*,int,int);
extern void FUN_0005833c(int*);
void att_req_sent(int param_1,int *param_2,int param_3)
{
    int *piVar1 = param_2;
    if (param_3 == 0) {
        FUN_000822ae();
    }
    if (*(int*)(*param_2 + 0x124) != 0) {
        k_work_reschedule(*param_2 + 0x160, piVar1, 0xf0000, 0);
    }
    FUN_0005833c(param_2);
}
