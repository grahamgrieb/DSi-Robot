
@{{BLOCK(ball)

@=======================================================================
@
@	ball, 32x32@8, 
@	+ palette 256 entries, not compressed
@	+ 16 tiles Metatiled by 4x4 not compressed
@	Total size: 512 + 1024 = 1536
@
@	Time-stamp: 2024-05-06, 16:37:47
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global ballTiles		@ 1024 unsigned chars
	.hidden ballTiles
ballTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x4A000000,0x00000000,0x6F9E0000
	.word 0x00000000,0x4D6FAA00,0x00000000,0x6F6829A8,0x60000000,0x7FBA7A23,0x07950000,0xA23F23E2
	.word 0x4A000000,0xDAF440FE,0xB9479F00,0xADADC85C,0x67676756,0xFAFAB91E,0xB9677FA2,0x2F2FC8FA
	.word 0xADFAA26F,0xB7B75C2F,0x2FFAB97F,0xFFFF1CB2,0xB7AD091E,0x7BAFFFB7,0x2F2FFA1E,0xFFAFB7FF
	.word 0x710A27EE,0x0000004A,0x2FC80976,0x0036DBFA,0x1EB9FAAD,0xF9B9B0F3,0xFAAD2F2F,0x3CD267B9
	.word 0x2FB7B7B7,0xD2A209AD,0xB7B7FFFF,0xA2B9C82F,0xFFFFFFAF,0x67092F2F,0xFFB7AFFF,0xB9FA2F5C
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x000000E1,0x00000000,0x0000F8D2,0x00000000
	.word 0x0032314D,0x00000000,0xAA7A3F6F,0x00000000,0x7A7C3F31,0x00000035,0xD923EAD2,0x00008649

	.word 0x490A0000,0x7FEA7AE7,0x07699A00,0xA2EAFDA9,0x6947BE00,0xA23F1613,0x6991A7C3,0x6FBAF5D7
	.word 0x6564464A,0x6FEF23D7,0x475AA120,0x3FF51349,0x0E089290,0xF5D9D707,0x647E02CB,0xD3134918
	.word 0x5C2FFAB9,0xB71CB7FF,0x5CADFA1E,0x847B2FB2,0xADADB91E,0x814E5CC8,0xADFA671E,0x4B59C7AD
	.word 0x09B97FA2,0x4B82C976,0x67A2D2C6,0x2472091E,0xA2A26FEA,0xB7671E7F,0x6FEA6848,0x7F317F3C
	.word 0x1CB71CB7,0x67FAAD5C,0xB2ADFF84,0x1EFAAD5C,0x76B78B81,0x67FA76AD,0xAD01834B,0xA267FAAD
	.word 0xB957854B,0x7F7FB909,0x6709A424,0xC6A2A267,0x1E7F67B7,0xEA6F7FA2,0x3C7FD27F,0x7ABA6F6F
	.word 0x2CF56FA2,0x0000AAD7,0x4C29EA7F,0x0097DB07,0xE7FD3FA2,0x00066507,0x2C16EA31,0xC3E90E65
	.word 0xD723EF6F,0xE146DA56,0x495416BA,0x58A15A47,0x07D723F5,0x05F4500E,0x651DE723,0xACDFA126

	.word 0x50151490,0xA9BD6591,0xAB0F0A20,0xBDC4785A,0xFCCF1A63,0x56A35F87,0x331A6A4A,0x3EDAE92D
	.word 0x226E17C3,0xCEAB2733,0xDC3B9000,0x7EF2CFB3,0xBEDEBB00,0x02140A6A,0x3A1B0000,0x6BC02E28
	.word 0x3FEF48D3,0x6F6F6FEA,0x292313E7,0xA2C6EF68,0x992C9B1D,0x0DB18899,0x8D4F53E6,0xD91303A9
	.word 0x1247F141,0x1D4F9612,0x44261152,0xB447B40E,0x5A08A1A7,0x7DE4EEDA,0x27F40232,0x08A1A1A1
	.word 0x3F6F6F6F,0x237AEF3F,0x68C63C3F,0x9B342388,0x34230D88,0x4FBCB534,0xE713B503,0x5B0CBCBC
	.word 0x75F91D0C,0x7D0E65E6,0xB4FBCD65,0x25DA26B4,0xEE64E441,0xA7A10825,0xA16DA108,0x3202F437
	.word 0xA3DB4954,0xCB141550,0x5AA369BD,0x36303204,0xA0444765,0x98A8B6AE,0x27ABEB3E,0x4ADC62E8
	.word 0x322D25CE,0xC39E6122,0x0ACFF27E,0x00AC1F2B,0xDC0A1402,0x0089DE28,0x286AC08F,0x00001B3A

	.word 0x5E430000,0xE36E515D,0x20000000,0xBE0B71DE,0x00000000,0x5D0B9E60,0x00000000,0x3ADE4500
	.word 0x00000000,0x5E580000,0x00000000,0x89000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x805530B3,0xF46C6C02,0x0AC0E36A,0x1414146B,0x6A3B9E71,0xC0A81A2E,0x7735FE5D,0xD4D49EBE
	.word 0x5D5D3ABE,0x35383535,0x0B3A6EBE,0x0B770B3A,0x2E0B1000,0x3A3A17DE,0x94000000,0xBFCB5863
	.word 0x02C26CC2,0x408F5580,0x6BC11414,0x61E3C030,0x2E66A8A8,0x711F3B6A,0xBE1F3BD4,0x5D5D3571
	.word 0x355D3535,0x285D5D5D,0x71770B77,0xBE6E280B,0x3B173A3A,0x00630B2E,0x6358CBBF,0x00000021
	.word 0x5DBE3B66,0x0000BB5E,0x3B5D5D1F,0x00000058,0xACDE3A35,0x00000000,0x00ACDE3A,0x00000000
	.word 0x0000586E,0x00000000,0x000000D8,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global ballPal		@ 512 unsigned chars
	.hidden ballPal
ballPal:
	.hword 0x0000,0x321F,0x1514,0x259B,0x1D56,0x0889,0x10CF,0x1D5B
	.hword 0x1917,0x29DF,0x14F1,0x0CAC,0x217A,0x29BD,0x1D59,0x1D34
	.hword 0x0445,0x1D36,0x2159,0x217D,0x14F3,0x1915,0x219E,0x10AE
	.hword 0x1D5A,0x259E,0x10D0,0x0C8B,0x2DFF,0x217B,0x29BF,0x10AD
	.hword 0x0867,0x0022,0x14F1,0x217E,0x5B5F,0x1936,0x1D38,0x1915
	.hword 0x10AD,0x259F,0x1D59,0x10CF,0x217C,0x1914,0x10CF,0x29DF
	.hword 0x14F2,0x25BF,0x14F3,0x1913,0x217D,0x0C8C,0x0868,0x1915
	.hword 0x0C8B,0x215B,0x0CAD,0x10AE,0x29BF,0x2158,0x1D58,0x259F

	.hword 0x14D1,0x1D38,0x217C,0x0001,0x1D58,0x0C8A,0x1D37,0x1D59
	.hword 0x259E,0x217B,0x0424,0x7FFF,0x217C,0x259F,0x429F,0x215B
	.hword 0x1936,0x0CAC,0x1936,0x217A,0x217D,0x18F3,0x215A,0x31FF
	.hword 0x0868,0x639F,0x1937,0x2159,0x2DDF,0x0C8C,0x10AF,0x2158
	.hword 0x088A,0x10CF,0x14F1,0x0446,0x1937,0x1D5A,0x10D1,0x29BF
	.hword 0x259F,0x1D5A,0x10CF,0x14F2,0x1914,0x1916,0x10AF,0x259F
	.hword 0x1D58,0x0C8C,0x3A5F,0x1514,0x10CF,0x215B,0x29DF,0x0CAC
	.hword 0x2179,0x14F3,0x259E,0x2DFF,0x257D,0x1D38,0x1915,0x25BF

	.hword 0x14F3,0x6BDF,0x5F7F,0x67BF,0x361F,0x639F,0x0002,0x1D36
	.hword 0x259D,0x0023,0x18F2,0x42BF,0x6BDF,0x217B,0x0867,0x14F2
	.hword 0x0869,0x1D38,0x1915,0x10AD,0x0002,0x0000,0x217A,0x0423
	.hword 0x0446,0x257D,0x0002,0x217C,0x1D37,0x0868,0x10AE,0x0868
	.hword 0x1D36,0x1916,0x29BF,0x1D39,0x3E5F,0x14F1,0x0445,0x1915
	.hword 0x10D0,0x217C,0x14F2,0x1936,0x0C8A,0x29DF,0x1D35,0x2DFF
	.hword 0x29BF,0x217E,0x29DF,0x14D1,0x1D58,0x217C,0x18F2,0x2DDF
	.hword 0x14F1,0x29BF,0x259F,0x0002,0x217B,0x215B,0x0CAD,0x0C8A

	.hword 0x10D1,0x14F2,0x1914,0x0000,0x215A,0x10AD,0x259F,0x31FF
	.hword 0x29DF,0x2DFF,0x259C,0x0C8A,0x1917,0x1D58,0x1D37,0x14F3
	.hword 0x0C8B,0x1915,0x25BF,0x217D,0x10AE,0x29BF,0x1D59,0x217B
	.hword 0x0423,0x217D,0x1D37,0x1D5A,0x10CF,0x18F4,0x10AE,0x1914
	.hword 0x14F1,0x0445,0x217C,0x10D0,0x1D38,0x10AD,0x215A,0x217C
	.hword 0x1913,0x1916,0x259F,0x1D57,0x0CAD,0x0846,0x1D37,0x259F
	.hword 0x215A,0x1D58,0x1914,0x29BF,0x1915,0x217E,0x321F,0x088A
	.hword 0x10CF,0x1D5B,0x29DF,0x1D59,0x1D35,0x219E,0x0C8C,0x2DFF

@}}BLOCK(ball)
