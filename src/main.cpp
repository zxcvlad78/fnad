#include <meatengine/MainLoop.hpp>
#include "FnadGame.hpp"

bool RenderSystems::enabled = true;
float speed_scale = 1.0f;

int main() {
    meatengine::MainLoop loop("Fnad");
    
    loop.run(std::make_unique<FnadGame>());
    
    return 0;
}
