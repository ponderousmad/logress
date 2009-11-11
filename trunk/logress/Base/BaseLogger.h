#ifndef BASE_LOGGER_H__INCLUDED
#define BASE_LOGGER_H__INCLUDED

#include <ostream>

namespace LoggingOn {
    class Logger {
    public:
        template < typename T >
        Logger& operator<<( const T & item )
        {
            if( gStream )
            {
                *gStream << item;
            }
            return *this;
        }

        Logger& operator<<( std::basic_ostream< char, std::char_traits<char> >& (*func)(std::basic_ostream< char, std::char_traits<char> >&) )
        {
            if( gStream )
            {
                *gStream << func;
            }
            return *this;
        }

        Logger& operator<<( std::ios_base& (*func)(std::ios_base& _Iosbase) )
        {
            if( gStream )
            {
                *gStream << func;
            }
            return *this;
        }

        void flush() {
            if( gStream )
            {
                *gStream << std::endl;
            }
        }

        static bool logging();
        static bool init( const char* logFile );
        static void uninit();

        static Logger gLogger;

    private:
        static std::ostream * gStream;
    };

    inline Logger & log() { return Logger::gLogger; }
}

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

        void flush() {}

        static bool logging();
        static bool init( const char* logFile );
        static void uninit();

        static Logger gLogger;
    };

    inline Logger & log() { return Logger::gLogger; }
}

#ifdef LOGGING

    using namespace LoggingOn;
    #define LOG_VARIABLE( variable ) variable

#else

    using namespace LoggingOff;
    #define LOG_VARIABLE( variable )

#endif


#endif // BASE_LOGGER_H__INCLUDED
