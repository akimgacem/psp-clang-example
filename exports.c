#include "moduleexport.h"

void extern module_start;
void extern module_info;
static const unsigned int __syslib_exports[4] __attribute__((section(".rodata.sceResident"))) = {
	0xD632ACDB,
	0xF01D73A7,
	(unsigned int) &module_start,
	(unsigned int) &module_info,
};

const struct _PspLibraryEntry __library_exports[1] __attribute__((section(".lib.ent"), used)) = {
	{0, 0x0000, 0x8000, 4, 1, 1, (void *) &__syslib_exports},
};
