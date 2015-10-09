/*
 * common.c
 *
 *  Created on: 07 ott 2015
 *      Author: raidenfox1
 */

void Delay(unsigned int ms) {
	//4694 = 1 ms
	while (ms > 1) {
		ms--;
		asm("nop");
	}
}
