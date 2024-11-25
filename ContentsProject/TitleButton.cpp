#include "PreCompile.h"
#include <EnginePlatform/EngineInput.h>

#include "TitleButton.h"

ATitleButton::ATitleButton()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetCameraEffect(false);
		SpriteRenderer->SetOrder(ERenderOrder::LOGO);
		SpriteRenderer->SetComponentScale({ 148.0f * 1.5f,116.0f * 1.5f });

	}
	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		//CollisionComponent->SetComponentLocation({ 0, 0 });
		CollisionComponent->SetComponentScale({ 148.0f * 1.5f,116.0f * 1.5f });

		CollisionComponent->SetCollisionGroup(ECollisionGroup::BUTTON);
		CollisionComponent->SetCollisionType(ECollisionType::Rect);
		CollisionComponent->SetCameraEffect(false);

		DebugOn();
	}
	CollisionComponent->SetCollisionStay(std::bind(&ATitleButton::CollisionStay, this, std::placeholders::_1));
	CollisionComponent->SetCollisionEnter(std::bind(&ATitleButton::CollisionEnter, this, std::placeholders::_1));
	CollisionComponent->SetCollisionEnd(std::bind(&ATitleButton::CollisionEnd, this, std::placeholders::_1));

}

ATitleButton::~ATitleButton()
{
}

void ATitleButton::BeginPlay()
{
	Super::BeginPlay();

}

void ATitleButton::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATitleButton::SetOrder(ERenderOrder _RenderOder)
{
	SpriteRenderer->SetOrder(_RenderOder);
}

void ATitleButton::SetSprite(std::string _SprtieName, int _SpriteIndex)
{
	SpriteRenderer->SetSprite(_SprtieName, _SpriteIndex);
}

void ATitleButton::SetScale(float _Scale)
{
	SpriteRenderer->SetSpriteScale(_Scale);
}

void ATitleButton::SetCameraEffect(bool _Effect)
{
	SpriteRenderer->SetCameraEffect(_Effect);
}


void ATitleButton::CollisionStay(AActor* _ColActor)
{
	IsCollisionStay = true;

	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		IsClick = true;
	}

}

void ATitleButton::CollisionEnter(AActor* _ColActor)
{
	IsCollisionEnter = true;
	IsCollisionEnd = false;

}

void ATitleButton::CollisionEnd(AActor* _ColActor)
{
	IsCollisionEnd = true;
	IsCollisionEnter = false;

}