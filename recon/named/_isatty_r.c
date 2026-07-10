/* named: _isatty_r */
/* globals referenced:
//   0x2000cc24  g_errno                      
*/
/* Reconstructed _isatty_r @ 0x78570  (parity: 300/300 trials, PROVEN) */

extern int _isatty(unsigned int);
void _isatty_r(int *param_1,unsigned int param_2)
{
  *(volatile int *)0x2000cc24UL = 0;
  int iVar2 = _isatty(param_2);
  if (iVar2 == -1) {
    int v = *(volatile int *)0x2000cc24UL;
    if (v != 0) {
      *(volatile int *)param_1 = v;
    }
  }
}

