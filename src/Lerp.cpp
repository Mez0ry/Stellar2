#include "Lerp.hpp"
#include "Color.hpp"
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

    Color Lerp(Color start, Color target, float t)
    {
        Color res;
        
        res.r = Stellar::Lerp(start.r,target.r,t);
        res.g = Stellar::Lerp(start.g,target.g,t);
        res.b = Stellar::Lerp(start.b,target.b,t);
        res.a = Stellar::Lerp(start.a,target.a,t);
        return res;
    }
}