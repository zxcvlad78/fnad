#include <meatengine/MainLoop.hpp>
#include "FnadGame.hpp"

bool RenderSystems::enabled = true;
float speed_scale = 1.0f;

int main() {
    meatengine::MainLoop engine("Fnad");
    
    engine.run(std::make_unique<FnadGameState>());
    
    return 0;
}
