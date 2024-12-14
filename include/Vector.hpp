#ifndef _VECTOR_HPP
#define _VECTOR_HPP

#include <algorithm>
#include <functional>
#include <iostream>
#include <math.h>
#include <type_traits>

#include "Logger.hpp"

template <typename T>
using enable_if_fundamental_t  = std::enable_if_t<std::is_fundamental_v<T>>;

/**
 * @param TValue type of vector components, int by default \n
 * @param TScalar type of scalar which used in operations such as multiplying vec by scalar, by default TScalar has type of TValue \n 
 * @warning if you using type (TValue/TScalar) that not fundamental it wouldn't enable instantiation
*/
template <typename TValue = int,typename TScalar = TValue,class = enable_if_fundamental_t<TValue>, class = enable_if_fundamental_t<TScalar> >
struct Vec2 {
  TValue x, y;

  Vec2() = default;
  Vec2(TValue pos_x, TValue pos_y) : x(pos_x), y(pos_y) {}
  Vec2(Vec2&& other) noexcept{
    swap(*this,other);
    other.clear();
  }

  Vec2(Vec2<TValue> &other) {
    *this = other;
  }
  
  Vec2(const Vec2<TValue> &other) {
    (*this).x = other.x;
    (*this).y = other.y;
  }

  ~Vec2() = default;

  friend void swap(Vec2<TValue> &lhs, Vec2<TValue> &rhs) {
    std::swap(lhs.x, rhs.x);
    std::swap(lhs.y, rhs.y);
  }

  /**
   * @brief used to get magnitude of the vector
   * @return magnitude
   */
  double Magnitude() const{
    return this->Length(); 
  }

  /**
   * @brief used to get length of the vector
   * @return length
   */
  double Length() const{
    return std::sqrt(DotProduct(*this,*this));
  }
  
  /**
   * @brief used to get distance
   * @return distance
   */
  static TValue Distance(const Vec2<TValue> &lhs, const Vec2<TValue> &rhs) {
    Vec2<TValue> res{std::abs(lhs.x - rhs.x), std::abs(lhs.y - rhs.y)};
    return res.Length();
  }

  /**
   * @brief Get the maximum number of 2 components
   * 
   * @return max component of type 'TValue'
  */
  TValue GetMaxComponent() const { return std::max(x, y); }

  /**
   * @brief Get the minimum number of 2 components
   * 
   * @return min component of type 'TValue'
  */
  TValue GetMinComponent() const { return std::min(x, y); }

  /**
   * @brief Get the angle of rotation
   * 
   * @param lhs vector that we trying to rotate
   * @param rhs target vector
   * @return angle in radians
   */
  static double GetRotationAngle(const Vec2<TValue> &lhs, const Vec2<TValue> &rhs) {
    Vec2<TValue> target_positive_perpendicular = (rhs - lhs).PositivePerpendicular();
    return ( atan2(target_positive_perpendicular.y, target_positive_perpendicular.x));
  }

  /**
   * @brief normalize vector
   * @return unit vector on success otherwise empty vector
   */
  Vec2<int> Normalize() const {
    double magnitude = this->Magnitude();
    if (magnitude == 0)
      return {0, 0};

    float inv_mag = 1.0f / magnitude;
    const Vec2<int> cpy = {static_cast<int>(x * inv_mag), static_cast<int>(y * inv_mag)};
    return cpy;
  }

  Vec2<TValue> PositivePerpendicular() const { return {-y, x}; }

  Vec2<TValue> NegativePerpendicular() const { return {y, -x}; }

  /**
   * @brief used to get dot product
   * @return dot product
   */
  static double DotProduct(const Vec2<TValue> &lhs, const Vec2<TValue> &rhs) {
    return (lhs.x * rhs.x + lhs.y * rhs.y);
  }

  static Vec2<TValue> Lerp(const Vec2<TValue> &lhs, const Vec2<TValue> &rhs, float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    Vec2<TValue> res;
    res.x = lhs.x + (rhs.x - lhs.x) * t;
    res.y = lhs.y + (rhs.y - lhs.y) * t;
    return res;
  }

