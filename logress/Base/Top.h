#ifndef TOP_H__INCLUDED
#define TOP_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#ifdef WIN32

#define WIN32_LEAN_AND_MEAN        // Exclude rarely-used stuff from Windows headers
#define PLATFORM_WINDOWS

#pragma warning( disable : 4786 )
#pragma warning( disable : 4503 )

#endif

#define PREVENT_COPY( C ) private: C( const C& );
#define PREVENT_ASSIGNMENT( C ) private: C& operator=( const C& );
#define PREVENT_COPY_AND_ASSIGNMENT( C ) private: C( const C& ); C& operator=( const C& );

#define NULLPTR 0

#endif // TOP_H__INCLUDED
