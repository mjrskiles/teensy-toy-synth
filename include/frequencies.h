//
// Created by Michael Skiles on 8/11/21.
//

/*
 *
Pitch 	MIDI Key 	Frequency (Hz)

C -1 	0 		8.176
C# -1 	1 		8.662
D -1 	2 		9.177
D# -1 	3 		9.723
E -1 	4 		10.301
F -1 	5 		10.913
F# -1 	6 		11.562
G -1 	7 		12.250
G# -1 	8 		12.978
A -1 	9 		13.750
A# -1 	10 		14.568
B -1 	11 		15.434
C 0 	12 		16.352
C# 0 	13 		17.324
D 0 	14 		18.354
D# 0 	15 		19.445
E 0 	16 		20.601
F 0 	17 		21.826
F# 0 	18 		23.124
G 0 	19 		24.499
G# 0 	20 		25.956
A 0 	21 		27.500* Lowest note on piano
A# 0 	22 		29.135
B 0 	23 		30.867
C 1 	24 		32.703
C# 1 	25 		34.648
D 1 	26 		36.708
D# 1 	27 		38.890
E 1 	28 		41.203
F 1 	29 		43.653
F# 1 	30 		46.249
G 1 	31 		48.999
G# 1 	32 		51.913
A 1 	33 		55.000
A# 1 	34 		58.270
B 1 	35 		61.735
C 2 	36 		65.406
C# 2 	37 		69.295
D 2 	38 		73.416
D# 2 	39 		77.781
E 2 	40 		82.406
F 2 	41 		87.307
F# 2 	42 		92.499
G 2 	43 		97.998
G# 2 	44 		103.82
A 2 	45 		110.00
A# 2 	46 		116.54
B 2 	47 		123.47
C 3 	48 		130.81
C# 3 	49 		138.59
D 3 	50 		146.83
D# 3 	51 		155.56
E 3 	52 		164.81
F 3 	53 		174.61
F# 3 	54 		184.99
G 3 	55 		195.99
G# 3 	56 		207.65
A 3 	57 		220.00
A# 3 	58 		233.08
B 3 	59 		246.94
C 4 	60 		261.63* Middle-C
C# 4 	61 		277.18
D 4 	62 		293.66
D# 4 	63 		311.13
E 4 	64 		329.63
F 4 	65 		349.23
F# 4 	66 		369.99
G 4 	67 		391.99
G# 4 	68 		415.31
A 4 	69 		440.00
A# 4 	70 		466.16
B 4 	71 		493.88
C 5 	72 		523.25
C# 5 	73 		554.37
D 5 	74 		587.33
D# 5 	75 		622.25
E 5 	76 		659.26
F 5 	77 		698.46
F# 5 	78 		739.99
G 5 	79 		783.99
G# 5 	80 		830.61
A 5 	81 		880.00
A# 5 	82 		932.32
B 5 	83 		987.77
C 6 	84 		1046.5
C# 6 	85 		1108.7
D 6 	86 		1174.7
D# 6 	87 		1244.5
E 6 	88 		1318.5
F 6 	89 		1396.9
F# 6 	90 		1480.0
G 6 	91 		1568.0
G# 6 	92 		1661.2
A 6 	93 		1760.0
A# 6 	94 		1864.7
B 6 	95 		1975.5
C 7 	96 		2093.0
C# 7 	97 		2217.5
D 7 	98 		2349.3
D# 7 	99 		2489.0
E 7 	100 		2637.0
F 7 	101 		2793.8
F# 7 	102 		2960.0
G 7 	103 		3136.0
G# 7 	104 		3322.4
A 7 	105 		3520.0
A# 7 	106 		3729.3
B 7 	107 		3951.1
C 8 	108 		4186.0* Highest note on piano
C# 8 	109 		4434.9
D 8 	110 		4698.6
D# 8 	111 		4978.0
E 8 	112 		5274.0
F 8 	113 		5587.7
F# 8 	114 		5919.9
G 8 	115 		6271.9
G# 8 	116 		6644.9
A 8 	117 		7040.0
A# 8 	118 		7458.6
B 8 	119 		7902.1
C 9 	120 		8372.0
C# 9 	121 		8869.8
D 9 	122 		9397.3
D# 9 	123 		9956.1
E 9 	124 		10548.1
F 9 	125 		11175.3
F# 9 	126 		11839.8
G 9 	127 		12543.9
 */

#ifndef SYNTH_FREQUENCIES_H
#define SYNTH_FREQUENCIES_H

