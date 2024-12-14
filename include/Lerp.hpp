#ifndef _STELLAR_LERP_HPP__
#define _STELLAR_LERP_HPP__
#include <algorithm>

namespace Stellar{

    float LerpUnClamped(float a, float b, float t);
    float Lerp(float a, float b, float t);

}//!Stellar

#endif // _STELLAR_LERP_HPP__