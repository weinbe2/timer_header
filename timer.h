/////////////////////////////
// Simple timing routines. //
// ESW 2017-10-12          //////////////////
// This header is maintained at            //
// https://github.com/weinbe2/timer_header //
/////////////////////////////////////////////

// Notes: You need to compile with the library flag '-lrt'.
// These routines can be used to time the number of seconds
// (as a double) that pass between calls to
// begin_timing and end_timing.
// This version should play nicely with C and C++, 
// furthermore, it supports different versions of the C
// and C++ standard. 

#ifndef TIMING_HEADER
#define TIMING_HEADER

#include <time.h>

#ifdef __cplusplus // Are we using C++?
  #if __cplusplus > 199711L // Use chrono class from C++11.
   #include <chrono>
   #define ESW_USE_CHRONO
   typedef std::chrono::time_point<std::chrono::steady_clock> time_sec_t;
  #else // Older version of C++.
    #ifdef CLOCK_PROCESS_CPUTIME_ID
      #define ESW_USE_CLOCK_GETTIME
      typedef timespec timeinfo;
      typedef double time_sec_t;
    #else // have to use "clock()"
      #define ESW_USE_CLOCK
      typedef double time_sec_t;
    #endif
  #endif // Checking C++ version
#else // we're using C.
  #if __STDC_VERSION__ >= 199901L // Are we using C99?
    #define ESW_USE_CLOCK
  #else // We're using an older version of C.
    #ifdef CLOCK_PROCESS_CPUTIME_ID
      #define ESW_USE_CLOCK_GETTIME
      typedef timespec timeinfo;
      typedef double time_sec_t;
    #else // have to use "clock()"
      #define ESW_USE_CLOCK
      typedef double time_sec_t;
    #endif
  #endif
    typedef double time_sec_t;
#endif

// Gets the "current" time in seconds relative
// to something (implementation, etc, dependent).
// The only guarantee is it's in units seconds.
time_sec_t curr_timing()
{
  time_sec_t curr_time;
  #ifdef ESW_USE_CHRONO
    curr_time = std::chrono::steady_clock::now();
  #elif defined ESW_USE_CLOCK
    clock_t start_ct;
    start_ct = clock();
    curr_time = ((double)(start_ct))/CLOCKS_PER_SEC; // guaranteed to be 1,000,000
  #elif defined ESW_USE_CLOCK_GETTIME
    timeinfo timespec_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timespec_time);
    double time_sec = ((double)(timespec_time.tv_sec)) + ((double)(timespec_time.tv_nsec))*1e-9;
    curr_time = time_sec;
  #endif
  return curr_time;
}

// Begin timing.
time_sec_t begin_timing()
{
  return curr_timing();
}

// Returns the time, in seconds, between the current
// time and the input time struct. The input time struct
// should ideally come from begin_timing.
double end_timing(time_sec_t* begin_time)
{
  time_sec_t end_time = curr_timing();
  #ifdef ESW_USE_CHRONO
    std::chrono::duration<double> diff_in_time = end_time - *begin_time;
    return diff_in_time.count();
  #elif defined ESW_USE_CLOCK
    return end_time - *begin_time;
  #elif defined ESW_USE_CLOCK_GETTIME
    return end_time - *begin_time;
  #endif
}


#ifdef ESW_USE_CLOCK_GETTIME
#undef ESW_USE_CLOCK_GETTIME
#endif

#ifdef ESW_USE_CLOCK
#undef ESW_USE_CLOCK
#endif

#ifdef ESW_USE_CHRONO
#undef ESW_USE_CHRONO
#endif

#endif // TIMING_HEADER
