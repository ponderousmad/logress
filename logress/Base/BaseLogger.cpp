#include "Base/Top.h"

#include "Base/BaseLogger.h"

#include <fstream>
#include <iostream>
#include <assert.h>

namespace {
    std::ofstream* gFileStream = 0;
}

std::ostream * LoggingOn::Logger::gStream = 0;
LoggingOn::Logger LoggingOn::Logger::gLogger;
LoggingOff::Logger LoggingOff::Logger::gLogger;

bool LoggingOn::Logger::logging()
{
    return gStream != 0;
}

bool LoggingOn::Logger::init( const char* logFile )
{
    assert( !gFileStream );
    if( logFile && logFile[0] )
    {
        gFileStream = new std::ofstream( logFile );
        gStream = gFileStream;
    }
    else
    {
        gStream = &std::cout;
    }
    return gStream->good();
}

void LoggingOn::Logger::uninit()
{
    if( gFileStream ) {
        *gFileStream << "\nEnd of log." << std::endl;
    }
    delete gFileStream;
    gFileStream = 0;
    gStream = 0;
}

bool LoggingOff::Logger::logging() { return false; }
bool LoggingOff::Logger::init( const char* ) { return true; }
void LoggingOff::Logger::uninit() {}
