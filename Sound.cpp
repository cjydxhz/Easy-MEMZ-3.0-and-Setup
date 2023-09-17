#include"Sound.h"
#include"resource.h"

BOOL ¶ñ³ô()
{
	if (PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC) == 0) {
		return FALSE;
	}

	else {
		return TRUE;
	}
}