#define FREQ_CMINUS1   8.176
#define FREQ_CSMINUS1  8.662
#define FREQ_DMINUS1   9.177
#define FREQ_DSMINUS1  9.723
#define FREQ_EMINUS1   10.301
#define FREQ_FMINUS1   10.913
#define FREQ_FSMINUS1  11.562
#define FREQ_GMINUS1   12.250
#define FREQ_GSMINUS1  12.978
#define FREQ_AMINUS1   13.750
#define FREQ_ASMINUS1  14.568
#define FREQ_BMINUS1   15.434
#define FREQ_C0        16.352
#define FREQ_CS0       17.324
#define FREQ_D0        18.354
#define FREQ_DS0       19.445
#define FREQ_E0        20.601
#define FREQ_F0        21.826
#define FREQ_FS0       23.124
#define FREQ_G0        24.499
#define FREQ_GS0       25.956
#define FREQ_A0        27.500
#define FREQ_AS0       29.135
#define FREQ_B0        30.867
#define FREQ_C1        32.703
#define FREQ_CS1       34.648
#define FREQ_D1        36.708
#define FREQ_DS1       38.890
#define FREQ_E1        41.203
#define FREQ_F1        43.653
#define FREQ_FS1       46.249
#define FREQ_G1        48.999
#define FREQ_GS1       51.913
#define FREQ_A1        55.000
#define FREQ_AS1       58.270
#define FREQ_B1        61.735
#define FREQ_C2        65.406
#define FREQ_CS2       69.295
#define FREQ_D2        73.416
#define FREQ_DS2       77.781
#define FREQ_E2        82.406
#define FREQ_F2        87.307
#define FREQ_FS2       92.499
#define FREQ_G2        97.998
#define FREQ_GS2       103.82
#define FREQ_A2        110.00
#define FREQ_AS2       116.54
#define FREQ_B2        123.47
#define FREQ_C3        130.81
#define FREQ_CS3       138.59
#define FREQ_D3        146.83
#define FREQ_DS3       155.56
#define FREQ_E3        164.81
#define FREQ_F3        174.61
#define FREQ_FS3       184.99
#define FREQ_G3        195.99
#define FREQ_GS3       207.65
#define FREQ_A3        220.00
#define FREQ_AS3       233.08
#define FREQ_B3        246.94
#define FREQ_C4        261.63
#define FREQ_CS4 	   277.18
#define FREQ_D4        293.66
#define FREQ_DS4 	   311.13
#define FREQ_E4 	   329.63
#define FREQ_F4 	   349.23
#define FREQ_FS4       369.99
#define FREQ_G4 	   391.99
#define FREQ_GS4 	   415.31
#define FREQ_A4 	   440.00
#define FREQ_AS4 	   466.16
#define FREQ_B4        493.88
#define FREQ_C5        523.25
#define FREQ_CS5       554.37
#define FREQ_D5        587.33
#define FREQ_DS5       622.25
#define FREQ_E5        659.26
#define FREQ_F5        698.46
#define FREQ_FS5       739.99
#define FREQ_G5        783.99
#define FREQ_GS5       830.61
#define FREQ_A5        880.00
#define FREQ_AS5       932.32
#define FREQ_B5        987.77
#define FREQ_C6        1046.5
#define FREQ_CS6       1108.7
#define FREQ_D6        1174.7
#define FREQ_DS6       1244.5
#define FREQ_E6        1318.5
#define FREQ_F6        1396.9
#define FREQ_FS6       1480.0
#define FREQ_G6        1568.0
#define FREQ_GS6       1661.2
#define FREQ_A6        1760.0
#define FREQ_AS6       1864.7
#define FREQ_B6        1975.5
#define FREQ_C7        2093.0
#define FREQ_CS7       2217.5
#define FREQ_D7        2349.3
#define FREQ_DS7       2489.0
#define FREQ_E7        2637.0
#define FREQ_F7        2793.8
#define FREQ_FS7       2960.0
#define FREQ_G7        3136.0
#define FREQ_GS7       3322.4
#define FREQ_A7        3520.0
#define FREQ_AS7       3729.3
#define FREQ_B7        3951.1
#define FREQ_C8        4186.0
#define FREQ_CS8       4434.9
#define FREQ_D8        4698.6
#define FREQ_DS8       4978.0
#define FREQ_E8        5274.0
#define FREQ_F8        5587.7
#define FREQ_FS8       5919.9
#define FREQ_G8        6271.9
#define FREQ_GS8       6644.9
#define FREQ_A8        7040.0
#define FREQ_AS8       7458.6
#define FREQ_B8        7902.1
#define FREQ_C9        8372.0
#define FREQ_CS9       8869.8
#define FREQ_D9        9397.3
#define FREQ_DS9       9956.1
#define FREQ_E9        10548.1
#define FREQ_F9        11175.3
#define FREQ_FS9       11839.8
#define FREQ_G9        12543.9

#endif //SYNTH_FREQUENCIES_H
