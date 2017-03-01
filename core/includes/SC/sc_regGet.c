#include "sclib.h"

int sc_regGet(int registr, int *value)
{
	if ((registr > 0) && (registr <6)) {
		*value = BIT_CHECK(sc_reg_flags, registr);
	}
	else
		return ERR_WF;
	return 0;
}
