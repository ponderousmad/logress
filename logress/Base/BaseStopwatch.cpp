/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "Base/BaseStopwatch.h"
#include "Base/BaseLogger.h"

using Base::Stopwatch;

#ifdef WIN32

#include <windows.h>

class Base::Stopwatch::Impl
{
    PREVENT_COPY_AND_ASSIGNMENT( Impl );
public:
    Impl()
    {
        reset();
    }

    void reset()
    {
        QueryPerformanceCounter( &mStartTicks );
    }

    double ellapsed() const
    {
        LARGE_INTEGER ticks;
        LARGE_INTEGER frequency;
        QueryPerformanceCounter( &ticks );
        QueryPerformanceFrequency( &frequency );

        double ellapsedTicks = static_cast<double>( ticks.QuadPart - mStartTicks.QuadPart );
        double freq = static_cast<double>( frequency.QuadPart );
        return ellapsedTicks / ( freq / 1e3 );

    }
private:
    LARGE_INTEGER mStartTicks;
};

#else

#include <sys/time.h>

class Base::Stopwatch::Impl
{
    PREVENT_COPY_AND_ASSIGNMENT( Impl );
public:
    Impl()
    {
        reset();
    }

    void reset()
    {
        struct timezone dummy;
        gettimeofday( &mStartTime, &dummy );
    }

    double ellapsed() const
    {
        struct timeval time;
        struct timezone dummy;

        gettimeofday( &time, &dummy );

        double ellapsedSeconds = time.tv_sec - mStartTime.tv_sec;
        double ellapsedMicros = time.tv_usec - mStartTime.tv_usec;
        return ellapsedSeconds * 1e3 + ellapsedMicros / 1e3;
    }
private:
    struct timeval mStartTime;
};

#endif

Stopwatch::Stopwatch()
    : mImpl( new Impl() )
{
}

Stopwatch::~Stopwatch()
{
}

double Stopwatch::reset()
{
    double lap = ellapsed();
    mImpl->reset();
    return lap;
}

double Stopwatch::ellapsed() const
{
    return mImpl->ellapsed();
}
