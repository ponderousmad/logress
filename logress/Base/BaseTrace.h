#ifndef BASE_TRACE_H__INCLUDED
#define BASE_TRACE_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

/*
 * The Trace utility is to allow for fine grained control of execution
 * of parts of the code at runtime. This is mostly allow logging of
 * only certain modules to be visible.
 *
 * In a header file the following line will allow you to reference a trace object:
 * DECLARE_TRACE( <trace name> );
 *
 * Then in one source file, the following will create the object to track the trace:
 * ADD_TRACE( <trace name> );
 *
 * In code, the following will then allow the block of code to execute only when
 * the trace is active:
 * TRACE( log() << "Trace active" )
 *
 * Finally, to wrap associated declarations, use TRACE_VARIABLE to exclude
 * any variables used only by the trace code.
 */
#ifdef TRACING

#include <utility>

namespace Base
{
    namespace Trace
    {
        typedef std::pair< const char*,bool > TraceActive;

        // Note, 'name' must be a compile time literal
        TraceActive& add( const char* name );
        bool activate( const char* name );
        bool deactivate( const char* name );
    };
}

// Add this at file scope (outside of any namespaces) with a unique name
#define ADD_TRACE( name )                              \
    namespace Base {                                   \
        namespace Trace {                              \
            TraceActive& sTrace##name( add( #name ) ); \
        }                                              \
    }

// Add this in a header file to expose a trace to multiple files
// Note that there needs to be at least one ADD_TRACE
#define DECLARE_TRACE( name )                 \
    namespace Base {                          \
        namespace Trace {                     \
            extern TraceActive& sTrace##name; \
        }                                     \
    }

#define TRACE( name, body ) if( Base::Trace::sTrace##name.second ) { body; }
#define TRACE_VARIABLE( variable ) variable

#else
    #define ADD_TRACE( name )
    #define DECLARE_TRACE( name )
    #define TRACE( id, body )
    #define TRACE_VARIABLE( variable )
#endif

#endif // BASE_TRACE_H__INCLUDED
