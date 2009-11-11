#ifndef BASE_STOPWATCH_H__INCLUDED
#define BASE_STOPWATCH_H__INCLUDED
/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */

#include <memory>

/*
 * Stopwatch provides high accuracy timing information.
 */

namespace Base
{
    class Stopwatch;
}

class Base::Stopwatch
{
    PREVENT_COPY_AND_ASSIGNMENT( Stopwatch );
public:
    // Stopwatch starts counting on construction.
    Stopwatch();
    ~Stopwatch();

    // Operate like a lap timer - return the
    // current ellapsed time in ms and reset the clock
    double reset();

    // Read the time since the last reset in ms
    double ellapsed() const;

private:
    void accumulate( double ellapsed );
    class Impl;

    std::auto_ptr<Impl> mImpl;
};

#endif // BASE_STOPWATCH_H__INCLUDED
