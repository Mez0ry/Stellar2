#ifndef __STELLAR_TIMESTEP_HPP__
#define __STELLAR_TIMESTEP_HPP__
#include "Core.hpp"

class Timestep {
private:
  double m_T;
  double m_Dt;
  double m_Accumulator;
  
public:
  Timestep(double t, double dt) : m_T(t), m_Dt(dt), m_Accumulator(0.0) {}
  Timestep(double t, double numerator, double fps) : m_T(t) {
    m_Dt = numerator / fps;
    m_Accumulator = {0.0};
  }

  ~Timestep() {}

  double GetT() const { return m_T; }
  double GetDeltaTime() const { return m_Dt; }
  double GetAccamulator() const { return m_Accumulator; }

  void SetT(double t) { m_T = t; }
  void SetDeltaTime(double dt) { m_Dt = dt; }
  void SetAccumulator(double accumulator) { m_Accumulator = accumulator; }
  
  void SetNewTime(double new_time) { m_NewTime = new_time; }
  void SetCurrentTime(double current_time) { m_CurrentTime = current_time; }
  void SetFrameTime(double frame_time) { m_FrameTime = frame_time; }
  
  double GetNewTime() const {return m_NewTime;}
  double GetCurrentTime() const { return m_CurrentTime; }
  double GetFrameTime() const { return m_FrameTime; }

private:
  double m_NewTime,m_CurrentTime, m_FrameTime;
};
#endif //!__STELLAR_TIMESTEP_HPP__