#include "sclib.h"

int sc_regSet(int registr, int value)
{

	if ((registr > 0) && (registr < 6)) {
		if (value == 1)
			BIT_SET(sc_reg_flags, registr);
		else if (value == 0)
			BIT_CLEAR(sc_reg_flags, registr);
		else
			return 0;
	}
	else
		return ERR_WF;
	return 0;
}
