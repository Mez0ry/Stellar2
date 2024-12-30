#ifndef _STELLAR_LERP_HPP__
#define _STELLAR_LERP_HPP__
#include <algorithm>
class Color;
namespace Stellar{

    float LerpUnClamped(float a, float b, float t);
    float Lerp(float a, float b, float t);
    Color Lerp(Color start, Color target, float t);

}//!Stellar

#endif // _STELLAR_LERP_HPP__