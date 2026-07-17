/* readable reconstruction; identity: FUN_0101f888 @ 0x0101f888
 * public-name: sdc_hci_event_suppressed
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_hci_event_suppressed                 <= FUN_0101f888 @ 0x0101f888
 */
/* net-core FUN_0101f888 @ 0x101f888  (parity 300 trials PROVEN) */

unsigned char sdc_hci_event_suppressed(void) {
    return *(volatile unsigned char *)(0x21001230 + 0x219);
}
