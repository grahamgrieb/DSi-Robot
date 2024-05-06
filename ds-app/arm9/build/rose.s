
@{{BLOCK(rose)

@=======================================================================
@
@	rose, 32x32@8, 
@	Transparent color : F1,D1,82
@	+ palette 256 entries, not compressed
@	+ 16 tiles Metatiled by 4x4 not compressed
@	Total size: 512 + 1024 = 1536
@
@	Time-stamp: 2024-05-06, 16:37:48
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global roseTiles		@ 1024 unsigned chars
	.hidden roseTiles
roseTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000101,0x01010101,0x01010101,0x04040401
	.word 0x01010401,0x04040404,0x01040401,0x04040404,0x06040201,0x06060606,0x04040201,0x04040406
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000101,0x00000000,0x01010104,0x01010101
	.word 0x01040604,0x06060404,0x0A040606,0x06040404,0x0A040406,0x08040404,0x0A080404,0x08040404
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000001,0x00000000
	.word 0x00000101,0x00000000,0x00000106,0x00000000,0x00000106,0x00000000,0x00000106,0x00000000

	.word 0x00000000,0x00000000,0x00000000,0x01000000,0x00000000,0x01000000,0x00000000,0x01000000
	.word 0x00000000,0x01000000,0x00000000,0x01000000,0x00000000,0x01000000,0x00000000,0x00000000
	.word 0x04080201,0x06060604,0x080A0201,0x06040404,0x0A0A0202,0x04040808,0x0A040202,0x08080A0A
	.word 0x04040802,0x0C0A0A0C,0x04080202,0x0C040404,0x04080201,0x080C0404,0x08020901,0x080C0408
	.word 0x0A0A0808,0x06080404,0x04060606,0x06060804,0x080A0A08,0x0C0C0A08,0x0C0C0A08,0x0C080C0C
	.word 0x040C0C0C,0x02080404,0x0404040C,0x01020804,0x04040404,0x01010208,0x08080408,0x00010102
	.word 0x00000106,0x00000000,0x00000101,0x00000000,0x00000101,0x00000000,0x0000010C,0x00000000
	.word 0x00000101,0x00000000,0x00000001,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x02050901,0x0C080808,0x02090501,0x08020202,0x09050501,0x07070709,0x050B0101,0x07070905
	.word 0x0B010100,0x05050503,0x01010000,0x05030303,0x01000000,0x03030101,0x00000000,0x030B0101
	.word 0x02020808,0x01010909,0x09020202,0x09090909,0x09090707,0x09050505,0x05050507,0x0505010B
	.word 0x0B030505,0x05010101,0x01030303,0x01010001,0x01010103,0x00000000,0x00000103,0x00000000
	.word 0x00000001,0x00000000,0x00000001,0x00000000,0x00000101,0x00000000,0x00000109,0x00000000
	.word 0x00000105,0x00000000,0x00000101,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x0B070701,0x01000000,0x05070701,0x01010100,0x05050707,0x07070100,0x01050507
	.word 0x07050100,0x01010507,0x01010100,0x00010101,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x0000010B,0x00000000,0x00000105,0x00000000,0x00000101,0x00000000,0x00000001,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global rosePal		@ 512 unsigned chars
	.hidden rosePal
rosePal:
	.hword 0x435E,0x0000,0x0012,0x0980,0x001A,0x0340,0x003E,0x0280
	.hword 0x0017,0x07E1,0x08BF,0x0E20,0x007E,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(rose)