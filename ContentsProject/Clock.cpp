#include "PreCompile.h"
#include "Clock.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"
#include <EngineCore/Level.h>


AClock::AClock()
{

}


AClock::~AClock()
{
}


void AClock::BeginPlay()
{

	//FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	ClockSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ClockSpriteRenderer->SetOrder(ERenderOrder::UI);
	ClockSpriteRenderer->SetSprite("UI", 0);
	ClockSpriteRenderer->SetSpriteScale(3.0f);
}

void AClock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FVector2D CameraPos = GetWorld()->GetCameraPos();
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	float XSize = ClockSpriteRenderer->GetActorTransform().Scale.Half().X;
	float YSize = ClockSpriteRenderer->GetActorTransform().Scale.Half().Y;
	SetActorLocation({ CameraPos.X + Size.X - XSize -10, CameraPos.Y + YSize +10});

}
