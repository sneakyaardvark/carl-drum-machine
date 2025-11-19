#include <stdint.h>
#include <stdlib.h>
#include <bits.h>

typedef unsigned long charLCD;

charLCD activePatchL = 0x07BC217BC0;
// activePatchL
// •••••
// □□□□•
// □□□□•
// •••□•
// •••□•
// □□□□•
// □□□□•
// •••••

charLCD activePatchR = 0x03DE843DE0;
// activePatchR
// •••••
// •□□□□
// •□□□□
// •□•••
// •□•••
// •□□□□
// •□□□□
// •••••

/*
1001 9
1010 A
1011 B
1100 C
1101 D
1110 E
1111 F

0000 0011 1101 1110 1000 0100 0011 1101 1110 0000
0    3    D    E    8    4    3    D    E    0
*/