  /** Comparison operators*/
  Vec2<TValue> operator-(const Vec2<TValue> &rhs) const {
    return {this->x - rhs.x, this->y - rhs.y};
  }

  Vec2<TValue> operator-(Vec2<TValue> &rhs) const {
    return {this->x - rhs.x, this->y - rhs.y};
  }

  Vec2<TValue> operator+(const Vec2<TValue> &rhs) const {
    return {this->x + rhs.x, this->y + rhs.y};
  }

  Vec2<TValue> &operator+=(const Vec2<TValue> &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }

  Vec2<TValue> &operator-=(const Vec2<TValue> &rhs) {
    this->x -= rhs.x;
    this->y -= this->y - rhs.y;
    return *this;
  }

  inline friend std::ostream &operator<<(std::ostream &out, const Vec2<TValue> &vec) {
    out << "Vector(" << vec.x << "," << vec.y << ")";
    return out;
  }

  bool operator==(const Vec2<TValue> &rhs) const {
    return (this->x == rhs.x && this->y == rhs.y);
  }

  bool operator!=(const Vec2<TValue> &rhs) const {
    return !(*this == rhs);
  }

  bool IsEmpty() const{
    return (x == 0 && y == 0);
  }
  
  /** Assignment operators*/
  Vec2<TValue> &operator=(const Vec2<TValue>& other) {
    if (this == &other) { // self assignment
      return (*this);
    }

    CopyAndSwap(*this,other);

    return (*this);
  }

  Vec2<TValue> operator+=(const TScalar scalar) {
    this->x += scalar;
    this->y += scalar;
    return *this;
  }

  Vec2<TValue> operator-=(const TScalar scalar) {
    this->x -= scalar;
    this->y -= scalar;
    return *this;
  }

  Vec2<TValue> operator*=(const TScalar scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
  }

  Vec2<TValue> operator/=(const TScalar scalar) {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
  }

  inline Vec2<TValue> operator+(const TScalar scalar) {
    Vec2<TValue> tmp = (*this);
    return tmp += scalar;
  }

  inline Vec2<TValue> operator-(const TScalar scalar) {
    Vec2<TValue> tmp = (*this);
    return tmp -= scalar;
  }

  inline Vec2<TValue> operator*(const TScalar scalar) {
    Vec2<TValue> tmp = (*this);
    return tmp *= scalar;
  }

  inline Vec2<TValue> operator*(const Vec2<TValue> &vec) {
    return {(*this).x * vec.x, (*this).y * vec.y};
  }

  inline Vec2<TValue> operator/(const TScalar scalar) {
    Vec2<TValue> tmp = (*this);
    return tmp /= scalar;
  }

  private:

  void clear(){
    this->x = 0;
    this->y = 0;
  }

  void CopyAndSwap(Vec2<TValue>& l, const Vec2<TValue>& other){
    Vec2<TValue> tmp(other);
    swap(l,tmp);
  }
};

template struct Vec2<int>;
template struct Vec2<float>;
template struct Vec2<double>;

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;
using Vec2d = Vec2<double>;

using Pointi = Vec2i;
using Pointf = Vec2f;
using Pointd = Vec2d;

template <typename TValue>
struct fmt::formatter<Vec2<TValue>> {
    constexpr auto parse(format_parse_context& ctx) {
      return ctx.end();
    }

    template <typename Context>
    auto format(const Vec2<TValue>& p, Context& ctx) {
      return format_to(ctx.out(), "Vector<{}>({}, {})", typeid(TValue).name(),p.x, p.y);
    }
};

/**
 * TODO test this with different types
 */
template <> struct std::hash<Vec2<>> {
  std::size_t operator()(const Vec2<> &k) const {
    using std::hash;
    using std::size_t;
    using std::string;

    // Compute individual hash values for first,
    // second and third and combine them using XOR
    // and bit shifting:

    return ((std::hash<int>()(k.x) ^ (std::hash<int>()(k.y) << 1)) >> 1);
  }
};

#endif //!_VECTOR_HPP

