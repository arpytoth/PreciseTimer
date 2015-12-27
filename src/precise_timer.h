/*
*  Precise Timer by Arpad Toth ( High Precision Timer Library )
*  Copyright (C) 2015  Arpad Toth
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
*  Arpad Toth <arpytoth@live.com>
*/
#ifndef _TOTH_TIMER_H_
#define _TOTH_TIMER_H_


#ifdef WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace toth 
{

  struct TimeInterval
  {
    __int64 start;
    __int64 stop;
  };

  class PreciseTimer
  {
  public:
    PreciseTimer()
    {
      reset();
    }

    void reset()
    {
      unsigned __int64 pf;
      QueryPerformanceFrequency((LARGE_INTEGER *)&pf);
      cycle_time = 1.0 / (double)pf;
    }

    void start()
    {
      reset();
      QueryPerformanceCounter((LARGE_INTEGER *)&t_interval.start);
    }

    void stop()
    {
      QueryPerformanceCounter((LARGE_INTEGER *)&t_interval.stop);
    }

    double seconds()
    {
      return (t_interval.stop - t_interval.start) * cycle_time;

    }

    double milliseconds()
    {
      return seconds() * 1000.0;
    }

    double microseconds()
    {
      return milliseconds() * 1000.0;
    }

  private:
    double cycle_time;
    TimeInterval t_interval;
  };

}

#else // [LINUX]

#include <sys/time.h>
#include <stdio.h>

namespace toth
{

  struct TimeInterval
  {
    struct timeval start;
    struct timeval stop;
  };


  class PreciseTimer
  {
  public:
    PreciseTimer()
    {
      reset();
    }

    void reset()
    {
      timerclear(&t_interval.start);
      timerclear(&t_interval.stop);
    }

    void start()
    {
      reset();
      gettimeofday(&t_interval.start, NULL);
    }

    void stop()
    {
      gettimeofday(&t_interval.stop, NULL);
    }

    double seconds()
    {
      struct timeval elapsed;
      timersub(&t_interval.stop, &t_interval.start, &elapsed);
      return (elapsed.tv_sec + elapsed.tv_usec / 1000000.0);
    }

    double milliseconds()
    {
      return seconds() * 1000.0;
    }

    double microseconds()
    {
      return milliseconds() * 1000.0;
    }
  private:
    TimeInterval t_interval;
  };

}

#endif

#endif // _TOTH_TIMER_H_
