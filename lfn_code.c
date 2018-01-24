 /* For LFN support*/


#include "ff.h"		/* Common include file for FatFs and disk I/O layer */


WCHAR ff_convert (WCHAR wch, UINT dir) {

	if (wch < 0x80){
		return wch;
		}
	return 0;
}

WCHAR ff_wtoupper (WCHAR wch) {
	
	if (wch < 0x80){
		if (wch >= 'a' && wch <= 'z'){
			wch &= ~0x20;
		}	
			return wch;
			}
		return 0;
}



