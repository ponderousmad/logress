/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"
#include "Base/BaseAssert.h"
#include "Base/BaseLogger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <string.h>

namespace {
    const int kMaxErrorLength = 1024;
    bool sWasError = false;
    char sErrorDescription[ kMaxErrorLength ];
}

namespace Base {
    void doTearDown( const char* assertString, const char* filename, int lineNumber  )
    {
        log() << filename << "(" << lineNumber << "): Asserting: " << assertString << std::endl;
        log().close();
    }

    void reportError( const char* description, const char* filename, int lineNumber )
    {
        std::ostringstream stream;
        stream << "Assert: " << description << " at " << filename << "(" << lineNumber << ")";
#ifdef PLATFORM_WINDOWS
        strncpy_s( sErrorDescription, stream.str().c_str(), kMaxErrorLength-1 );
#else
        strncpy( sErrorDescription, stream.str().c_str(), kMaxErrorLength-1 );
#endif
        // Force null termination.
        sErrorDescription[ kMaxErrorLength-1 ] = 0;

        sWasError = true;
    }

    void reportException( const char* function, const char* description )
    {
        std::ostringstream stream;
        stream << "An exception was caught during the call to " << function;
        if( strlen( description ) > 0 )
        {
            stream << ": " << description;
        }
#ifdef PLATFORM_WINDOWS
        strncpy_s( sErrorDescription, stream.str().c_str(), kMaxErrorLength-1 );
#else
        strncpy( sErrorDescription, stream.str().c_str(), kMaxErrorLength-1 );
#endif
        // Force null termination.
        sErrorDescription[ kMaxErrorLength-1 ] = 0;
        sWasError = true;
    }

    bool wasError()
    {
        return sWasError;
    }

    const char* getErrorDescription()
    {
        if( sWasError ) {
            sWasError = false;
            return sErrorDescription;
        }
        return "";
    }
}
