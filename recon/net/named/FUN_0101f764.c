/* readable reconstruction; identity: FUN_0101f764 @ 0x0101f764
 * public-name: FUN_0101f764
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_intrusive_list_append_unique  <= FUN_010294d2 @ 0x010294d2
 */
/* net-core FUN_0101f764 @ 0x101f764  (parity 300 trials PROVEN) */

extern void controller_intrusive_list_append_unique(unsigned int, unsigned int);

void FUN_0101f764(void)
{
  unsigned int base = 0x21001230;

  controller_intrusive_list_append_unique(base + 0x20c, 0x21000518);
  controller_intrusive_list_append_unique(base + 0x210, 0x21000520);
  controller_intrusive_list_append_unique(base + 0x214, 0x21000510);
}
