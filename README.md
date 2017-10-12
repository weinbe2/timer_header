# timer_header
A single header file that handles timing in both C and C++.

Timing routines, ESW 2017.

Just #include the file "timer.h", link against the library 'rt'
(that is, add -lrt to your compile string), and go for it!

The header plays nicely with both C and C++, at a nightmarish
cost to simplicity in timer.h. There are two core functions:

## time_sec_t begin_timing();
Returns a "time_sec_t", which is a different typedef depending on
what version of C/C++ you're using. In a rough sense, "time_sec_t"
is some amount of time (not necessarily seconds) relative to 
some (implementation-dependent) absolute starting time. This is
a nice way of saying don't waste your time trying to use the 
"time_sec_t" on its own, it only makes sense after a call to...

## double end_timing(time_sec_t\* begin_time); ---
Returns the duration in seconds between when the function is called
and some "time_sec_t" returned by "begin_timing()". "begin_time" is
passed as a pointer to (1) avoid the overhead of a copy constructor
in C++ since (2) C doesn't support pass by reference.

These routines have been tested on a laptop with Ubuntu 14.04.5 LTS
using various compilers and versions of the standard:

## gcc version 4.8.4 

gcc timer_test_c.c -lrt -o timer_test_c
gcc -std=c99 timer_test_c.c -lrt -o timer_test_c # C99
gcc -std=gnu99 timer_test_c.c -lrt -o timer_test_c # C99 w/ GNU extensions
gcc -std=c11 timer_test_c.c -lrt -o timer_test_c # C11
gcc -std=gnu11 timer_test_c.c -lrt -o timer_test_c # C11 w/ GNU extensions

## gcc version 5.4.1 

gcc-5 timer_test_c.c -lrt -o timer_test_c
gcc-5 -std=c99 timer_test_c.c -lrt -o timer_test_c # C99
gcc-5 -std=gnu99 timer_test_c.c -lrt -o timer_test_c # C99 w/ GNU extensions
gcc-5 -std=c11 timer_test_c.c -lrt -o timer_test_c # C11
gcc-5 -std=gnu11 timer_test_c.c -lrt -o timer_test_c # C11 w/ GNU extensions

## g++ version 4.8.4 

g++ timer_test.cpp -lrt -o timer_test
g++ -std=c++11 timer_test.cpp -lrt -o timer_test # C++11
g++ -std=c++1y timer_test.cpp -lrt -o timer_test # C++14

## g++ version 5.4.1

g++-5 timer_test.cpp -lrt -o timer_test
g++-5 -std=c++11 timer_test.cpp -lrt -o timer_test # C++11
g++-5 -std=c++14 timer_test.cpp -lrt -o timer_test # C++14
g++-5 -std=c++17 timer_test.cpp -lrt -o timer_test # C++17

I'm definitely interested in feedback on other systems and compilers,
so please let me know!

Happy timing!

