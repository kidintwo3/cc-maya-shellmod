#ifndef ICONS_H
#define ICONS_H

#include <cstddef>


void compileImagexmptoBinary(char * filename, char * output) {

	FILE * file = fopen(filename, "rb");
	FILE * out = fopen(output, "w");

	unsigned char buffer[32];
	size_t count;
	fprintf(out, "#pragma once \n\n static unsigned char TEXT_xmp_BYTES[] = { ");
	while (!feof(file)) {
		count = fread(buffer, 1, 32, file);

		for (int n = 0; n < count; ++n) {
			fprintf(out, "0x%02X, ", buffer[n]);
		};
	};
	fprintf(out, "};");
	fclose(file);
	fclose(out);

};

//-------------------------------------------------------------------------------------------------------------------



void writeIcon(MString path, MString filename, char * output[], int str_len) {


	static ofstream myfile;

	myfile.open(MString(path + filename).asChar());

	MGlobal::displayInfo(MString() + sizeof(*output));
	

	for (int i = 0; i < str_len; i++)
	{
		myfile << output[i] << endl;
	}


	myfile.close();
}


void icons_data_write()
{

	/* XPM */
	static char * out_shellMod_xmp[] = {
		"20 20 54 2",
		"  	c #FFFFFF",
		". 	c #000000",
		"X 	c #0A0A0A",
		"o 	c #1A1A1A",
		"O 	c #000001",
		"+ 	c #8F8F8F",
		"@ 	c #CCCCCC",
		"# 	c #212121",
		"$ 	c #030303",
		"% 	c #878787",
		"& 	c #DCDCDC",
		"* 	c #D4D4D4",
		"= 	c #BDBDBD",
		"- 	c #050505",
		"; 	c #E0E0E0",
		": 	c #BABABA",
		"> 	c #B8B8B8",
		", 	c #D1D1D1",
		"< 	c #BFBFBF",
		"1 	c #141414",
		"2 	c #828282",
		"3 	c #D9D9D9",
		"4 	c #6B3939",
		"5 	c #96522D",
		"6 	c #636363",
		"7 	c #DEB887",
		"8 	c #1F1F1F",
		"9 	c #F4A460",
		"0 	c #5E5E5E",
		"q 	c #F5DEB3",
		"w 	c #1C1C1C",
		"e 	c #5C5C5C",
		"r 	c #D6D6D6",
		"t 	c #C2C2C2",
		"y 	c #595959",
		"u 	c #B5B5B5",
		"i 	c #DEDEDE",
		"p 	c #080808",
		"a 	c #121212",
		"s 	c #575757",
		"d 	c #C4C4C4",
		"f 	c #0D0D0D",
		"g 	c #545454",
		"h 	c #DBDBDB",
		"j 	c #CFCFCF",
		"k 	c #474747",
		"l 	c #666666",
		"z 	c #55562F",
		"x 	c #B7644D",
		"c 	c #0F0F0F",
		"v 	c #E9967A",
		"b 	c #BDB76B",
		"n 	c #171717",
		"m 	c #292929",
		"      . . . X o . . . . . . . . .       ",
		"      . . O + @ # . . . . . . . .       ",
		"      . $ % & * = # . . . . . . .       ",
		"      - + ; : > , < # . . . . . .       ",
		"      1 2 3 = = > * = # . . . . .       ",
		"      4 5 6 3 7 : > , = 8 . . . .       ",
		"      4 9 5 0 3 q = > * : 8 . . .       ",
		"      4 9 9 5 0 3 7 = > * = w . .       ",
		"      4 9 9 9 5 e r t : > * > # O       ",
		"      4 9 9 9 9 5 y r q = u i > p       ",
		"      a 9 9 9 9 9 5 s r q d @ s f       ",
		"      . 1 9 9 9 9 9 5 g h j k 5 4       ",
		"      . . 1 9 9 9 9 9 5 l y 5 9 8       ",
		"      . . . a 9 9 9 9 9 z 5 9 9 8       ",
		"      . . . . a 9 9 9 9 5 x 9 9 #       ",
		"      . . . . . c 9 9 9 z x 9 9 w       ",
		"      . . . . . . c 9 9 z x 9 4 .       ",
		"      . . . . . . . f v 5 b z . .       ",
		"      . . . . . . . . n z m . . .       ",
		"      . . . . . . . . . . . . . .       "
	};


	/* XPM */
	static char * out_shellModNode_xmp[] = {
		"20 20 54 2",
		"  	c #FFFFFF",
		". 	c #000000",
		"X 	c #0A0A0A",
		"o 	c #1A1A1A",
		"O 	c #000001",
		"+ 	c #8F8F8F",
		"@ 	c #CCCCCC",
		"# 	c #212121",
		"$ 	c #030303",
		"% 	c #878787",
		"& 	c #DCDCDC",
		"* 	c #D4D4D4",
		"= 	c #BDBDBD",
		"- 	c #050505",
		"; 	c #E0E0E0",
		": 	c #BABABA",
		"> 	c #B8B8B8",
		", 	c #D1D1D1",
		"< 	c #BFBFBF",
		"1 	c #141414",
		"2 	c #828282",
		"3 	c #D9D9D9",
		"4 	c #6B3939",
		"5 	c #96522D",
		"6 	c #636363",
		"7 	c #DEB887",
		"8 	c #1F1F1F",
		"9 	c #F4A460",
		"0 	c #5E5E5E",
		"q 	c #F5DEB3",
		"w 	c #1C1C1C",
		"e 	c #5C5C5C",
		"r 	c #D6D6D6",
		"t 	c #C2C2C2",
		"y 	c #595959",
		"u 	c #B5B5B5",
		"i 	c #DEDEDE",
		"p 	c #080808",
		"a 	c #121212",
		"s 	c #575757",
		"d 	c #C4C4C4",
		"f 	c #0D0D0D",
		"g 	c #545454",
		"h 	c #DBDBDB",
		"j 	c #CFCFCF",
		"k 	c #474747",
		"l 	c #666666",
		"z 	c #55562F",
		"x 	c #B7644D",
		"c 	c #0F0F0F",
		"v 	c #E9967A",
		"b 	c #BDB76B",
		"n 	c #171717",
		"m 	c #292929",
		"      . . . X o . . . . . . . . .       ",
		"      . . O + @ # . . . . . . . .       ",
		"      . $ % & * = # . . . . . . .       ",
		"      - + ; : > , < # . . . . . .       ",
		"      1 2 3 = = > * = # . . . . .       ",
		"      4 5 6 3 7 : > , = 8 . . . .       ",
		"      4 9 5 0 3 q = > * : 8 . . .       ",
		"      4 9 9 5 0 3 7 = > * = w . .       ",
		"      4 9 9 9 5 e r t : > * > # O       ",
		"      4 9 9 9 9 5 y r q = u i > p       ",
		"      a 9 9 9 9 9 5 s r q d @ s f       ",
		"      . 1 9 9 9 9 9 5 g h j k 5 4       ",
		"      . . 1 9 9 9 9 9 5 l y 5 9 8       ",
		"      . . . a 9 9 9 9 9 z 5 9 9 8       ",
		"      . . . . a 9 9 9 9 5 x 9 9 #       ",
		"      . . . . . c 9 9 9 z x 9 9 w       ",
		"      . . . . . . c 9 9 z x 9 4 .       ",
		"      . . . . . . . f v 5 b z . .       ",
		"      . . . . . . . . n z m . . .       ",
		"      . . . . . . . . . . . . . .       "
	};


	/* XPM */
	static char * shellModNode_xmp[] = {
		"32 32 65 2",
		"  	c #FFFFFF",
		". 	c #000000",
		"X 	c #7D7D7D",
		"o 	c #7A7A7A",
		"O 	c #666666",
		"+ 	c #F2F2F2",
		"@ 	c #5E5E5E",
		"# 	c #EDEDED",
		"$ 	c #C2C2C2",
		"% 	c #EBEBEB",
		"& 	c #5C5C5C",
		"* 	c #636363",
		"= 	c #C4C4C4",
		"- 	c #B8B8B8",
		"; 	c #C7C7C7",
		": 	c #575757",
		"> 	c #595959",
		", 	c #BDBDBD",
		"< 	c #545454",
		"1 	c #0D0D0D",
		"2 	c #2B2B2B",
		"3 	c #B3B3B3",
		"4 	c #E0E0E0",
		"5 	c #C9C9C9",
		"6 	c #E8E8E8",
		"7 	c #4F4F4F",
		"8 	c #1A1A1A",
		"9 	c #96522D",
		"0 	c #141414",
		"q 	c #A8A8A8",
		"w 	c #E5E5E5",
		"e 	c #4D4D4D",
		"r 	c #030303",
		"t 	c #F4A460",
		"y 	c #080808",
		"u 	c #ABABAB",
		"i 	c #CCCCCC",
		"p 	c #474747",
		"a 	c #D1C166",
		"s 	c #D2691E",
		"d 	c #E3E3E3",
		"f 	c #454545",
		"g 	c #CFCFCF",
		"h 	c #404040",
		"j 	c #3D3D3D",
		"k 	c #363636",
		"l 	c #0A0A0A",
		"z 	c #050505",
		"x 	c #2F2F64",
		"c 	c #DCDCDC",
		"v 	c #383838",
		"b 	c #242424",
		"n 	c #292929",
		"m 	c #8B4513",
		"M 	c #B0B0B0",
		"N 	c #F8F8FF",
		"B 	c #333333",
		"V 	c #6B3939",
		"C 	c #B7644D",
		"Z 	c #2E2E2E",
		"A 	c #2F4F4F",
		"S 	c #55562F",
		"D 	c #121212",
		"F 	c #171717",
		"G 	c #262626",
		"                                                                ",
		"                                                                ",
		"            . . . . . . . . . . . . . . . . . . . .             ",
		"            . . . . . X o . . . . . . . . . . . . .             ",
		"            . . . . O + + @ . . . . . . . . . . . .             ",
		"            . . . O # $ $ % & . . . . . . . . . . .             ",
		"            . . * # = - - ; % : . . . . . . . . . .             ",
		"            . >   $ - , , - ; % < . . . . . . . . .             ",
		"            1 2 3 4 - , , , - 5 6 7 . . . . . . . .             ",
		"            8 9 0 q w - , , , - 5 6 e . . . . . . .             ",
		"            r t t y u w - , , , - i 6 p . . . . . .             ",
		"            y t a s y u d - , , , - i w f . . . . .             ",
		"            y t t t s y u w - , , , - g w h . . . .             ",
		"            y t t t t s y u d - , , , - g d j . . .             ",
		"            y t t t t t s y u d - , , , - g d k . .             ",
		"            l t t t t t t s y u d - , , , - i % e .             ",
		"            z t t t t t t t s y u d - , , - i 6 x .             ",
		"            . 2 t t t t t t t s y u d - - g c v b z             ",
		"            . . n t t t t t t t s y u 4 ; 4 n m t .             ",
		"            . . . n t t t t t t t s y M N B V a C .             ",
		"            . . . . n t t t t t t t 9 Z A V t t C .             ",
		"            . . . . . n t t t t t t a S D t t t C .             ",
		"            . . . . . . n t t t t t t 9 S t t t C .             ",
		"            . . . . . . . n t t t t t 9 V t t t C .             ",
		"            . . . . . . . . n t t t t 9 V t t t C .             ",
		"            . . . . . . . . . n t t t 9 V t t t 8 .             ",
		"            . . . . . . . . . . n t t S V a t F . .             ",
		"            . . . . . . . . . . . G a 9 S a F . . .             ",
		"            . . . . . . . . . . . . V C S V . . . .             ",
		"            . . . . . . . . . . . . . F . . . . . .             ",
		"            . . . . . . . . . . . . . . . . . . . .             ",
		"                                                                "
	};


	/* XPM */
	static char * shellModNode_Add_xmp[] = {
		"32 32 63 2",
		"  	c #FFFFFF",
		". 	c #000000",
		"X 	c #7D7D7D",
		"o 	c #7A7A7A",
		"O 	c #666666",
		"+ 	c #F2F2F2",
		"@ 	c #5E5E5E",
		"# 	c #0D0D0D",
		"$ 	c #EDEDED",
		"% 	c #C2C2C2",
		"& 	c #EBEBEB",
		"* 	c #5C5C5C",
		"= 	c #FF7256",
		"- 	c #636363",
		"; 	c #C4C4C4",
		": 	c #B8B8B8",
		"> 	c #C7C7C7",
		", 	c #575757",
		"< 	c #D52079",
		"1 	c #595959",
		"2 	c #BDBDBD",
		"3 	c #545454",
		"4 	c #2B2B2B",
		"5 	c #B3B3B3",
		"6 	c #E0E0E0",
		"7 	c #C9C9C9",
		"8 	c #E8E8E8",
		"9 	c #4F4F4F",
		"0 	c #1A1A1A",
		"q 	c #96522D",
		"w 	c #141414",
		"e 	c #A8A8A8",
		"r 	c #E5E5E5",
		"t 	c #D4D4D4",
		"y 	c #424242",
		"u 	c #030303",
		"i 	c #F4A460",
		"p 	c #080808",
		"a 	c #ABABAB",
		"s 	c #616161",
		"d 	c #FF6347",
		"f 	c #D1C166",
		"g 	c #D2691E",
		"h 	c #E3E3E3",
		"j 	c #A6A6A6",
		"k 	c #A1A1A1",
		"l 	c #CFCFCF",
		"z 	c #0A0A0A",
		"x 	c #787878",
		"c 	c #050505",
		"v 	c #8C8C8C",
		"b 	c #B5B5B5",
		"n 	c #292929",
		"m 	c #B0B0B0",
		"M 	c #F8F8FF",
		"N 	c #2E2E2E",
		"B 	c #2F4F4F",
		"V 	c #6B3939",
		"C 	c #55562F",
		"Z 	c #121212",
		"A 	c #B7644D",
		"S 	c #171717",
		"D 	c #262626",
		"                                                                ",
		"                                                                ",
		"      . . . . . . . . . . . . . . . . . . . .                   ",
		"      . . . . . X o . . . . . . . . . . . . . . . . . . . . . . ",
		"      . . . . O + + @ . . . . . . . . . # # # # . . . . . . . . ",
		"      . . . O $ % % & * . . . . . . . # = = = = # . . . . . . . ",
		"      . . - $ ; : : > & , . . . . . . # = < < = # . . . . . . . ",
		"      . 1   % : 2 2 : > & 3 . . . . . # = < < = # . . . . . . . ",
		"      # 4 5 6 : 2 2 2 : 7 8 9 . . . . # = < < = # . . . . . . . ",
		"      0 q w e r : 2 2 2 : ; t y . . . # = < < = # . . . . . . . ",
		"      u i i p a r : 2 2 : s # # # # # 0 d < < d 0 # # # # # . . ",
		"      p i f g p a h : 2 a # = = = = = d < < < < d = = = = = # . ",
		"      p i i i g p a r : j # = < < < < < < < < < < < < < < = # . ",
		"      p i i i i g p a h k # = < < < < < < < < < < < < < < = # . ",
		"      p i i i i i g p a l # = = = = = d < < < < d = = = = = # . ",
		"      z i i i i i i g p j x # # # # # 0 d < < d 0 # # # # # . . ",
		"      c i i i i i i i g p j l k j j v # = < < = # . . . . . . . ",
		"      . 4 i i i i i i i g p a h : : b # = < < = # . . . . . . . ",
		"      . . n i i i i i i i g p a 6 > ; # = < < = # . . . . . . . ",
		"      . . . n i i i i i i i g p m M 4 # = < < = # . . . . . . . ",
		"      . . . . n i i i i i i i q N B V # = = = = # . . . . . . . ",
		"      . . . . . n i i i i i i f C Z i C # # # # . . . . . . . . ",
		"      . . . . . . n i i i i i i q C i i i q . . . . . . . . . . ",
		"      . . . . . . . n i i i i i q V i i i A . . . . . . . . . . ",
		"      . . . . . . . . n i i i i q V i i i A .                   ",
		"      . . . . . . . . . n i i i q V i i i 0 .                   ",
		"      . . . . . . . . . . n i i C V f i S . .                   ",
		"      . . . . . . . . . . . D f q C f S . . .                   ",
		"      . . . . . . . . . . . . V A C V . . . .                   ",
		"      . . . . . . . . . . . . . S . . . . . .                   ",
		"      . . . . . . . . . . . . . . . . . . . .                   ",
		"                                                                "
	};


	/* XPM */
	static char * shellModNode_Apply_xmp[] = {
		"14 14 2 2",
		"  	c #FFFFFF",
		". 	c #1E90FF",
		"                            ",
		"                            ",
		"                            ",
		"                            ",
		"          . . . .           ",
		"        . . . . . .         ",
		"        . . . . . .         ",
		"        . . . . . .         ",
		"        . . . . . .         ",
		"          . . . .           ",
		"                            ",
		"                            ",
		"                            ",
		"                            "
	};


	/* XPM */
	static char * shellModNode_CCLogo_xmp[] = {
		"20 20 48 2",
		"  	c #6B6B6B",
		". 	c #6E6E6E",
		"X 	c #636363",
		"o 	c #616161",
		"O 	c #696969",
		"+ 	c #666666",
		"@ 	c #828282",
		"# 	c #878787",
		"$ 	c #999999",
		"% 	c #BDBDBD",
		"& 	c #C2C2C2",
		"* 	c #A6A6A6",
		"= 	c #787878",
		"- 	c #5E5E5E",
		"; 	c #858585",
		": 	c #B0B0B0",
		"> 	c #8C8C8C",
		", 	c #ABABAB",
		"< 	c #969696",
		"1 	c #737373",
		"2 	c #4A4A4A",
		"3 	c #9C9C9C",
		"4 	c #B8B8B8",
		"5 	c #525252",
		"6 	c #ADADAD",
		"7 	c #5C5C5C",
		"8 	c #8F8F8F",
		"9 	c #545454",
		"0 	c #949494",
		"q 	c #A3A3A3",
		"w 	c #DCDCDC",
		"e 	c #4D4D4D",
		"r 	c #757575",
		"t 	c #D6D6D6",
		"y 	c #B5B5B5",
		"u 	c #7A7A7A",
		"i 	c #A1A1A1",
		"p 	c #BABABA",
		"a 	c #B3B3B3",
		"s 	c #8A8A8A",
		"d 	c #9E9E9E",
		"f 	c #DEDEDE",
		"g 	c #575757",
		"h 	c #A8A8A8",
		"j 	c #7F7F7F",
		"k 	c #707070",
		"l 	c #7D7D7D",
		"z 	c #BFBFBF",
		"                                        ",
		"                                        ",
		"              .   X o O .               ",
		"            . + o @ # O o .             ",
		"          . o   $ % & * = - O .         ",
		"      . + o ; : > $ * @ , < + o   .     ",
		"  .   - 1 * * = 2 3 4 5 + 3 6 @ 7 + .   ",
		"    O ; * 8 - 9 @ , , 0 - 9 @ q 0 . O   ",
		". o ; w 0 e + 3 : r + q , = 2 1 t , -   ",
		". o > q # y 6 # + X + o u * 4 0 > i X   ",
		". o > i ; p a ; X + O o = * p $ s d X   ",
		". o ; f 0 e + i 6 1 X i , u e r t 6 -   ",
		"    O # * > 7 g ; h , < - 9 j i < k O   ",
		"  . O 7 1 * * r 2 3 4 9 X $ 6 ; 7 + .   ",
		"      . X o s : # < * l , $ O o   .     ",
		"        .   - . 3 z & h u 7 O .         ",
		"            . + o @ s   o               ",
		"              .   o o O .               ",
		"                                        ",
		"                                        "
	};


	/* XPM */
	static char * shellModNode_Minus_xmp[] = {
		"14 14 2 2",
		"  	c #FFFFFF",
		". 	c #D11619",
		"                            ",
		"                            ",
		"                            ",
		"                            ",
		"                            ",
		"                            ",
		"        . . . . . .         ",
		"        . . . . . .         ",
		"                            ",
		"                            ",
		"                            ",
		"                            ",
		"                            ",
		"                            "
	};

	/* XPM */
	static char * shellModNode_Plane_xmp[] = {
		"32 32 60 2",
		"  	c #FFFFFF",
		". 	c #3B3B3B",
		"X 	c #383838",
		"o 	c #2E2E2E",
		"O 	c #333333",
		"+ 	c #55562F",
		"@ 	c #6B3939",
		"# 	c #B7644D",
		"$ 	c #F4A460",
		"% 	c #303030",
		"& 	c #E9967A",
		"* 	c #91535D",
		"= 	c #363636",
		"- 	c #BDB76B",
		"; 	c #1C1C1C",
		": 	c #2B2B2B",
		"> 	c #292929",
		", 	c #262626",
		"< 	c #3D3D3D",
		"1 	c #858585",
		"2 	c #474747",
		"3 	c #4D4D4D",
		"4 	c #9C9C9C",
		"5 	c #4A4A4A",
		"6 	c #999999",
		"7 	c #9E9E9E",
		"8 	c #6B6B6B",
		"9 	c #737373",
		"0 	c #ADADAD",
		"q 	c #B0B0B0",
		"w 	c #424242",
		"e 	c #5E5E5E",
		"r 	c #8A8A8A",
		"t 	c #A1A1A1",
		"y 	c #919191",
		"u 	c #545454",
		"i 	c #6E6E6E",
		"p 	c #A3A3A3",
		"a 	c #7F7F7F",
		"s 	c #525252",
		"d 	c #8F8F8F",
		"f 	c #8C8C8C",
		"g 	c #949494",
		"h 	c #595959",
		"j 	c #5C5C5C",
		"k 	c #454545",
		"l 	c #696969",
		"z 	c #A8A8A8",
		"x 	c #A6A6A6",
		"c 	c #7A7A7A",
		"v 	c #616161",
		"b 	c #787878",
		"n 	c #969696",
		"m 	c #575757",
		"M 	c #757575",
		"N 	c #828282",
		"B 	c #C2C2C2",
		"V 	c #878787",
		"C 	c #4F4F4F",
		"Z 	c #404040",
		"                                                                ",
		"                                                                ",
		"                                                                ",
		"                                                                ",
		"                                                                ",
		"    . . . . . . . . . . . . X o o X . . . . . . . . . . . .     ",
		"    . . . . . . . . . . . O o + + o O . . . . . . . . . . .     ",
		"    . . . . . . . . . X o @ # $ $ # @ o X . . . . . . . . .     ",
		"    . . . . . . . . O o + $ $ $ $ $ $ + o O . . . . . . . .     ",
		"    . . . . . . X % @ # $ $ $ $ $ $ $ $ # @ % X . . . . . .     ",
		"    . . . . . O o + + & $ $ $ $ $ $ $ $ & + + o O . . . . .     ",
		"    . . . X o @ # $ # + * $ $ $ $ $ $ * + # $ # @ o X . . .     ",
		"    . . = o + $ $ $ $ & + + - $ $ & + + & $ $ $ $ + o = . .     ",
		"    X O @ # $ $ $ $ $ $ $ * + # # + * $ $ $ $ $ $ $ # @ O X     ",
		"    O ; # $ $ $ $ $ $ $ $ $ # : : # $ $ $ $ $ $ $ $ $ # > =     ",
		"    X , = * $ $ $ $ $ $ $ * + * # + * $ $ $ $ $ $ $ * + < X     ",
		"    . o 1 2 + & $ $ $ $ + + - $ $ - + + $ $ $ $ & + 3 4 5 .     ",
		"    . o 6 7 8 @ # $ # + * $ $ $ $ $ $ * + # $ # @ 9 0 q w .     ",
		"    e o r 6 t y 3 + + - $ $ $ $ $ $ $ $ - + + 3 6 q q 4 O e     ",
		"    u o X i 6 7 p i @ # $ $ $ $ $ $ $ $ # @ i 0 q 0 a < o u     ",
		"    e u = o s d 4 t f 2 + $ $ $ $ $ $ + 5 g q q 7 h % = u e     ",
		"    . . j k o X 9 6 4 4 e @ # $ $ # @ l z x x c < o k j . .     ",
		"    . . . v u O o u y 6 4 b % + + = a 4 6 n m % O u v . . .     ",
		"    . . . . . j w o . M 6 6 N o w y g g g . o w j . . . . .     ",
		"    v v B B B B e s O o m g V w V 6 g g o O s e B B B B v v     ",
		"    v v B B B B B B j w o < i w V b < o w j B B B B B B v v     ",
		"    v v B B B B B B B e C % o . u % % C e B B B B B B B v v     ",
		"    v v v v v v v v v v v h Z o o Z h v v v v v v v v v v v     ",
		"    v v v v v v v v v v v v e C C e v v v v v v v v v v v v     ",
		"                                                                ",
		"                                                                ",
		"                                                                "
	};


	/* XPM */
	static char * shellModNode_Plus_xmp[] = {
		"14 14 2 2",
		"  	c #FFFFFF",
		". 	c #00C05E",
		"                            ",
		"                            ",
		"                            ",
		"                            ",
		"            . .             ",
		"            . .             ",
		"        . . . . . .         ",
		"        . . . . . .         ",
		"            . .             ",
		"            . .             ",
		"                            ",
		"                            ",
		"                            ",
		"                            "
	};

	/* XPM */
	static char * shellModNode_Preset_xmp[] = {
		"14 14 3 2",
		"  	c #FFFFFF",
		". 	c #000000",
		"X 	c #545454",
		"                            ",
		"    . . . . . . . . . . .   ",
		"  . X X X X X X X X X X .   ",
		"  . X X X X X X X X X X .   ",
		"  . X X X X X X X X X X .   ",
		"  . X X X X X X X X X X .   ",
		"  . X X X X X X X X X X .   ",
		"  . X X X X X X X X X X .   ",
		"  . X X X X X X X X X X .   ",
		"  . X X X X X X X X X X .   ",
		"  . X X X X X X X X X X .   ",
		"  . X X X X X X X X X X .   ",
		"  . . . . . . . . . . . .   ",
		"                            "
	};

	/* XPM */
	static char * shellModNode_Refresh_xmp[] = {
		"14 14 2 2",
		"  	c #FFFFFF",
		". 	c #000000",
		"                            ",
		"                            ",
		"        . . . . . .         ",
		"      . .       . . . .     ",
		"      .   . . .   .   .     ",
		"      . . . . . .     .     ",
		"    . . . . . .       .     ",
		"    .       . . . . . .     ",
		"    .     . . . . . .       ",
		"    .   .   . . .   .       ",
		"    . . . .       . .       ",
		"        . . . . . .         ",
		"                            ",
		"                            "
	};

	/* XPM */
	static char * shellModNode_Trash_xmp[] = {
		"14 14 4 2",
		"  	c #FFFFFF",
		". 	c #000000",
		"X 	c #ABABAB",
		"o 	c #333333",
		"                            ",
		"            . . .           ",
		"          . . . . .         ",
		"    . . . . . . . . . .     ",
		"    . X X X X X X X X .     ",
		"    . . . . . . . . . .     ",
		"    . . X X X X X X . .     ",
		"    . . X X o X o X . .     ",
		"    . . X X o X o X . .     ",
		"      . X X o X o X . .     ",
		"      . X X o X o X . .     ",
		"      . X X X X X X . .     ",
		"      . . . . . . . . .     ",
		"                            "
	};



	//compileImagexmptoBinary("shellModNode_Add.xmp", "shellModNode_Add.txt");

	MString path;
	MGlobal::executeCommand("internalVar -userBitmapsDir", path);
	MGlobal::displayInfo(MString() + "[ShellMod] Icons path: " + path);

	std::string c_path = path.asChar();

	writeIcon(path, "out_shellMod.xmp", out_shellMod_xmp, 76);
	writeIcon(path, "out_shellModNode.xmp", out_shellModNode_xmp, 76);
	writeIcon(path, "shellModNode.xmp", shellModNode_xmp, 98);
	writeIcon(path, "shellModNode_Add.xmp", shellModNode_Add_xmp, 96);
	writeIcon(path, "shellModNode_Apply.xmp", shellModNode_Apply_xmp, 17);
	writeIcon(path, "shellModNode_CCLogo.xmp", shellModNode_CCLogo_xmp, 69);
	writeIcon(path, "shellModNode_Minus.xmp", shellModNode_Minus_xmp, 17);
	writeIcon(path, "shellModNode_Plane.xmp", shellModNode_Plane_xmp, 93);

	writeIcon(path, "shellModNode_Plus.xmp", shellModNode_Plus_xmp, 17);
	writeIcon(path, "shellModNode_Preset.xmp", shellModNode_Preset_xmp, 18);
	writeIcon(path, "shellModNode_Refresh.xmp", shellModNode_Refresh_xmp, 17);
	writeIcon(path, "shellModNode_Trash.xmp", shellModNode_Trash_xmp, 19);


	//// Shell Icons
	//ofstream myfile;

	//myfile.open(MString(path + "shellModNode.xmp").asChar());



	//myfile.write((char *)shellModNode_xmp, sizeof(shellModNode_xmp));
	//for (int i = 0; i < size; i++)
	//{

	//}
	//myfile.close();
	//MGlobal::displayInfo(MString() + "[ShellMod] Created icon: " + path + "shellModNode.xmp");

	//myfile.open(MString(path + "out_shellModNode.smp").asChar());
	//myfile.write((char *)out_shellModNode_xmp, sizeof(out_shellModNode_xmp));
	//myfile.close();
	//MGlobal::displayInfo(MString() + "[ShellMod] Created icon: " + path + "out_shellModNode.xmp");

	//myfile.open(MString(path + "shellModNode_Add.xmp").asChar());
	//myfile.write((char *)shellModNode_Add_xmp, sizeof(shellModNode_Add_xmp));
	//myfile.close();
	//MGlobal::displayInfo(MString() + "[ShellMod] Created icon: " + path + "shellModNode_Add.xmp");


	//myfile.open(MString(path + "shellModNode_Plane.xmp").asChar());
	//myfile.write((char *)shellModNode_Plane_xmp, sizeof(shellModNode_Plane_xmp));
	//myfile.close();
	//MGlobal::displayInfo(MString() + "[ShellMod] Created icon: " + path + "shellModNode_Plane.xmp");

	//// AE Template Icons
	//myfile.open(MString(path + "shellModNode_Apply.xmp").asChar());
	//myfile.write((char *)shellModNode_Apply_xmp, sizeof(shellModNode_Apply_xmp));
	//myfile.close();
	//MGlobal::displayInfo(MString() + "[ShellMod] Created icon: " + path + "shellModNode_Apply.xmp");

	//myfile.open(MString(path + "shellModNode_Minus.xmp").asChar());
	//myfile.write((char *)shellModNode_Minus_xmp, sizeof(shellModNode_Minus_xmp));
	//myfile.close();
	//MGlobal::displayInfo(MString() + "[ShellMod] Created icon: " + path + "shellModNode_Minus.xmp");

	//myfile.open(MString(path + "shellModNode_Plus.xmp").asChar());
	//myfile.write((char *)shellModNode_Plus_xmp, sizeof(shellModNode_Plus_xmp));
	//myfile.close();
	//MGlobal::displayInfo(MString() + "[ShellMod] Created icon: " + path + "shellModNode_Plus.xmp");

	//myfile.open(MString(path + "shellModNode_Preset.xmp").asChar());
	//myfile.write((char *)shellModNode_Preset_xmp, sizeof(shellModNode_Preset_xmp));
	//myfile.close();
	//MGlobal::displayInfo(MString() + "[ShellMod] Created icon: " + path + "shellModNode_Preset.xmp");

	//myfile.open(MString(path + "shellModNode_Refresh.xmp").asChar());
	//myfile.write((char *)shellModNode_Refresh_xmp, sizeof(shellModNode_Refresh_xmp));
	//myfile.close();
	//MGlobal::displayInfo(MString() + "[ShellMod] Created icon: " + path + "shellModNode_Refresh.xmp");

	//myfile.open(MString(path + "shellModNode_Trash.xmp").asChar());
	//myfile.write((char *)shellModNode_Trash_xmp, sizeof(shellModNode_Trash_xmp));
	//myfile.close();
	//MGlobal::displayInfo(MString() + "[ShellMod] Created icon: " + path + "shellModNode_Trash.xmp");

	//myfile.open(MString(path + "shellModNode_CCLogo.xmp").asChar());
	//myfile.write((char *)shellModNode_CCLogo_xmp, sizeof(shellModNode_CCLogo_xmp));
	//myfile.close();
	//MGlobal::displayInfo(MString() + "[ShellMod] Created icon: " + path + "shellModNode_CCLogo.xmp");


}

#endif