#include "turret_move_command.hpp"
#include "tap/control/command.hpp"
#include "tap/drivers.hpp"
#include <math.h>

#include "turret_subsystem.hpp"

#define POSDEADZONE 10
#define NEGDEADZONE -10

using namespace tap::communication::serial;

namespace control
{
namespace turret
{
    TurretMoveCommand::TurretMoveCommand(tap::Drivers *drivers, TurretSubsystem *sub)
        : drivers(drivers), 
          turret(sub)
    {
        addSubsystemRequirement(sub);
    }

void TurretMoveCommand::initialize() {}

void TurretMoveCommand::execute() 
{ 
    float x = drivers->remote.getMouseX();
    float y = drivers->remote.getMouseY();

    if (fabs(x) > POSDEADZONE || fabs(y) > POSDEADZONE) {
        turret->setDesiredOutput(x, y);
    } 

    else {
        turret->setDesiredOutput(0, 0);
    }
}

void TurretMoveCommand::end(bool) { turret->setDesiredOutput(0.0f, 0.0f); }

bool TurretMoveCommand::isFinished() const { return false; }
}  // namespace turret
}  // namespace control
