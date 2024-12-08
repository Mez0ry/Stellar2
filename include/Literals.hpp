#ifndef __STELLAR_LITERALS_HPP__
#define __STELLAR_LITERALS_HPP__
#include <cstdint>

inline constexpr uint8_t operator "" _u8(unsigned long long arg ) noexcept
{
    return static_cast< uint8_t >( arg );
}

inline constexpr uint16_t operator "" _u16(unsigned long long arg ) noexcept
{
    return static_cast< uint16_t >( arg );
}

inline constexpr uint32_t operator "" _u32(unsigned long long arg ) noexcept
{
    return static_cast< uint32_t >( arg );
}

inline constexpr uint64_t operator "" _u64(unsigned long long arg ) noexcept
{
    return static_cast< uint64_t >( arg );
}

#endif //!__STELLAR_LITERALS_HPP__