/* named: cjson_create_array */
/* globals referenced:
//   0x20002bac  g_cjson_hooks                
*/
/* Reconstructed cjson_create_array @ 0x64c8c  (parity: 300/300 trials, PROVEN) */

extern unsigned int alloc_zeroed_node(unsigned int a);

void cjson_create_array(void)
{
    unsigned int v = *(volatile unsigned int*)0x20002bacUL;
    unsigned int r = alloc_zeroed_node(v);
    if (r != 0) {
        *(volatile unsigned int*)(r + 0xc) = 0x20;
    }
}

