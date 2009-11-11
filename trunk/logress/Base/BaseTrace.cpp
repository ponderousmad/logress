/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#ifdef TRACING

#include "Base/BaseTrace.h"

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <assert.h>

namespace {
    typedef std::map< std::string, Base::Trace::TraceActive > Traces;

    Traces& traces()
    {
        static Traces sTraces;
        return sTraces;
    }

    bool setTraceActive( const char* name, bool value )
    {
        Traces::iterator trace( traces().find( name ) );
        if( traces().end() != trace )
        {
            trace->second.second = value;
            return true;
        }
        return false;
    }
}

namespace Base
{
    namespace Trace {

        TraceActive& add( const char* name )
        {
            assert( name );
            TraceActive& trace = traces()[ name ];
            trace.first = name;
            trace.second = false;
            return trace;
        }

        bool activate( const char* name )
        {
            return setTraceActive( name, true );
        }

        bool deactivate( const char* name )
        {
            return setTraceActive( name, false );
        }
    }
}

#endif // TRACING
