#include <nds.h>
#include <stdio.h>
#include <string.h>
#include <libcamera.h>

SpriteEntry OAMCopy[128];
#include "puffle.h"
#include "penguin.h"
#include "rose.h"
#include "dandelion.h"
#include "ball.h"
#include "moustache.h"
#include "flappy_bird.h"
#include "nyan.h"
#include "pleading_face.h"
#include "top_hat.h"
#include "pirate.h"
union
{
	u16 integer;
	unsigned char byte[4];
} rgb565;

void startScreenshot()
{
	vramSetBankD(VRAM_D_LCD);
	REG_DISPCAPCNT = DCAP_BANK(3) | DCAP_ENABLE | DCAP_SIZE(3) | DCAP_MODE(0) | DCAP_SRC_A(0); //|DCAP_SRC_B(1);

	// dmaCopy(VRAM_D, buffer, 256 * 192 * 2);
}
bool screenshotDone()
{
	return !(REG_DISPCAPCNT & DCAP_ENABLE);
}

void screenshotbmp(u8 *buffer)
{

	vramSetBankD(VRAM_D_LCD);
	REG_DISPCAPCNT = DCAP_BANK(3) | DCAP_ENABLE | DCAP_SIZE(3) | DCAP_MODE(0) | DCAP_SRC_A(0);

	while (REG_DISPCAPCNT & DCAP_ENABLE)
		;

	for (int y = 0; y < 192; y++)
	{
		for (int x = 0; x < 256; x++)
		{
			u16 color = VRAM_D[y * 256 + x];

			u8 b = (color & 31) << 3;
			u8 g = ((color >> 5) & 31) << 3;
			u8 r = ((color >> 10) & 31) << 3;

			buffer[((y * 256) + x) * 3] = r;
			buffer[((y * 256) + x) * 3 + 1] = g;
			buffer[((y * 256) + x) * 3 + 2] = b;
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
	// REG_DISPCNT |= (3 << 18);

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
	for (i = 0; i <= moustachePalLen; i++)
		VRAM_F_EXT_SPR_PALETTE[5][i] = ((u16 *)moustachePal)[i];
		
	for (i = 0; i <= piratePalLen; i++)
		VRAM_F_EXT_SPR_PALETTE[6][i] = ((u16 *)piratePal)[i];
	for (i = 0; i <= top_hatPalLen; i++)
		VRAM_F_EXT_SPR_PALETTE[7][i] = ((u16 *)top_hatPal)[i];

	for (i = 0; i <= flappy_birdPalLen; i++)
		VRAM_F_EXT_SPR_PALETTE[8][i] = ((u16 *)flappy_birdPal)[i];
	for (i = 0; i <= nyanPalLen; i++)
		VRAM_F_EXT_SPR_PALETTE[9][i] = ((u16 *)nyanPal)[i];
	for (i = 0; i <= pleading_facePalLen; i++)
		VRAM_F_EXT_SPR_PALETTE[10][i] = ((u16 *)pleading_facePal)[i];
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
	u16 *puffle = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	u16 *penguin = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	u16 *rose = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	u16 *dandelion = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	u16 *ball = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	u16 *moustache = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	u16 *flappy_bird = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	u16 *nyan = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	u16 *pleading_face = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	u16 *pirate = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	u16 *top_hat = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	dmaCopy(puffleTiles, puffle, puffleTilesLen);
	dmaCopy(penguinTiles, penguin, penguinTilesLen);
	dmaCopy(roseTiles, rose, roseTilesLen);
	dmaCopy(dandelionTiles, dandelion, dandelionTilesLen);
	dmaCopy(ballTiles, ball, ballTilesLen);
	dmaCopy(moustacheTiles, moustache, moustacheTilesLen);
	dmaCopy(flappy_birdTiles, flappy_bird, flappy_birdTilesLen);
	dmaCopy(nyanTiles, nyan, nyanTilesLen);
	dmaCopy(pleading_faceTiles, pleading_face, pleading_faceTilesLen);
	dmaCopy(pirateTiles, pirate, pirateTilesLen);
	dmaCopy(top_hatTiles, top_hat, top_hatTilesLen);

	sysSetBusOwners(false, false); // give ARM7 access to the cart

	enableSlot1();

	REG_AUXSPICNT = /*E*/ 0x8000 | /*SEL*/ 0x2000 | /*MODE*/ 0x40;
	REG_AUXSPIDATA = 0xFF;
	eepromWaitBusy();
	REG_AUXSPICNT = /*MODE*/ 0x40;

	u8 *temp = (u8 *)malloc(256 * 192 * 2);
	bool screenshotted = false;
	bool firstrun = true;

	int print_count = 0;
	bool manual_mode = true;

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

		// auto screenshot and SPI send code
		if (firstrun)
		{
			firstrun = false;
			startScreenshot();
			screenshotted = true;
		}
		// check if SPI sent
		if (fifoCheckValue32(FIFO_USER_02))
		{
			int value = fifoGetValue32(FIFO_USER_02);

			// 12 means SPI was sent
			if (value == 12 && !manual_mode)
			{
				startScreenshot();
				screenshotted = true;
			}
		}
		// if Capture Unit is done putting capture data into VRAM D
		if (screenshotted)
		{
			if (screenshotDone())
			{
				// tell ARM7 CPU to start sending data from VRAM D (Capture Data) over SPI
				//sysSetBusOwners(false, false); // give ARM7 access to the cart
				vramSetBankD(VRAM_D_ARM7_0x06000000);
				screenshotted = false;
			}
		}
		// end screenshot and SPI send code

		touchRead(&touch);
		scanKeys();
		
		if (keysDown() & KEY_SELECT)
		{
		}
		
		if (keysDown() & KEY_UP)
		{
			fifoSendValue32(FIFO_USER_03, 1);
		}
		if (keysDown() & KEY_LEFT)
		{
			fifoSendValue32(FIFO_USER_03, 2);
		}
		if (keysDown() & KEY_RIGHT)
		{
			fifoSendValue32(FIFO_USER_03, 3);
		}
		if (keysUp() & (KEY_LEFT|KEY_RIGHT|KEY_UP))
		{
			fifoSendValue32(FIFO_USER_03, 4);
		}
		if (keysDown() & KEY_X)
		{
			if (manual_mode)
			{
				firstrun = true;
			}
			manual_mode = !manual_mode;
		}
		if (keysDown() & KEY_Y)
		{
			if (sprite_i > 0)
			{
				sprite_i--;
				oamSet(&oamMain, // main graphics engine context
					   sprite_i, // oam index (0 to 127)  (spritenumber)
					   0, 0,	 // x and y pixle location of the sprite
					   0,		 // priority, lower renders last (on top)
					   mode - 1, // this is the palette index if multiple palettes or the alpha value if bmp sprite
					   SpriteSize_32x32,
					   SpriteColorFormat_256Color,
					   0,			 // pointer to the loaded graphics
					   -1,			 // sprite rotation data
					   false,		 // double the size when rotating?
					   true,		 // hide the sprite?
					   false, false, // vflip, hflip
					   false		 // apply mosaic
				);
			}
		}
		if (keysDown() & KEY_A)
		{
			startScreenshot();
			screenshotted = true;
		}
		if (keysDown() & KEY_B)
		{ // switch cameras whenever the B button is pressed
			camSwitch();
		}
		if (keysDown() & KEY_START)
		{
		}
		// change sticker mode
		if (keysDown() & KEY_R)
		{
			if (mode == 11)
			{
				mode = 1;
			}
			else
			{
				mode += 1;
			}
		}
		if (keysDown() & KEY_L)
		{
			if (mode == 1)
			{
				mode = 11;
			}
			else
			{
				mode -= 1;
			}
		}
		iprintf("\x1b[3;4HPress B to Switch Cameras\n");
		iprintf("\x1b[5;4HPress X to Switch Modes:\n");

		// Debug info on bottom screen
		if (manual_mode)
		{
			iprintf("\x1b[6;9HManual Mode\n");
			iprintf("\x1b[8;4HPress A To Send Picture\n");
		}
		else
		{
			iprintf("\x1b[6;9HAuto Mode  \n");
			iprintf("\x1b[8;4H                       \n");
		}
		iprintf("\n\n\nTouch and Drag to Place Sticker\n");
		iprintf("\n  Press Y to Delete Sticker\n");
		iprintf("\n Use L and R to Change Sticker\n");
		// iprintf("\x1bStickers: %d\n", sprite_i);
		if(mode==1){
			iprintf("\tSticker Mode: Puffle       \n");
		}
		else if(mode==2){
			iprintf("\tSticker Mode: Penguin    \n");
		}
		else if(mode==3){
			iprintf("\tSticker Mode: Rose       \n");
		}
		else if(mode==4){
			iprintf("\tSticker Mode: Dandelion  \n");
		}
		else if(mode==5){
			iprintf("\tSticker Mode: Ball       \n");
		}
		else if(mode==6){
			iprintf("\tSticker Mode: Moustache  \n");
		}
		else if(mode==7){
			iprintf("\tSticker Mode: Pirate Hat \n");
		}
		else if(mode==8){
			iprintf("\tSticker Mode: Top Hat    \n");
		}
		else if(mode==9){
			iprintf("\tSticker Mode: Flappy Bird\n");
		}
		else if(mode==10){
			iprintf("\tSticker Mode: Nyan Cat     \n");
		}
		else if(mode==11){
			iprintf("\tSticker Mode: Pleading Face\n");
		}

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
			else if (mode == 6)
			{
				sprite_p = moustache;
			}
			else if (mode == 7)
			{
				sprite_p = pirate;
			}
			else if (mode == 8)
			{
				sprite_p = top_hat;
			}
			else if (mode == 9)
			{
				sprite_p = flappy_bird;
			}
			else if (mode == 10)
			{
				sprite_p = nyan;
			}
			else if (mode == 11)
			{
				sprite_p = pleading_face;
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
