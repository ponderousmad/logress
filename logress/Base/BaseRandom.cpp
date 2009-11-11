#include "Base/Top.h"

#include "Base/BaseRandom.h"

#include <stdlib.h>
#include <time.h>

namespace {
    bool gNeedInit = true;
    void init()
    {
        if( gNeedInit )
        {
            srand( (unsigned)time( NULL ) );
            gNeedInit = false;
        }
    }
}

int Base::random()
{
    init();
    return rand();
}
