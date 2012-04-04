#ifndef _SYSCONF_H_
#define _SYSCONF_H_

#cmakedefine HAVE_BACKTRACE 1
#cmakedefine HAVE_SYS_UTSNAME_H 1

#define VERSION_MAJOR @mineserver_MAJOR_VERSION@
#define VERSION_MINOR @mineserver_MINOR_VERSION@
#define VERSION_PATCH @mineserver_PATCH_LEVEL@
#define VERSION_SIMPLE "@mineserver_VERSION_SIMPLE@"
#define VERSION_GIT "@VERSION_GIT@"
#define VERSION_COMPLETE "@mineserver_VERSION_COMPLETE@"

#ifdef HAVE_BACKTRACE
# include <execinfo.h>
#endif

#ifdef HAVE_SYS_UTSNAME_H
# include <sys/utsname.h>
#endif

#endif // _SYSCONF_H_