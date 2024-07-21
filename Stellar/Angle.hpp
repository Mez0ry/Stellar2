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

  Angle operator*=(const Angle &angle) {
    (*this) *= angle;
    return (*this);
  }

  Angle operator/=(const _Ty value) {
    this->m_Angle /= value;
    return (*this);
  }

  inline Angle operator+(const _Ty value) {
    return Angle((*this) + value);
  }

  inline Angle operator-(const _Ty value) {
    return Angle((*this) - value);
  }

  inline Angle operator*(const _Ty value) {
    return (this->GetAngle() + value);
  }

  inline Angle operator*(const Angle &angle) {
    return (this->GetAngle() * angle.GetAngle());
  }

  inline Angle operator/(const _Ty value) {
    return (this->GetAngle() / value);
  }

  operator _Ty() const noexcept { return m_Angle; }

private:
  _Ty m_Angle;
};

using Anglef = Angle<float>;
using Angled = Angle<float>;
using Anglei = Angle<int>;

#endif //! __STELLAR_ANGLE_HPP__