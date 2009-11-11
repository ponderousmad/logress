/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "Base/BaseLogger.h"

#include <fstream>
#include <iostream>
#include <assert.h>

bool LoggingOn::Logger::logging()
{
    return getLogger().mStream != 0;
}

LoggingOn::Logger& LoggingOn::Logger::getLogger()
{
    static LoggingOn::Logger sLogger( NULL );
    return sLogger;
}

LoggingOn::Logger::Logger( const char* logFile )
{
    if( logFile && logFile[0] )
    {
        mStream = new std::ofstream( logFile );
        mOwnStream = true;
    }
    else
    {
        mStream = &std::cout;
        mOwnStream = false;
    }
}

void LoggingOn::Logger::close()
{
    if( mStream )
    {
        *mStream << "\nEnd of log." << std::endl;
    }
    if(mOwnStream)
    {
        delete mStream;
    }
    mStream = 0;
}

LoggingOn::Logger::~Logger()
{
    close();
}

bool LoggingOff::Logger::logging()
{
    return false;
}

LoggingOff::Logger & LoggingOff::Logger::getLogger()
{
    static LoggingOff::Logger sLogger;
    return sLogger;
}
