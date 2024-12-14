#ifndef __STELLAR_TIMER_HPP__
#define __STELLAR_TIMER_HPP__
#include <chrono>
#include <iostream>
#include <cstdint>
#include "SDL2/SDL.h"

class Timer{
  public:
      Timer();
      ~Timer() = default;

      void Start();
      void Stop();
      void Pause();
      void UnPause();

      Uint64 GetTicks();

      //Checks the status of the timer
      bool isStarted();
      bool isPaused();

  private:
      //The clock time when the timer started
      Uint64 m_StartTicks;

      //The ticks stored when the timer was paused
      Uint64 m_PausedTicks;

      //The timer status
      bool m_IsPaused;
      bool m_IsStarted;
};

#endif //!__STELLAR_TIMER_HPP__