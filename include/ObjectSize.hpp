#ifndef __OBJECT_SIZE_HPP__
#define __OBJECT_SIZE_HPP__
#include <cstdint>
#include <fmt/format.h>
struct ObjectSize {
  ObjectSize() = default;
  ObjectSize(int width, int height) : w_(width), h_(height) {}
  ~ObjectSize() = default;

  void SetWidth(int width) {w_ = width;}
  void SetHeight(int height) {h_ = height;}
  int GetWidth() const { return w_; }
  int GetHeight() const { return h_; }
  int HalfWidth() const {return (w_ != 0) ? w_ >> 1 : 0;}
  int HalfHeight() const {return (h_ != 0) ? h_ >> 1 : 0; }

  ObjectSize &operator+=(const ObjectSize &rhs) {
    this->w_ += rhs.w_;
    this->h_ += rhs.h_;

    return *this; // return the result by reference
  }

  friend ObjectSize operator+(ObjectSize lhs, const ObjectSize &rhs) {
    return (lhs += rhs);
  }

  friend ObjectSize operator*(ObjectSize lhs, const ObjectSize &rhs) {
    return (lhs *= rhs);
  }

  ObjectSize& operator*=(const ObjectSize &rhs) {
    this->w_ *= rhs.w_;
    this->h_ *= rhs.h_;
    return (*this);
  }

  ObjectSize &operator-=(const ObjectSize &rhs) {
    this->w_ -= rhs.w_;
    this->h_ -= rhs.h_;

    return *this;
  }
  
  friend ObjectSize operator-(ObjectSize lhs, const ObjectSize &rhs) {
    return (lhs -= rhs);
  }

  ObjectSize& operator/=(const ObjectSize& rhs){
    this->w_ /= rhs.w_;
    this->h_ /= rhs.h_;
    return (*this);
  }

  friend ObjectSize operator/(ObjectSize lhs, const ObjectSize& rhs){
    return (lhs /= rhs);
  }

/**
 * @todo default math operations on scalar
*/
   friend ObjectSize operator+(ObjectSize lhs, const int scalar) {
    lhs.w_ += scalar;
    lhs.h_ += scalar;
    return lhs;
  }

  friend ObjectSize operator-(ObjectSize lhs, const int scalar) {
    lhs.w_ -= scalar;
    lhs.h_ -= scalar;
    return lhs;
  }

  friend ObjectSize operator*(ObjectSize lhs, const int scalar) {
    lhs.w_ *= scalar;
    lhs.h_ *= scalar;
    return lhs;
  }

  friend ObjectSize operator/(ObjectSize lhs, const int scalar) {
    lhs.w_ /= scalar;
    lhs.h_ /= scalar;
    return lhs;
  }
  
  ObjectSize &operator+=(const int scalar) {
    (*this) = (*this) + scalar;
    return (*this);
  }

  ObjectSize &operator-=(const int scalar) {
    (*this) = (*this) - scalar;
    return (*this);
  }

  ObjectSize &operator*=(const int scalar) {

    (*this) = (*this) * scalar;
    return (*this);
  }

  ObjectSize &operator/=(const int scalar) {
    (*this) = (*this) / scalar;
    return (*this);
  }

  bool operator==(const ObjectSize& other) const{
    return (w_ == other.w_ && h_ == other.h_);
  }

  bool operator!=(const ObjectSize& other) const {
    return !(*this == other);
  }
  
  bool operator<(const ObjectSize& other) const{
    return (this->h_ < other.h_ && this->w_ < other.w_);
  }

  bool operator<(const int scalar) const{
    return (this->h_ < scalar && this->w_ < scalar);
  }

  bool operator>(const ObjectSize& other) const{
    return (this->h_ > other.h_ && this->w_ > other.w_);
  }

  bool operator>(const int scalar) const{
    return (this->h_ > scalar && this->w_ > scalar);
  }
  
private:
  int w_, h_;
};
template <>
struct fmt::formatter<ObjectSize> {
    constexpr auto parse(format_parse_context& ctx) {
      return ctx.end();
    }

    template <typename Context>
    auto format(const ObjectSize& p, Context& ctx) const{
      return format_to(ctx.out(), "obj_size(w: {0},h: {1})", p.GetWidth(),p.GetHeight());
    }
};

#endif //! __OBJECT_SIZE_HPP__