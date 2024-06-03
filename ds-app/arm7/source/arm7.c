/*---------------------------------------------------------------------------------

	derived from the default ARM7 core

		Copyright (C) 2005 - 2010
		Michael Noland (joat)
		Jason Rogers (dovoto)
		Dave Murphy (WinterMute)

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any
	damages arising from the use of this software.

	Permission is granted to anyone to use this software for any
	purpose, including commercial applications, and to alter it and
	redistribute it freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you
		must not claim that you wrote the original software. If you use
		this software in a product, an acknowledgment in the product
		documentation would be appreciated but is not required.

	2.	Altered source versions must be plainly marked as such, and
		must not be misrepresented as being the original software.

	3.	This notice may not be removed or altered from any source
		distribution.

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <dswifi7.h>
#include <maxmod7.h>
#include <nds/bios.h>
#include <libcamera.h>

union
{
    u16 integer;
    u8 byte[2];
} rgb565;

	
void VblankHandler(void) {
	Wifi_Update();
}

void VcountHandler() {
	inputGetAndSend();
}

volatile bool exitflag = false;

void powerButtonCB() {
	exitflag = true;
}

int main() {
	readUserSettings();

	irqInit();
	fifoInit();
	touchInit();

	mmInstall(FIFO_MAXMOD);
	// Start the RTC tracking IRQ
	initClockIRQ();

	SetYtrigger(80);

	installWifiFIFO();
	installSoundFIFO();

	installSystemFIFO();

	irqSet(IRQ_VCOUNT, VcountHandler);
	irqSet(IRQ_VBLANK, VblankHandler);

	irqEnable( IRQ_VBLANK | IRQ_VCOUNT | IRQ_NETWORK);   

	setPowerButtonCB(powerButtonCB);

	camSetupDefault(FIFO_USER_01); //setup our camera handler to listen on the first FIFO channel
	u16 *capture=VRAM;
	bool sent_once = false;
	// Keep the ARM7 mostly idle
	while (!exitflag) {
		if ( 0 == (REG_KEYINPUT & (KEY_SELECT | KEY_START | KEY_L | KEY_R))) {
			exitflag = true;
		}
		swiWaitForVBlank();
				
		if((*(vu8*)0x4000240)&(1<<1)){
			if(!sent_once){
				//VRAM[0]=0x4D42;
				REG_AUXSPICNT = /*NDS Slot Enable*/ 0x8000 | /*NDS Slot Mode Serial*/ 0x2000 | /*SPI Hold Chipselect */ 0x40;
				//REG_AUXSPIDATA = 0xFF;
				//eepromWaitBusy();

				//REG_AUXSPIDATA = 0xFF;
				//eepromWaitBusy();
				int i = 0;
				for(int y=0;y<192;y++){
					for(int x=0;x<256;x++)
					{
						
						u16 color=capture[y*256+x];

						u8 r=(color&31);
						u8 g=((color>>5)&31)<<1;
						u8 b=((color>>10)&31);
						//convert from RGB555 to RGB565
						rgb565.integer=(r<<11)|(g<<5)|(b);
						//rgb565.integer=color;
						//send in two separate bytes
						
						REG_AUXSPIDATA = rgb565.byte[0];
						eepromWaitBusy();
						if(i==32766||i==98300)
						{
							fifoSendValue32(FIFO_USER_02, i);
							REG_AUXSPICNT = /*MODE*/ 0x40;
							//wait 1ms
							swiDelay(2095);
							REG_AUXSPICNT = /*NDS Slot Enable*/ 0x8000 | /*NDS Slot Mode Serial*/ 0x2000 | /*SPI Hold Chipselect */ 0x40;
						}
						REG_AUXSPIDATA = rgb565.byte[1];
						eepromWaitBusy();
						if(i==65532)
						{
							fifoSendValue32(FIFO_USER_02, i);
							REG_AUXSPICNT = /*MODE*/ 0x40;
							//wait .25ms
							swiDelay(2095);
							REG_AUXSPICNT = /*NDS Slot Enable*/ 0x8000 | /*NDS Slot Mode Serial*/ 0x2000 | /*SPI Hold Chipselect */ 0x40;
						}
						i+=2;
					}
				}
				
				REG_AUXSPICNT = /*MODE*/ 0x40;
				
				sent_once = true;
				//send message over fifo, 12 means SPI was sent
				fifoSendValue32(FIFO_USER_02, 12);
			}
		}
		else{
			sent_once = false;
		}
		
		
	}
	return 0;
}
