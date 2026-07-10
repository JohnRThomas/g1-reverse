/* named: handle_touch_single_click */
/* globals referenced:
//   0x20004950  g_dashboard_widget_state     
//   0x2001b816  g_widget0_index_raw          
*/
/* Reconstructed handle_touch_single_click @ 0x3707c  (parity: 300/300 trials, PROVEN) */
typedef unsigned char u8;extern void set_dashboard_startup_default_language(void);int handle_touch_single_click(u8 p){*(volatile u8*)(0x20004950UL+1)=p;*(volatile u8*)0x2001b816UL=p;set_dashboard_startup_default_language();return 0;}
