#include <nds.h>
#include <stdio.h>
#include <string.h>
#include <libcamera.h>
#include "bmp.h"
SpriteEntry OAMCopy[128];
#include "puffle.h"
#include "penguin.h"
#include "rose.h"
#include "dandelion.h"
#include "ball.h"

void screenshot(u8 *buffer)
{
	/*u8 vram_cr_temp=VRAM_C_CR;
	VRAM_C_CR=VRAM_C_LCD;
	u8* vram_temp=(u8*)malloc(128*1024);
	dmaCopy(VRAM_B, vram_temp, 128*1024);*/
	//VRAM_C_CR=VRAM_C_LCD|VRAM_ENABLE;
	vramSetBankD(VRAM_D_LCD);
	REG_DISPCAPCNT = DCAP_BANK(3) | DCAP_ENABLE | DCAP_SIZE(3) | DCAP_MODE(0) | DCAP_SRC_A(0) ; //|DCAP_SRC_B(1);
	while (REG_DISPCAPCNT & DCAP_ENABLE);
	dmaCopy(VRAM_D, buffer, 256 * 192 * 2);
	
	//VRAM_C_CR=0x00;
	/*dmaCopy(vram_temp, VRAM_B, 128*1024);

	VRAM_B_CR=vram_cr_temp;

	free(vram_temp);*/
}

void write16(void* address, u16 value) {

	u8* array=(u8*)address;

	array[0]=value&0xff;
	array[1]=value>>8;
}

void write32(void* address, u32 value) {

	u8* array=(u8*)address;

	array[0]=value&0xff;
	array[1]=(value>>8)&0xff;
	array[2]=(value>>16)&0xff;
	array[3]=(value>>24)&0xff;
}
void screenshotbmp(u8 *buffer) {

	vramSetBankD(VRAM_D_LCD);
	REG_DISPCAPCNT = DCAP_BANK(3) | DCAP_ENABLE | DCAP_SIZE(3) | DCAP_MODE(0) | DCAP_SRC_A(0) ; 

	while(REG_DISPCAPCNT & DCAP_ENABLE);

	//u8* temp=(u8*)malloc(256*192*3+sizeof(INFOHEADER)+sizeof(HEADER));

	HEADER* header=(HEADER*)buffer;
	INFOHEADER* infoheader=(INFOHEADER*)(buffer+sizeof(HEADER));

	write16(&header->type, 0x4D42);
	write32(&header->size, 256*192*3+sizeof(INFOHEADER)+sizeof(HEADER));
	write16(&header->reserved1, 0);
	write16(&header->reserved2, 0);
	write32(&header->offset, sizeof(INFOHEADER)+sizeof(HEADER));

	write16(&infoheader->bits, 24);
	write32(&infoheader->size, sizeof(INFOHEADER));
	write32(&infoheader->compression, 0);
	write32(&infoheader->width, 256);
	write32(&infoheader->height, 192);
	write16(&infoheader->planes, 1);
	write32(&infoheader->imagesize, 256*192*3);
	write32(&infoheader->xresolution, 0);
	write32(&infoheader->yresolution, 0);
	write32(&infoheader->importantcolours, 0);
	write32(&infoheader->ncolours, 0);

	for(int y=0;y<192;y++)
	{
		for(int x=0;x<256;x++)
		{
			u16 color=VRAM_D[256*192-y*256+x];

			u8 b=(color&31)<<3;
			u8 g=((color>>5)&31)<<3;
			u8 r=((color>>10)&31)<<3;

			buffer[((y*256)+x)*3+sizeof(INFOHEADER)+sizeof(HEADER)]=r;
			buffer[((y*256)+x)*3+1+sizeof(INFOHEADER)+sizeof(HEADER)]=g;
			buffer[((y*256)+x)*3+2+sizeof(INFOHEADER)+sizeof(HEADER)]=b;
		}
	}

	
	
}
// simple sprite struct
typedef struct
{
	int x, y;		  // screen co-ordinates
	int dx, dy;		  // velocity
	SpriteEntry *oam; // pointer to the sprite attributes in OAM
	int gfxID;		  // graphics lovation
} Sprite;
//---------------------------------------------------------------------------------
void initOAM(void)
{
	//---------------------------------------------------------------------------------
	int i;

	for (i = 0; i < 128; i++)
	{
		OAMCopy[i].attribute[0] = ATTR0_DISABLED;
	}
}

