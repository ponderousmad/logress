#ifndef BASE_TRACE_H__INCLUDED
#define BASE_TRACE_H__INCLUDED

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
