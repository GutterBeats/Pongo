//
// Created by Anthony Lesch on 11/7/25.
//

#pragma once

namespace Utils
{
    template <typename T>
    static T Clamp(T value, T min, T max)
    {
        return value < min ? min
             : value > max ? max : value;
    }
}
