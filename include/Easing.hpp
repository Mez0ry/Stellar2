#ifndef __STELLAR_EASING_HPP__
#define __STELLAR_EASING_HPP__
#include <math.h>

namespace Stellar{

    namespace Easing{
        double EaseInSine(double t);
        double EaseOutSine(double t);
        double EaseInOutSine(double t);
        double EaseInQuad(double t);
        double EaseOutQuad(double t);
        double EaseInOutQuad(double t);
        double EaseInCubic(double t);
        double EaseOutCubic(double t);
        double EaseInOutCubic(double t);
        double EaseInQuart(double t);
        double EaseOutQuart(double t);
        double EaseInOutQuart(double t);
        double EaseInQuint(double t);
        double EaseOutQuint(double t);
        double EaseInOutQuint(double t);
        double EaseInExpo(double t);
        double EaseOutExpo(double t);
        double EaseInOutExpo(double t);
        double EaseInCirc(double t);
        double EaseOutCirc(double t);
        double EaseInOutCirc(double t);
        double EaseInBack(double t);
        double EaseOutBack(double t);
        double EaseInOutBack(double t);
        double EaseInElastic(double t);
        double EaseOutElastic(double t);
        double EaseInOutElastic(double t);
        double EaseInBounce(double t);
        double EaseOutBounce(double t);
        double EaseInOutBounce(double t);

    }//!Easing

}//!Stellar

#endif // __STELLAR_EASING_HPP__