#include "Timer.hpp"

Timer::Timer() {
  m_StartTicks = 0;
  m_PausedTicks = 0;

  m_IsPaused = false;
  m_IsStarted = false;
}

void Timer::Start() {
  m_IsStarted = true;

  // Unpause the timer
  m_IsPaused = false;

  // Get the current clock time
  m_StartTicks = SDL_GetTicks();
  m_PausedTicks = 0;
}

void Timer::Stop() {
  // Stop the timer
  m_IsStarted = false;

  // Unpause the timer
  m_IsPaused = false;

  // Clear tick variables
  m_StartTicks = 0;
  m_PausedTicks = 0;
}

void Timer::Pause() {
  if (m_IsStarted && !m_IsPaused) {
    // Pause the timer
    m_IsPaused = true;

    // Calculate the paused ticks
    m_PausedTicks = SDL_GetTicks() - m_StartTicks;
    m_StartTicks = 0;
  }
}
void Timer::UnPause() {
  if (m_IsStarted && m_IsPaused) {
    // Unpause the timer
    m_IsPaused = false;

    // Reset the starting ticks
    m_StartTicks = SDL_GetTicks() - m_PausedTicks;

    // Reset the paused ticks
    m_PausedTicks = 0;
  }
}

Uint32 Timer::GetTicks() {
  Uint32 time = 0;

  if (m_IsStarted) {
    if (m_IsPaused) {
      time = m_PausedTicks;
    } else {
      time = SDL_GetTicks() - m_StartTicks;
    }
  }

  return time;
}

bool Timer::isStarted() {return m_IsStarted;}

bool Timer::isPaused() {return m_IsPaused;}