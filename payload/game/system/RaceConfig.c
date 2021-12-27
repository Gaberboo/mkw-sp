#include "RaceConfig.h"

#include "GhostFile.h"
#include "InputManager.h"

#include <string.h>

void RaceConfigScenario_initGhostController(RaceConfigScenario *this, u32 playerId) {
    u32 ghostId = this->players[0].type == PLAYER_TYPE_GHOST ? playerId : playerId - 1;
    const u8 *rawGhostFile = (*this->ghostBuffer)[ghostId];
    const RawGhostHeader *rawGhostHeader = (RawGhostHeader *)rawGhostFile;
    bool driftIsAuto = rawGhostHeader->driftIsAuto;
    InputManager_setGhostPad(s_inputManager, ghostId, rawGhostFile + 0x88, driftIsAuto);
    this->players[playerId].characterId = rawGhostHeader->characterId;
    this->players[playerId].vehicleId = rawGhostHeader->vehicleId;
    this->players[playerId].controllerId = rawGhostHeader->controllerId;
}

static RaceConfig *my_RaceConfig_createInstance(void) {
    s_raceConfig = new(sizeof(RaceConfig));
    RaceConfig_ct(s_raceConfig);

    s_raceConfig->raceScenario.ghostBuffer = s_raceConfig->ghostBuffers + 0;
    s_raceConfig->menuScenario.ghostBuffer = s_raceConfig->ghostBuffers + 1;

    memset(s_raceConfig->ghostBuffers, 0, sizeof(s_raceConfig->ghostBuffers));

    return s_raceConfig;
}

PATCH_B(RaceConfig_createInstance, my_RaceConfig_createInstance);
