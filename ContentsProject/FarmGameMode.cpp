#include "PreCompile.h"
#include "FarmGameMode.h"

#include <EngineCore/Level.h>

#include "FarmMap.h"
#include "Player.h"

AFarmGameMode::AFarmGameMode()
{
}

AFarmGameMode::~AFarmGameMode()
{
}

void AFarmGameMode::BeginPlay()
{
	AFarmMap* Farm = GetWorld()->SpawnActor<AFarmMap>();
}
