#ifndef __STELLAR_COLOR_HPP__
#define __STELLAR_COLOR_HPP__
#include "SDL2/SDL_pixels.h"
#include <cstdint>
#include <algorithm>

struct Color {
  uint8_t r, g, b, a;
  
  Color() : r(0), g(0), b(0), a(0){};
  Color(SDL_Color color) : r(color.a), g(color.g), b(color.b), a(color.a) {}
  constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r{r},g{g},b{b},a{a} {}

  ~Color() = default;

  /**
   * @brief copy constructor and assignment operator
   */
  Color(const Color &other) { (*this) = other; }

  Color &operator=(const Color &other) {
    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
    this->a = other.a;
    return (*this);
  }

  /**
   * @todo Move semantics
   */
  Color(Color &&other) noexcept { (*this) = std::move(other); }

  Color &operator=(Color &&other) noexcept {
    if (this == &other) {
      return (*this);
    }

    this->r = other.r;
    this->g = other.g;
    this->b = other.b;
    this->a = other.a;

    Color::Clear(other);
    return (*this);
  }
  uint32_t GetAsU32(){
    return r | (g << 8) | (b << 16) | (a << 24);
  }
  /**
   * @todo default math operations
   */
  friend Color operator+(Color lhs, const Color &other) {
    lhs.r += other.r;
    lhs.g += other.g;
    lhs.b += other.b;
    lhs.a += other.a;
    return lhs;
  }

  friend Color operator-(Color lhs, const Color &other) {
    lhs.r -= other.r;
    lhs.g -= other.g;
    lhs.b -= other.b;
    lhs.a -= other.a;
    return lhs;
  }

  friend Color operator*(Color lhs, const Color &other) {
    lhs.r *= other.r;
    lhs.g *= other.g;
    lhs.b *= other.b;
    lhs.a *= other.a;
    return lhs;
  }

  friend Color operator/(Color lhs, const Color &other) {
    lhs.r /= other.r;
    lhs.g /= other.g;
    lhs.b /= other.b;
    lhs.a /= other.a;
    return lhs;
  }
  
  Color &operator+=(Color &other) {
    (*this) = (*this) + other;
    return (*this);
  }

  Color &operator-=(Color &other) {
    (*this) = (*this) - other;
    return (*this);
  }

  Color &operator*=(Color &other) {

    (*this) = (*this) * other;
    return (*this);
  }

  Color &operator/=(Color &other) {
    (*this) = (*this) / other;
    return (*this);
  }

  /**
   * @todo default math operations on scalar
  */
   friend Color operator+(Color lhs, const uint8_t scalar) {
    lhs.r += scalar;
    lhs.g += scalar;
    lhs.b += scalar;
    lhs.a += scalar;
    return lhs;
  }

  friend Color operator-(Color lhs, const uint8_t scalar) {
    lhs.r -= scalar;
    lhs.g -= scalar;
    lhs.b -= scalar;
    lhs.a -= scalar;
    return lhs;
  }

  friend Color operator*(Color lhs, const uint8_t scalar) {
    lhs.r *= scalar;
    lhs.g *= scalar;
    lhs.b *= scalar;
    lhs.a *= scalar;
    return lhs;
  }

  friend Color operator/(Color lhs, const uint8_t scalar) {
    lhs.r /= scalar;
    lhs.g /= scalar;
    lhs.b /= scalar;
    lhs.a /= scalar;
    return lhs;
  }
  
  Color &operator+=(const uint8_t scalar) {
    (*this) = (*this) + scalar;
    return (*this);
  }

  Color &operator-=(const uint8_t scalar) {
    (*this) = (*this) - scalar;
    return (*this);
  }

  Color &operator*=(const uint8_t scalar) {

    (*this) = (*this) * scalar;
    return (*this);
  }

  Color &operator/=(const uint8_t scalar) {
    (*this) = (*this) / scalar;
    return (*this);
  }
  
  /**
   * @todo color blending
  */
  static Color AlphaBlending(const Color& fg, const Color& bg){
    Color res;
    res.a = 1 - (1 - fg.a) * (1 - bg.a);
    if (res.a < 1.0e-6) return res; // Fully transparent -- R,G,B not important

    res.r = fg.a * fg.a/ res.a + bg.r * bg.a * (1 - fg.a) / res.a;
    res.g = fg.g  * fg.a / res.a + bg.g * bg.a * (1 - fg.a) / res.a;
    res.b = fg.b * fg.a / res.a + bg.b * bg.a * (1 - fg.a) / res.a;
    return res;
  }

  bool operator==(const Color& other) const{
    return (this->r == other.r && this->g == other.g && this->b == other.b && this->a == other.a);
  }

  bool operator!=(const Color& other) const{
    return !(*this == other);
  }

  /**
   * @todo adaptive blending
  */

  operator SDL_Color() const { return SDL_Color{r, g, b, a}; }

  static void Clamp(uint8_t& component, uint8_t low, uint8_t high) {
    component = std::clamp(component,low,high);
  }

  static void Clear(Color &color) {
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 0;
  }

private:
};

constexpr Color color_red_t    = Color(255,0,0,255);
constexpr Color color_blue_t   = Color(0,0,255,255);
constexpr Color color_aqua_t   = Color(0,255,255,255);
constexpr Color color_yellow_t = Color(250,250,55,255);
constexpr Color color_purple_t = Color(160,32,240,255);
constexpr Color color_white_t  = Color(255,255,255,255);
constexpr Color color_black_t  = Color(0,0,0,255);
constexpr Color color_green_t  = Color(0,255,0,255);
constexpr Color color_orange_t = Color(255,165,0,255);

#endif //!__STELLAR_COLOR_HPP__