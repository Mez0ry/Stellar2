#include "Lerp.hpp"

namespace Stellar
{
    float LerpUnClamped(float a, float b, float t)
    {
        return a * (1.0 - t) + (b * t);
    }

    float Lerp(float a, float b, float t)
    {
        auto t_clamped = std::clamp(0.0f,1.0f,t);
        return LerpUnClamped(a,b,t_clamped);
    }
    
}