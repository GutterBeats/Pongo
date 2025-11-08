//
// Created by Anthony Lesch on 11/6/25.
//

#pragma once

#include <string_view>

namespace Assets
{
    namespace Textures
    {
        static constexpr std::string_view BACKGROUND = "assets/textures/Background.png";
        static constexpr std::string_view BALL = "assets/textures/Ball.png";
        static constexpr std::string_view LEFT_PADDLE = "assets/textures/LeftPaddle.png";
        static constexpr std::string_view RIGHT_PADDLE = "assets/textures/RightPaddle.png";
    }

    namespace Sfx
    {
        static constexpr std::string_view HIT = "assets/sfx/hit.wav";
    }
}
