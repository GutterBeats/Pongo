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
        static constexpr std::string_view EXIT = "assets/textures/Exit.png";
        static constexpr std::string_view EXIT_SELECTED = "assets/textures/ExitSelected.png";
        static constexpr std::string_view LEFT_PADDLE = "assets/textures/LeftPaddle.png";
        static constexpr std::string_view LOGO = "assets/textures/Logo.png";
        static constexpr std::string_view OPTIONS = "assets/textures/Options.png";
        static constexpr std::string_view OPTIONS_SELECTED = "assets/textures/OptionsSelected.png";
        static constexpr std::string_view PLAY = "assets/textures/Play.png";
        static constexpr std::string_view PLAY_SELECTED = "assets/textures/PlaySelected.png";
        static constexpr std::string_view RIGHT_PADDLE = "assets/textures/RightPaddle.png";
        static constexpr std::string_view TABLE = "assets/textures/Table.png";
    }

    namespace Sfx
    {
        static constexpr std::string_view HIT = "assets/sfx/hit.wav";
    }

    namespace Audio
    {
        static constexpr std::string_view DANGEROUS_CIRCUITS = "assets/audio/DangerousCircuits.wav";
    }

    namespace Fonts
    {
        static constexpr std::string_view MAPLE_MONO = "assets/fonts/MapleMono.ttf";
    }
}
