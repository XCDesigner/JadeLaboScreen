#ifndef IMAGEPATH_H
#define IMAGEPATH_H

#if defined(XH_WIN)
#include "linuxPath.h"
#elif defined(XH_LINUX)
#include "windowsPath.h"
#endif

#define qmlColor "#202023"


#define LogoPic                 ":/image/LogoPic.jpg"
#define lHotEndActive           ":/image/LHotendActive.png"
#define lHotEndInactive         ":/image/LHotendInactive.png"
#define rHotEndActive           ":/image/RHotendActive.png"
#define rHotEndInactive         ":/image/RHotendInactive.png"
#define bedActive               ":/image/BedActive.png.png"
#define bedInactive             ":/image/rrr.png"

#define selfTestOk                ":/image/testok.png"
#define selfTestWait            ":/image/wait.png"

#define RECOVERY_RECORD         RECOVERY_INFO

#if defined(XH_WIN)

#elif defined(XH_LINUX)

#endif

#endif // IMAGEPATH_H
