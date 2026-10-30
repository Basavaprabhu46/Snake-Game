#pragma once

#include <string>
#include "Types.h"

namespace snake {

inline std::string highScoreLabel(const RenderData& data)
{
    return "HIGH " + std::to_string(data.highScore);
}

}
