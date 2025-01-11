#include "Easing.hpp"

namespace Stellar {
namespace Easing {
double EaseInSine(double t) { return 1 - std::cos((t * M_PI) / 2); }

double EaseOutSine(double t) { return std::sin((t * M_PI) / 2); }

double EaseInOutSine(double t) { return -(std::cos(M_PI * t) - 1) / 2; }

double EaseInQuad(double t) { return (t * t); }

double EaseOutQuad(double t) { return 1 - (1 - t) * (1 - t); }

double EaseInOutQuad(double t) {
  return t < 0.5 ? 2 * t * t : 1 - std::pow(-2 * t + 2, 2) / 2;
}

double EaseInCubic(double t) { return (t * t * t); }

double EaseOutCubic(double t) { return 1 - std::pow(1 - t, 3); }

double EaseInOutCubic(double t) {
  return t < 0.5 ? 4 * t * t * t : 1 - std::pow(-2 * t + 2, 3) / 2;
}

double EaseInQuart(double t) { return t * t * t * t; }

double EaseOutQuart(double t) { return 1 - std::pow(1 - t, 4); }

double EaseInOutQuart(double t) {
  return (t < 0.5) ? 8 * t * t * t * t : 1 - std::pow(-2 * t + 2, 4) / 2;
}

double EaseInQuint(double t) { return t * t * t * t * t; }

double EaseOutQuint(double t) { return 1 - std::pow(1 - t, 5); }

double EaseInOutQuint(double t) {
  return (t < 0.5) ? 16 * t * t * t * t * t : 1 - std::pow(-2 * t + 2, 5) / 2;
}

double EaseInExpo(double t) { return (t == 0) ? 0 : std::pow(2, 10 * t - 10); }

double EaseOutExpo(double t) { return (t == 1) ? 1 : 1 - std::pow(2, -10 * t); }

double EaseInOutExpo(double t) {
  if (t < 0.5) {
    return (std::pow(2, 16 * t) - 1) / 510;
  }

  return 1 - 0.5 * std::pow(2, -16 * (t - 0.5));
}

double EaseInCirc(double t) { return 1 - std::sqrt(1 - std::pow(t, 2)); }

double EaseOutCirc(double t) { return std::sqrt(1 - std::pow(t - 1, 2)); }

double EaseInOutCirc(double t) {
  return (t < 0.5) ? (1 - std::sqrt(1 - std::pow(2 * t, 2))) / 2
                   : (std::sqrt(1 - std::pow(-2 * t + 2, 2)) + 1) / 2;
}

double EaseInBack(double t) { return t * t * (2.70158 * t - 1.70158); }

double EaseOutBack(double t) { return 1 + (t - 1) * t * (2.70158 * t + 1.70158); }

double EaseInOutBack(double t) {
  if (t < 0.5) {
    return t * t * (7 * t - 2.5) * 2;
  }

  return 1 + (t - 1) * t * 2 * (7 * t + 2.5);
}

double EaseInElastic(double t) {
  double t_pow_2 = t * t;
  return t_pow_2 * t_pow_2 * std::sin(t * M_PI * 4.5);
}

double EaseOutElastic(double t) {
  double t_pow_2 = (t - 1) * (t - 1);
  return 1 - t_pow_2 * t_pow_2 * std::cos(t * M_PI * 4.5);
}

double EaseInOutElastic(double t) {
  double t_pow_2;

  if (t < 0.45) {
    t_pow_2 = t * t;
    return 8 * t_pow_2 * t_pow_2 * std::sin(t * M_PI * 9);
  } else if (t < 0.55) {
    return 0.5 + 0.75 * std::sin(t * M_PI * 4);
  } else {
    t_pow_2 = (t - 1) * (t - 1);
    return 1 - 8 * t_pow_2 * t_pow_2 * std::sin(t * M_PI * 9);
  }

  return t;
}

double EaseInBounce(double t) {
  return std::pow(2, 6 * (t - 1)) * std::abs(std::sin(t * M_PI * 3.5));
}

double EaseOutBounce(double t) {
  return 1 - std::pow(2, -6 * t) * std::abs(std::cos(t * M_PI * 3.5));
}

double EaseInOutBounce(double t) {
  if (t < 0.5) {
    return 8 * std::pow(2, 8 * (t - 1)) * std::abs(std::sin(t * M_PI * 7));
  } else {
    return 1 - 8 * std::pow(2, -8 * t) * std::abs(std::sin(t * M_PI * 7));
  }
}

} // !namespace Easing
}   // !namespace Stellar