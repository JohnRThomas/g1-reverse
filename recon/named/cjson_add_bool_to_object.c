/* readable reconstruction; identity: FUN_0008504c @ 0x0008504c
 * public-name: cjson_add_bool_to_object
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_add_item_to_object                 <= FUN_0006466c @ 0x0006466c
 *   cjson_delete                             <= FUN_00064b1c @ 0x00064b1c
 *   cjson_create_bool                        <= FUN_00064c3c @ 0x00064c3c
 *   cjson_add_bool_to_object                 <= FUN_0008504c @ 0x0008504c
 */
/* Reconstructed FUN_0008504c @ 0x8504c  (parity: 300/300 trials, PROVEN) */

extern int cjson_create_bool(int);
extern int cjson_add_item_to_object(int,int,int,int);
extern void cjson_delete(volatile int*);
int cjson_add_bool_to_object(int param_1,int param_2,int param_3)
{
    int uVar1 = cjson_create_bool(param_3);
    int iVar2 = cjson_add_item_to_object(param_1,param_2,uVar1,0);
    if (iVar2 == 0) {
        cjson_delete(uVar1);
        uVar1 = 0;
    }
    return uVar1;
}
