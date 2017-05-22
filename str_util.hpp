/*
 * std_patch.hpp
 *
 *  Created on: Apr 18, 2017
 *      Author: lubuntu
 */

#ifndef STR_UTIL_HPP_
#define STR_UTIL_HPP_

#include <string>
#include <sstream>

// patch library for g++
namespace str_util
{
    // https://stackoverflow.com/a/20861692
    template<typename T> std::string to_string(const T& obj)
    {
        std::ostringstream os;
        os << obj;
        return os.str();
    }

    // https://stackoverflow.com/questions/14409466
    uint32_t adler32(const void* buf, int len)
    {
        const uint8_t* p = (const uint8_t*)buf;

        uint32_t s1 = 1;
        uint32_t s2 = 0;

        for(int i = 0; i < len; ++i)
        {
            s1 = (s1 + p[i]) % 65521;
            s2 = (s2 + s1) % 65521;
        }

        return (s2 << 16) | s1;
    }

    std::string adler32_str(const std::string& str)
    {
        return to_string(adler32(str.c_str(), str.length()));
    }
}

#endif /* STR_UTIL_HPP_ */
