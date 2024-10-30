#include "PreCompile.h"
#include "FarmMap.h"
#include <EngineCore/EngineAPICore.h>

AFarmMap::AFarmMap()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	SetActorScale(WindowSize*2);
	SetActorLocation(WindowSize);
	SetSprite("Farm.png");

}

AFarmMap::~AFarmMap()
{
}

