#include "PreCompile.h"
#include "Tools.h"

ATools::ATools()
{
	SetActorScale({ 50, 50 });
}

ATools::~ATools()
{
}

void ATools::Tick(float _DeltaTime)
{
	AddActorLocation(FVector2D::RIGHT * _DeltaTime * 300.0f);
}