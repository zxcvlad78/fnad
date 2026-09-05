#include <meatengine/MainLoop.hpp>
#include "FnadGame.hpp"

bool RenderSystems::enabled = true;

int main() {
    meatengine::MainLoop loop("Fnad");
    
    loop.run(std::make_unique<FnadGame>());
    
    return 0;
}
