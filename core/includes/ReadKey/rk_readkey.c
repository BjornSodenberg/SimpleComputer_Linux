#include "readkeylib.h"

int rk_readkey(enum keys *key)
{
	char buff[16];
	int read_ch;
	read_ch = read(1,buff,15);
	if( read_ch < 0 ) return -1;
	if( strcmp( buff, "l" )        == 0 ) *key = l_key;
	if( strcmp( buff, "s" )        == 0 ) *key = s_key;
	if( strcmp( buff, "r" )        == 0 ) *key = r_key;
	if( strcmp( buff, "t" )        == 0 ) *key = t_key;
	if( strcmp( buff, "i" )        == 0 ) *key = i_key;
	if( strcmp( buff, "\033[15~" ) == 0 ) *key = f5_key;
	if( strcmp( buff, "\033[17~" ) == 0 ) *key = f6_key;
	if( strcmp( buff, "\033[A" )   == 0 ) *key = up_key;
	if( strcmp( buff, "\033[B" )   == 0 ) *key = down_key;
	if( strcmp( buff, "\033[C" )   == 0 ) *key = left_key;
	if( strcmp( buff, "\033[D" )   == 0 ) *key = right_key;
	if( strcmp( buff, "\n" )       == 0 ) *key = enter_key;

	return 0;
}
