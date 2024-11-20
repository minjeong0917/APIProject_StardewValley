#include "PreCompile.h"

#include "Cursor.h"
#include <EngineCore/EngineCoreDebug.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

ACursor::ACursor()
{
	CursorSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	CursorSpriteRenderer->SetCameraEffect(false);
	CursorSpriteRenderer->SetOrder(ERenderOrder::CURSOR);
	CursorSpriteRenderer->SetSprite("UI", 1);
	CursorSpriteRenderer->SetComponentScale({ 24,30 });

	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentScale(FVector2D{ 5,5 });
		CollisionComponent->SetComponentLocation({ -8,-12 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::CURSOR);
		CollisionComponent->SetCollisionType(ECollisionType::Rect);
		CollisionComponent->SetCameraEffect(false);

		DebugOn();
	}

	GetWorld()->CollisionGroupLink(ECollisionGroup::SLOT, ECollisionGroup::CURSOR);

	CollisionComponent->SetCollisionEnter(std::bind(&ACursor::CollisionEnter, this, std::placeholders::_1));
	CollisionComponent->SetCollisionStay(std::bind(&ACursor::CollisionStay, this, std::placeholders::_1));

}

ACursor::~ACursor()
{
}

void ACursor::BeginPlay()
{
	Super::BeginPlay();
}
void ACursor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


	//bool IsColision = CollisionComponent->Collision(static_cast<int>(ECollisionGroup::SLOT));
	AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::SLOT);
	if (nullptr != Result)
	{
		UEngineDebug::CoreOutPutString("Ãæµ¹ÇÔ");

	}
}


void ACursor::CollisionEnter(AActor* _ColActor)
{
	int a = 0;
}
void ACursor::CollisionStay(AActor* _ColActor)
{
	int a = 0;
}
