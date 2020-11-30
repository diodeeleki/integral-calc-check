/*-------------------------------------------------------------------------
    Copyright diode 2020.
    Use, modification and distribution are subject to the
    Boost Software License, Version 1.0.  (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*///-----------------------------------------------------------------------
#pragma once

#include <limits>
#include <concepts>
#include <cassert>
#include <stdexcept>
#include <cmath>

namespace icc// integral calc check
{

using Result = unsigned short;
constexpr Result success = 0;
constexpr Result overflow = 1;
constexpr Result underflow = 2;

/*-------------------------------------------------

    ここから符号なし整数同士の計算におけるチェック

*///-----------------------------------------------

//  符号なし整数の和を行うときのオーバーフローチェック
template<std::unsigned_integral Type>
inline Result add(const Type l_arg, const Type r_arg)noexcept
{
    return r_arg <= std::numeric_limits<Type>::max() - l_arg ? success : overflow;
}

//  符号なし整数の差を行うときのアンダーフローチェック
template<std::unsigned_integral Type>
inline Result sub(const Type l_arg, const Type r_arg)noexcept
{
    return l_arg >= r_arg ? success : underflow;
}

//  符号なし整数の積を行うときのオーバーフローチェック
template<std::unsigned_integral Type>
inline Result mul(const Type l_arg, const Type r_arg)noexcept
{
    if(l_arg == Type(0)) return success;//    ゼロ除算対策(ゼロをかけても絶対にオーバーフローしない)
    return r_arg <= std::numeric_limits<Type>::max() / l_arg ? success : overflow;
}

/*-------------------------------------------------

    ここから符号あり整数同士の計算におけるチェック

*///-----------------------------------------------

//  符号あり整数の和を行うときのオーバーフローチェックとアンダーフローチェック
template<std::signed_integral Type>
inline Result add(const Type l_arg, const Type r_arg)noexcept
{   
    if((Type(0) <= l_arg)&&(Type(0) <= r_arg)) return std::numeric_limits<Type>::max() - l_arg >= r_arg ? success : overflow;
    if((Type(0) > l_arg)&&(Type(0) > r_arg)) return std::numeric_limits<Type>::min() - l_arg <= r_arg ? success : underflow;
    return success;
}

//  符号あり整数の差を行うときのオーバーフローチェックとアンダーフローチェック
template<std::signed_integral Type>
inline Result sub(const Type l_arg, const Type r_arg)noexcept
{   
    return add<Type>(l_arg, r_arg * Type(-1));
}

//  符号あり整数の積を行うときのオーバーフローチェックとアンダーフローチェック
template<std::signed_integral Type>
inline Result mul(const Type l_arg, const Type r_arg)noexcept
{   
    if(l_arg == Type(0)) return success;
    
    if(Type(0) <= l_arg && Type(0) <= r_arg || Type(0) >  l_arg && Type(0) >  r_arg)
        return std::numeric_limits<Type>::max() / std::abs(l_arg) >= std::abs(r_arg) ? success : overflow;
    
    return std::numeric_limits<Type>::min() / std::abs(l_arg) <= -std::abs(r_arg) ? success : underflow;   
}

}
