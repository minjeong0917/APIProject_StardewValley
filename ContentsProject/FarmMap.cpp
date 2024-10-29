#include "PreCompile.h"
#include "FarmMap.h"
#include <EngineCore/EngineAPICore.h>

AFarmMap::AFarmMap()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	SetActorScale(WindowSize.Half());
	SetActorLocation(WindowSize.Half());
}

AFarmMap::~AFarmMap()
{
}

