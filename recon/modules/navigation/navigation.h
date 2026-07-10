/*
 * navigation: turn-by-turn + map HUD driven by the phone's navigation app.
 *
 * The phone runs the actual navigation; the glasses are a display surface. Over
 * BLE service SVC_NAVIGATION (0x0820) the phone sends navigation info packets --
 * a startup packet, a turn/direction indication, an overview/panoramic map
 * bitmap (sometimes compressed to a single pack), an "arrived" status, and an
 * exit packet -- and the glasses render them and mirror them to the slave lens
 * over ESB. This module's one reconstructed piece is navigation_direction_img_
 * display (draws the turn-arrow icon); the packet state machine (ui_navigation_
 * task) and the map renderers (navigation_overview_map_display / navigation_
 * panoramic_map_display) are known from firmware strings but not yet
 * reconstructed into recon/named/. See even_protocol.h for the service ID.
 */
#ifndef G1_NAVIGATION_H
#define G1_NAVIGATION_H

#include <stdint.h>

/* Reconstructed (recon/named/navigation_direction_img_display.c):
 *   dir_id 1..0x23 selects a turn-arrow icon, drawn via gui_bmp_bitmap_draw. */
void navigation_direction_img_display(int dir_id, int x, int y);

/* ---- known-but-not-yet-reconstructed firmware symbols (from debug strings) --
 *   void ui_navigation_task(...);              // BLE packet state machine / screen thread
 *   int  navigation_overview_map_display(...); // draw overview map bitmap
 *   int  navigation_panoramic_map_display(...);// draw panoramic map bitmap
 * These live in the ble_proto/system dispatch groups (not in this agent's set)
 * and are declared here only to document the subsystem's surface.            */

#endif /* G1_NAVIGATION_H */
