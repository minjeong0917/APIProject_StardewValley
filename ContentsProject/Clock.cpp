#include "PreCompile.h"
#include "Clock.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"


AClock::AClock()
{
	ClockSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ClockSpriteRenderer->SetCameraEffect(false);
	ClockSpriteRenderer->SetOrder(ERenderOrder::UI);
	ClockSpriteRenderer->SetSprite("Clock.png", 0);
	ClockSpriteRenderer->SetSpriteScale(4.0f);
}

AClock::~AClock()
{
}


void AClock::BeginPlay()
{
	Super::BeginPlay();


}

void AClock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}
void AClock::SetActive(bool _Active)
{
	ClockSpriteRenderer->SetActive( _Active);

}