
@{{BLOCK(top_hat)

@=======================================================================
@
@	top_hat, 32x32@8, 
@	Transparent color : 00,FF,00
@	+ palette 256 entries, not compressed
@	+ 16 tiles Metatiled by 4x4 not compressed
@	Total size: 512 + 1024 = 1536
@
@	Time-stamp: 2024-06-05, 01:31:13
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global top_hatTiles		@ 1024 unsigned chars
	.hidden top_hatTiles
top_hatTiles:
	.word 0x00000000,0x00000000,0x00000000,0x01000000,0x00000000,0x02010000,0x00000000,0x01010000
	.word 0x00000000,0x03010000,0x00000000,0x03010000,0x00000000,0x03010000,0x00000000,0x03010000
	.word 0x01010101,0x01010101,0x02020202,0x02020202,0x02020202,0x02020202,0x02020202,0x02020202
	.word 0x01010101,0x01010101,0x03030303,0x03030303,0x03030303,0x03030303,0x03030303,0x03030303
	.word 0x01010101,0x01010101,0x02020202,0x02020202,0x02020202,0x02020202,0x02020202,0x02020202
	.word 0x01010101,0x01010101,0x03030303,0x03030302,0x03030303,0x03030302,0x03030303,0x03030302
	.word 0x00000000,0x00000000,0x00000001,0x00000000,0x00000102,0x00000000,0x00000101,0x00000000
	.word 0x00000103,0x00000000,0x00000103,0x00000000,0x00000103,0x00000000,0x00000103,0x00000000

	.word 0x00000000,0x03010000,0x00000000,0x03010000,0x00000000,0x03010000,0x00000000,0x03010000
	.word 0x00000000,0x03010000,0x00000000,0x03010000,0x00000000,0x03010000,0x00000000,0x03010000
	.word 0x03030303,0x03030303,0x03030303,0x03030303,0x03030303,0x03030303,0x03030303,0x03030303
	.word 0x03030303,0x03030303,0x03030303,0x03030303,0x03030303,0x03030303,0x03030303,0x03030303
	.word 0x03030303,0x03030302,0x03030303,0x03030302,0x03030303,0x03030302,0x03030303,0x03030302
	.word 0x03030303,0x03030302,0x03030303,0x03030302,0x03030303,0x03030302,0x03030303,0x03030302
	.word 0x00000103,0x00000000,0x00000103,0x00000000,0x00000103,0x00000000,0x00000403,0x00000000
	.word 0x00000503,0x00000000,0x00000103,0x00000000,0x00000103,0x00000000,0x00000103,0x00000000

	.word 0x00000000,0x03010000,0x00000000,0x03010000,0x00000000,0x03010000,0x00000000,0x01010000
	.word 0x00000000,0x01010101,0x01010100,0x01010303,0x03030301,0x01010303,0x03030301,0x03030303
	.word 0x03030303,0x03030303,0x03030303,0x03030303,0x03030303,0x03030303,0x03030303,0x03030303
	.word 0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101
	.word 0x03030303,0x03030302,0x03030303,0x03030302,0x03030303,0x03030302,0x03030303,0x03030302
	.word 0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101,0x01010101
	.word 0x00000103,0x00000000,0x00000103,0x00000000,0x00000103,0x00000000,0x00000101,0x00000000
	.word 0x01010101,0x00000000,0x03030101,0x00010101,0x03030101,0x01030303,0x03030303,0x01030303

	.word 0x03030301,0x03030303,0x01010101,0x03030303,0x01010100,0x03010101,0x00000000,0x01010101
	.word 0x00000000,0x01000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x03030303,0x03030303,0x03030303,0x03030303,0x03030303,0x03030303,0x01010101,0x01010101
	.word 0x01010101,0x01010101,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x03030303,0x03020206,0x03030303,0x02020603,0x03030303,0x02020303,0x01010101,0x01010101
	.word 0x01010101,0x01010101,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x03030303,0x01030303,0x03030303,0x01010101,0x01010102,0x00010101,0x01010101,0x00000000
	.word 0x00000001,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global top_hatPal		@ 512 unsigned chars
	.hidden top_hatPal
top_hatPal:
	.hword 0x03E0,0x0000,0x3CEA,0x28A6,0x0842,0x0000,0x30C7,0x0000
	.hword 0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421
	.hword 0x0842,0x0842,0x0842,0x0842,0x0842,0x0842,0x0842,0x0842
	.hword 0x0C63,0x0C63,0x0C63,0x0C63,0x0C63,0x0C63,0x0C63,0x0C63
	.hword 0x1084,0x1084,0x1084,0x1084,0x1084,0x1084,0x1084,0x1084
	.hword 0x14A5,0x14A5,0x14A5,0x14A5,0x14A5,0x14A5,0x14A5,0x14A5
	.hword 0x18C6,0x18C6,0x18C6,0x18C6,0x18C6,0x18C6,0x18C6,0x18C6
	.hword 0x1CE7,0x1CE7,0x1CE7,0x1CE7,0x1CE7,0x1CE7,0x1CE7,0x1CE7

	.hword 0x2108,0x2108,0x2108,0x2108,0x2108,0x2108,0x2108,0x2108
	.hword 0x2529,0x2529,0x2529,0x2529,0x2529,0x2529,0x2529,0x2529
	.hword 0x294A,0x294A,0x294A,0x294A,0x294A,0x294A,0x294A,0x294A
	.hword 0x2D6B,0x2D6B,0x2D6B,0x2D6B,0x2D6B,0x2D6B,0x2D6B,0x2D6B
	.hword 0x318C,0x318C,0x318C,0x318C,0x318C,0x318C,0x318C,0x318C
	.hword 0x35AD,0x35AD,0x35AD,0x35AD,0x35AD,0x35AD,0x35AD,0x35AD
	.hword 0x39CE,0x39CE,0x39CE,0x39CE,0x39CE,0x39CE,0x39CE,0x39CE
	.hword 0x3DEF,0x3DEF,0x3DEF,0x3DEF,0x3DEF,0x3DEF,0x3DEF,0x3DEF

	.hword 0x4210,0x4210,0x4210,0x4210,0x4210,0x4210,0x4210,0x4210
	.hword 0x4631,0x4631,0x4631,0x4631,0x4631,0x4631,0x4631,0x4631
	.hword 0x4A52,0x4A52,0x4A52,0x4A52,0x4A52,0x4A52,0x4A52,0x4A52
	.hword 0x4E73,0x4E73,0x4E73,0x4E73,0x4E73,0x4E73,0x4E73,0x4E73
	.hword 0x5294,0x5294,0x5294,0x5294,0x5294,0x5294,0x5294,0x5294
	.hword 0x56B5,0x56B5,0x56B5,0x56B5,0x56B5,0x56B5,0x56B5,0x56B5
	.hword 0x5AD6,0x5AD6,0x5AD6,0x5AD6,0x5AD6,0x5AD6,0x5AD6,0x5AD6
	.hword 0x5EF7,0x5EF7,0x5EF7,0x5EF7,0x5EF7,0x5EF7,0x5EF7,0x5EF7

	.hword 0x6318,0x6318,0x6318,0x6318,0x6318,0x6318,0x6318,0x6318
	.hword 0x6739,0x6739,0x6739,0x6739,0x6739,0x6739,0x6739,0x6739
	.hword 0x6B5A,0x6B5A,0x6B5A,0x6B5A,0x6B5A,0x6B5A,0x6B5A,0x6B5A
	.hword 0x6F7B,0x6F7B,0x6F7B,0x6F7B,0x6F7B,0x6F7B,0x6F7B,0x6F7B
	.hword 0x739C,0x739C,0x739C,0x739C,0x739C,0x739C,0x739C,0x739C
	.hword 0x77BD,0x77BD,0x77BD,0x77BD,0x77BD,0x77BD,0x77BD,0x77BD
	.hword 0x7BDE,0x7BDE,0x7BDE,0x7BDE,0x7BDE,0x7BDE,0x7BDE,0x7BDE
	.hword 0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF,0x7FFF

@}}BLOCK(top_hat)
