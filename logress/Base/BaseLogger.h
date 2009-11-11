#ifndef BASE_LOGGER_H__INCLUDED
#define BASE_LOGGER_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include <ostream>

/*
 * Logging functionality which can be controlled by the defining LOGGING
 * Usage:
 * include this file, then use:
 * log() << "Stuff to log";
 *
 * In theory it supports anything the ostream objects support, but there
 * may be some corner cases that are not supported.
 *
 * To change the stream used by the logger at compile time, at the moment
 * only way is to edit the static Logger::getLogger() method.
 *
 * There is also a LOG_VARIABLE macro to wrap logging variable declarations
 * that should also disappear when logging is off.
 */

namespace LoggingOn {
    class Logger {
    public:
        Logger( const char* file );
        ~Logger();

        template < typename T >
        Logger& operator<<( const T & item )
        {
            if( mStream )
            {
                *mStream << item;
            }
            return *this;
        }

        // The template system wouldn't automatically infer types for some of the stream control objects,
        // so this is here to explitly support them.
        Logger& operator<<( std::basic_ostream< char, std::char_traits<char> >& (*func)(std::basic_ostream< char, std::char_traits<char> >&) )
        {
            if( mStream )
            {
                *mStream << func;
            }
            return *this;
        }

        // Another method to work around template limitations.
        Logger& operator<<( std::ios_base& (*func)(std::ios_base& _Iosbase) )
        {
            if( mStream )
            {
                *mStream << func;
            }
            return *this;
        }

        void close();

        static bool logging();
        static Logger & getLogger();

    private:
        std::ostream * mStream;
        bool mOwnStream;
    };

    inline Logger & log()
    {
        return Logger::getLogger();
    }
}

/*
 * This version of the logger is a 'do nothing' logger for when LOGGING is not defined.
 */

namespace LoggingOff {
    class Logger {
    public:
        template < typename T >
        Logger& operator<<( const T & )
        {
            return *this;
        }

        Logger& operator<<( std::basic_ostream< char, std::char_traits<char> >& (*)(std::basic_ostream< char, std::char_traits<char> >&) )
        {
            return *this;
        }

        Logger& operator<<( std::ios_base& (*)(std::ios_base& _Iosbase) )
        {
            return *this;
        }

        void close() {}

        static Logger & getLogger();
        static bool logging();
    };

    inline Logger & log()
    {
        return Logger::getLogger();
    }
}

#ifdef LOGGING

    using namespace LoggingOn;
    #define LOG_VARIABLE( variable ) variable

#else

    using namespace LoggingOff;
    #define LOG_VARIABLE( variable )

#endif


#endif // BASE_LOGGER_H__INCLUDED
