/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2008 Tord Romstad (Glaurung author)
  Copyright (C) 2008-2014 Marco Costalba, Joona Kiiski, Tord Romstad

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include <inttypes.h>

#ifndef _WIN32 // Linux - Unix

#  include <sys/time.h>

inline int64_t system_time_to_msec() {
  timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec * 1000LL + t.tv_usec / 1000;
}

#  include <pthread.h>
typedef pthread_mutex_t Lock;
typedef pthread_cond_t WaitCondition;
typedef pthread_t NativeHandle;
typedef void*(*pt_start_fn)(void*);

#  define lock_init(x) pthread_mutex_init(&(x), NULL)
#  define lock_grab(x) pthread_mutex_lock(&(x))
#  define lock_release(x) pthread_mutex_unlock(&(x))
#  define lock_destroy(x) pthread_mutex_destroy(&(x))
#  define cond_destroy(x) pthread_cond_destroy(&(x))
#  define cond_init(x) pthread_cond_init(&(x), NULL)
#  define cond_signal(x) pthread_cond_signal(&(x))
#  define cond_wait(x,y) pthread_cond_wait(&(x),&(y))
#  define cond_timedwait(x,y,z) pthread_cond_timedwait(&(x),&(y),z)
#  define thread_create(x,f,t) pthread_create(&(x),NULL,(pt_start_fn)f,t)
#  define thread_join(x) pthread_join(x, NULL)

#else // Windows and MinGW
#endif

#endif // #ifndef PLATFORM_H_INCLUDED