//---------------------------------------------------------------------------------
void updateOAM(void)
{
	//---------------------------------------------------------------------------------

	memcpy(OAM, OAMCopy, 128 * sizeof(SpriteEntry));
}

int main(void)
{

	bool holding = false;
	touchPosition touch;
	int mode = 1;
	int sprite_i = 0;
	// videoSetMode(MODE_5_2D);
	// set the video mode
	initOAM();
	videoSetMode(MODE_5_2D |
				 DISPLAY_SPR_ACTIVE | // turn on sprites
				 DISPLAY_BG0_ACTIVE | // turn on background 0
				 DISPLAY_SPR_1D		  // this is used when in tile mode
	);
	vramSetBankA(VRAM_A_MAIN_BG_0x06040000);
	
	// set bits 18 and 19 of DISPCNT register to 11
	//REG_DISPCNT |= (3 << 18);
	


	consoleDemoInit();
	// consoleInit(0, 0,BgType_Text4bpp, BgSize_T_256x256, 31,0, true, true);

	// initialize the buffer
	int bg = bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 16, 0); // going to VRAM_A

	// get a pointer to the buffer
	u16 *bgmem = (u16 *)bgGetGfxPtr(bg);

	// initialize the camera
	camInit(FIFO_USER_01, BACK);
	int i;
	int shot_i = 0;
	// Sprite initialisation
	// setup memory for sprites
	oamInit(&oamMain, SpriteMapping_1D_32, true);
	vramSetBankF(VRAM_F_LCD);

	for (i = 0; i <= pufflePalLen; i++)
		VRAM_F_EXT_SPR_PALETTE[0][i] = ((u16 *)pufflePal)[i];
	for (i = 0; i <= penguinPalLen; i++)
		VRAM_F_EXT_SPR_PALETTE[1][i] = ((u16 *)penguinPal)[i];
	for (i = 0; i <= rosePalLen; i++)
		VRAM_F_EXT_SPR_PALETTE[2][i] = ((u16 *)rosePal)[i];
	for (i = 0; i <= dandelionPalLen; i++)
		VRAM_F_EXT_SPR_PALETTE[3][i] = ((u16 *)dandelionPal)[i];
	for (i = 0; i <= ballPalLen; i++)
		VRAM_F_EXT_SPR_PALETTE[4][i] = ((u16 *)ballPal)[i];
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
	u16 *puffle = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	u16 *penguin = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	u16 *rose = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	u16 *dandelion = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	u16 *ball = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	dmaCopy(puffleTiles, puffle, puffleTilesLen);
	dmaCopy(penguinTiles, penguin, penguinTilesLen);
	dmaCopy(roseTiles, rose, roseTilesLen);
	dmaCopy(dandelionTiles, dandelion, dandelionTilesLen);
	dmaCopy(ballTiles, ball, ballTilesLen);

	sysSetBusOwners(true, true); // give ARM9 access to the cart
	u8 *card = (u8 *)CARD_CMD_DUMMY;
	enableSlot1();
	static u8 header1[512];
	bool swap = false;

	REG_AUXSPICNT = /*E*/ 0x8000 | /*SEL*/ 0x2000 | /*MODE*/ 0x40;
	REG_AUXSPIDATA = 0xFF;
	eepromWaitBusy();
	REG_AUXSPICNT = /*MODE*/ 0x40;

	u8 *temp = (u8 *)malloc(256 * 192 * 2);
	u8 *temp1 = (u8 *)malloc(256 * 192 * 3 + sizeof(INFOHEADER)+sizeof(HEADER));
	bool screenshotted = false;
	// set first 8 bytes of temp to FF
	for (i = 0; i < 8; i++)
	{
		temp[i] = 0xFF;
	}

	while (1)
	{
		// cardWriteCommand(card);
		// cardEepromCommand(0x02);
		// cardWriteEeprom(0, card, 512, 0);

		// cardReadHeader(header1);
		// wait for the next VBlank to repeat
		swiWaitForVBlank();
		oamUpdate(&oamMain);
		// fetch a frame and write it to the active background, displaying it to the screen
		camFetch(bgmem);

		// updateOAM();

		touchRead(&touch);
		scanKeys();
		if (keysDown() & KEY_UP)
		{
			REG_AUXSPICNT = /*NDS Slot Enable*/ 0x8000 | /*NDS Slot Mode Serial*/ 0x2000 | /*SPI Hold Chipselect */ 0x40;
			REG_AUXSPIDATA = 0x02;
			eepromWaitBusy();
			REG_AUXSPICNT = /*MODE*/ 0x40;
		}
		if (keysDown() & KEY_DOWN)
		{
			// send temp to eeprom
			for (i = 0; i < 256 * 192 * 2; i += 1)
			{
				REG_AUXSPICNT = /*NDS Slot Enable*/ 0x8000 | /*NDS Slot Mode Serial*/ 0x2000 | /*SPI Hold Chipselect */ 0x40;
				REG_AUXSPIDATA = temp[i];
				eepromWaitBusy();
				REG_AUXSPICNT = /*MODE*/ 0x40;
			}
		}
		if (keysDown() & KEY_X)
		{
			// send temp to eeprom
			for (i = 0; i < (256 * 192 * 3 + sizeof(INFOHEADER)+sizeof(HEADER)); i += 1)
			{
				REG_AUXSPICNT = /*NDS Slot Enable*/ 0x8000 | /*NDS Slot Mode Serial*/ 0x2000 | /*SPI Hold Chipselect */ 0x40;
				REG_AUXSPIDATA = temp1[i];
				eepromWaitBusy();
				REG_AUXSPICNT = /*MODE*/ 0x40;
			}
		}
		if (keysDown() & KEY_A)
		{

			screenshot(temp);
			screenshotbmp(temp1);
			screenshotted = true;
		}
		if (keysDown() & KEY_B)
		{ // switch cameras whenever the B button is pressed
			camSwitch();
		}
		if (keysDown() & KEY_START)
		{ // deactivate the camera and terminate the program whenever START is pressed
			camStop();
			break;
		}
		// change sticker mode
		if (keysDown() & KEY_RIGHT)
		{
			if (mode == 5)
			{
				mode = 1;
			}
			else
			{
				mode += 1;
			}
		}
		if (keysDown() & KEY_LEFT)
		{
			if (mode == 1)
			{
				mode = 5;
			}
			else
			{
				mode -= 1;
			}
		}
		// Debug info on bottom screen
		iprintf("\x1b[6;5HToucha x = %04X, %04X\n", touch.rawx, touch.px);
		iprintf("\x1b[7;5HTouch y = %04X, %04X\n", touch.rawy, touch.py);
		// print address of temp buffer
		iprintf("\x1bTemp1 buffer: %08X\n", temp1);
		// print vrama address
		iprintf("size: info: %d head:%d\n", sizeof(INFOHEADER),sizeof(HEADER));
		if (screenshotted)
		{
			iprintf("\x1bScreenshot taken\n");
		}
		else
		{
			iprintf("\x1bScreenshot not taken\n");
		}
		iprintf("\x1b%d\n", holding);
		iprintf("\x1bStickers: %d\n", sprite_i);
		iprintf("\x1bMode: %d\n", mode);

		// let go of sticker
		if (holding && (touch.rawx == 0 || touch.rawy == 0))
		{
			holding = false;
			sprite_i += 1;
		}
		// start sticker
		else if (!holding && (touch.rawx > 0 || touch.rawy > 0))
		{
			holding = true;
		}
		else if (holding)
		{
			u16 *sprite_p;
			if (mode == 1)
			{
				sprite_p = puffle;
			}
			else if (mode == 2)
			{
				sprite_p = penguin;
			}
			else if (mode == 3)
			{
				sprite_p = rose;
			}
			else if (mode == 4)
			{
				sprite_p = dandelion;
			}
			else if (mode == 5)
			{
				sprite_p = ball;
			}

			// sprites[i].oam = &OAMCopy[sprite_i];
			// set up our sprites OAM entry attributes

			oamSet(&oamMain,		   // main graphics engine context
				   sprite_i,		   // oam index (0 to 127)  (spritenumber)
				   touch.px, touch.py, // x and y pixle location of the sprite
				   0,				   // priority, lower renders last (on top)
				   mode - 1,		   // this is the palette index if multiple palettes or the alpha value if bmp sprite
				   SpriteSize_32x32,
				   SpriteColorFormat_256Color,
				   sprite_p,	 // pointer to the loaded graphics
				   -1,			 // sprite rotation data
				   false,		 // double the size when rotating?
				   false,		 // hide the sprite?
				   false, false, // vflip, hflip
				   false		 // apply mosaic
			);
		}
	}

	return 0;
}
