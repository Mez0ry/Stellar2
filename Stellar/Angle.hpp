#ifndef __STELLAR_ANGLE_HPP__
#define __STELLAR_ANGLE_HPP__
#include <cstdint>
#include <math.h>

template <typename TAngle>
class Angle {
public:
  Angle() = default;
  Angle(TAngle angle) : m_Angle(angle) {}

  TAngle GetAngle() const { return m_Angle; }
  void SetAngle(TAngle angle) { m_Angle = angle; }

  bool operator==(const Angle &rhs) const {
    return (m_Angle == rhs.GetAngle());
  }

  bool operator!=(const Angle &rhs) const { return !(*this == rhs); }

  Angle operator+=(const TAngle value) {
    this->m_Angle += value;
    return (*this);
  }

  Angle operator-=(const TAngle value) {
    this->m_Angle -= value;
    return (*this);
  }

  Angle operator*=(const TAngle value) {
    this->m_Angle *= value;
    return (*this);
  }

  Angle operator*=(const Angle<TAngle> &angle) {
    (*this) *= angle;
    return (*this);
  }

  Angle operator/=(const TAngle value) {
    this->m_Angle /= value;
    return (*this);
  }

  inline Angle<TAngle> operator+(const TAngle value) {
    return Angle<TAngle>((*this) + value);
  }

  inline Angle<TAngle> operator-(const TAngle value) {
    return Angle((*this) - value);
  }

  inline Angle<TAngle> operator*(const TAngle value) {
    return (this->GetAngle() + value);
  }

  inline Angle<TAngle> operator*(const Angle<TAngle> &angle) {
    return (this->GetAngle() * angle.GetAngle());
  }

  inline Angle<TAngle> operator/(const TAngle value) {
    return (this->GetAngle() / value);
  }

  operator TAngle() const noexcept { return m_Angle; }

  static TAngle Degree2Rad(double angle){
    return (angle * ( M_PI / 180));
  }

  static TAngle Degree2Rad(const Angle<TAngle>& angle){
    return (angle.GetAngle() * ( M_PI / 180));
  }

  static TAngle Rad2Degree(double angle_rad){
    return (angle_rad * (180 / M_PI));
  }

  static TAngle Rad2Degree(const Angle<TAngle>& angle_rad){
    return (angle_rad.GetAngle() * (180 / M_PI));
  }

private:
  TAngle m_Angle;
};

using Anglef = Angle<float>;
using Angled = Angle<double>;
using Anglei = Angle<int>;

#endif //! __STELLAR_ANGLE_HPP__