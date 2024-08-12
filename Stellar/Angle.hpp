#ifndef __STELLAR_ANGLE_HPP__
#define __STELLAR_ANGLE_HPP__
#include <cstdint>

template <typename _Ty>
class Angle {
public:
  Angle() = default;
  Angle(_Ty angle) : m_Angle(angle) {}

  _Ty GetAngle() const { return m_Angle; }
  void SetAngle(_Ty angle) { m_Angle = angle; }

  bool operator==(const Angle &rhs) const {
    return (m_Angle == rhs.GetAngle());
  }

  bool operator!=(const Angle &rhs) const { return !(*this == rhs); }

  Angle operator+=(const _Ty value) {
    this->m_Angle += value;
    return (*this);
  }

  Angle operator-=(const _Ty value) {
    this->m_Angle -= value;
    return (*this);
  }

  Angle operator*=(const _Ty value) {
    this->m_Angle *= value;
    return (*this);
  }

  Angle operator*=(const Angle<_Ty> &angle) {
    (*this) *= angle;
    return (*this);
  }

  Angle operator/=(const _Ty value) {
    this->m_Angle /= value;
    return (*this);
  }

  inline Angle<_Ty> operator+(const _Ty value) {
    return Angle<_Ty>((*this) + value);
  }

  inline Angle<_Ty> operator-(const _Ty value) {
    return Angle((*this) - value);
  }

  inline Angle<_Ty> operator*(const _Ty value) {
    return (this->GetAngle() + value);
  }

  inline Angle<_Ty> operator*(const Angle<_Ty> &angle) {
    return (this->GetAngle() * angle.GetAngle());
  }

  inline Angle<_Ty> operator/(const _Ty value) {
    return (this->GetAngle() / value);
  }

  operator _Ty() const noexcept { return m_Angle; }

  static _Ty Degree2Rad(double angle){
    return (angle * ( M_PI / 180));
  }

  static _Ty Degree2Rad(const Angle<_Ty>& angle){
    return (angle.GetAngle() * ( M_PI / 180));
  }

  static _Ty Rad2Degree(double angle_rad){
    return (angle_rad * (180 / M_PI));
  }

  static _Ty Rad2Degree(const Angle<_Ty>& angle_rad){
    return (angle_rad.GetAngle() * (180 / M_PI));
  }

private:
  _Ty m_Angle;
};

using Anglef = Angle<float>;
using Angled = Angle<double>;
using Anglei = Angle<int>;

#endif //! __STELLAR_ANGLE_HPP__