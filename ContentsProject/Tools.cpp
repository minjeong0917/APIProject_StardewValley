#include "PreCompile.h"
#include "Tools.h"

ATools::ATools()
{
}

ATools::~ATools()
{
}

void ATools::Tick(float _DeltaTime)
{
	AddActorLocation(FVector2D::RIGHT * _DeltaTime * 300.0f);
}