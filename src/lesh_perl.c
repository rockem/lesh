#include <EXTERN.h>
#include <perl.h>
#include <XSUB.h>
#include <stdlib.h>
#include "lesh_perl.h"
#include "cmd/cd_cmd.h"

EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);

static XS (XS_cd);
static XS (XS_exit);

void xs_init () {
	dXSUB_SYS;
	
	newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, __FILE__);
	newXS(_XS_CD, XS_cd, __FILE__);
	newXS(_XS_EXIT, XS_exit, __FILE__);
}

static XS (XS_cd) {
	dXSARGS;
	char* path;
	/*if(items != 1) {
		XSRETURN_IV(1);
		}*/
	path = SvPV_nolen (ST (0));
	cd_cmd(path);
}

static XS (XS_set) {
	

}

static XS (XS_alias) {
	
}

static XS (XS_exit) {
	exit(0);
}




