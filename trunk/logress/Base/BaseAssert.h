#ifndef BASE_ASSERT_H__INCLUDED
#define BASE_ASSERT_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

namespace Base
{
    void doTearDown( const char* assertString, const char* filename, int lineNumber );
    void reportError( const char* assertString, const char* filename, int lineNumber );
    void reportException( const char* function, const char* message );

    bool wasError();

    // Getting the error description clears the error flag.
    const char* getErrorDescription();
}

#if defined( _DEBUG )

    #include <assert.h>

    #define ASSERT( cond ) if( !(cond) ) { Base::doTearDown( #cond, __FILE__, __LINE__ ); assert( cond ); }
    #define ABORT( description ) Base::doTearDown( description, __FILE__, __LINE__ ); assert( !description );
    #define ASSERT_VARIABLE( variable ) variable

    #define ASSERT_MSG( cond, message ) if( !(cond) ) { Base::doTearDown( message, __FILE__, __LINE__ ); assert( cond ); }
    #define ASSERT_RTN( cond, result, message ) if( !(cond) ) { Base::doTearDown( message, __FILE__, __LINE__ ); assert( cond ); return result; }

#else

    #define ASSERT( cond ) if( !(cond) ) { Base::reportError( #cond, __FILE__, __LINE__ ); }
    #define ABORT( description ) Base::reportError( description, __FILE__, __LINE__ );
    #define ASSERT_VARIABLE( variable ) variable

    #define ASSERT_MSG( cond, message ) if( !(cond) ) { Base::reportError( message, __FILE__, __LINE__ ); return; }
    #define ASSERT_RTN( cond, result, message ) if( !(cond) ) { Base::reportError( message, __FILE__, __LINE__ ); return result; }

#endif

#endif // BASE_ASSERT_H__INCLUDED
