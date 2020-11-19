/*-------------------------------------------------------------------------
    Copyright diode 2020.
    Use, modification and distribution are subject to the
    Boost Software License, Version 1.0.  (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*///-----------------------------------------------------------------------

#include <iostream>
#include <icc/icc.hpp>

int main()
{
    using Type = int;
    
    Type max = std::numeric_limits<Type>::max();
    Type min = std::numeric_limits<Type>::min();
    
    Type a = max/3;
    Type b = -4;
    
    auto res = icc::mul(a, b);
    
    std::cout << a*b << std::endl;
    
    switch(res)
    {
        case icc::success:
            std::cout << "success" << std::endl;
            break;
            
        case icc::overflow:
            std::cout << "overflow" << std::endl;
            break;
            
        case icc::underflow:
            std::cout << "underflow" << std::endl;
            break;
    }
    
    return 0;
}
