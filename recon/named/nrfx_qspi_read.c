/* named: nrfx_qspi_read */
/* globals referenced:
//   0x2000b348  g_qspi_cb                    
//   0x5002b000  NRF_QSPI_BASE                
*/
/* Reconstructed nrfx_qspi_read @ 0x66bc4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int qspi_ready_wait(void);
extern int qspi_activate(int);
extern void assert_post_action(uint32_t,int);
extern void printk(uint32_t,uint32_t,uint32_t,int,uint32_t);

int nrfx_qspi_read(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
  uint8_t r4 = *(volatile uint8_t*)0x2000b378UL;
  if (r4 == 0){
    printk(0x99cbd, 0xf6d9a, 0xf6d5e, 0x2e8, param_4);
    assert_post_action(0xf6d5e, 0x2e8);
  }
  int iVar3 = 0x0bad000a;
  if ((param_2 & 3) == 0){
    if (*(volatile int*)0x2000b348UL == 0){
      *(volatile uint32_t*)(0x5002b000UL+0x51c) = param_2;
      *(volatile uint32_t*)(0x5002b000UL+0x520) = param_1;
      *(volatile uint8_t*)(0x2000b348UL+0x39) = 0;
      if (*(volatile uint8_t*)0x2000b380UL != 0 ||
          (iVar3 = qspi_activate(1), iVar3 != 0x0bad0007)){
        *(volatile uint32_t*)(0x5002b000UL+0x100) = 0;
        *(volatile uint32_t*)(0x5002b000UL+0xc) = 1;
        return qspi_ready_wait();
      }
    } else {
      iVar3 = 0x0bad000b;
      if (r4 == 1){
        *(volatile uint32_t*)(0x5002b000UL+0x51c) = param_2;
        *(volatile uint32_t*)(0x5002b000UL+0x520) = param_1;
        *(volatile uint8_t*)(0x2000b348UL+0x39) = 0;
        *(volatile uint8_t*)(0x2000b348UL+0x30) = 4;
        *(volatile uint32_t*)(0x5002b000UL+0x100) = 0;
        *(volatile uint32_t*)(0x5002b000UL+0x304) = 1;
        if (*(volatile uint8_t*)0x2000b380UL == 0){
          qspi_activate(0);
          iVar3 = 0x0bad0000;
        } else {
          *(volatile uint32_t*)(0x5002b000UL+0xc) = 1;
          iVar3 = 0x0bad0000;
        }
      }
    }
  }
  return iVar3;
}

