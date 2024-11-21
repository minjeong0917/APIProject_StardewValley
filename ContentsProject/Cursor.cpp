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
	CursorSpriteRenderer->SetSprite("Cursor.png", 0);
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
	CollisionComponent->SetCollisionEnter(std::bind(&ACursor::CollisionEnter, this, std::placeholders::_1));
	CollisionComponent->SetCollisionEnd(std::bind(&ACursor::CollisionEnd, this, std::placeholders::_1));
}

ACursor::~ACursor()
{
}

void ACursor::CollisionEnter(AActor* _ColActor)
{
	IsEnter = true;

}

void ACursor::CollisionEnd(AActor* _ColActor)
{

	IsEnter = false;
}


void ACursor::BeginPlay()
{
	Super::BeginPlay();
}
void ACursor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	AActor* Result = CollisionComponent->CollisionOnce(ECollisionGroup::SLOT);
	if (nullptr != Result)
	{
		UEngineDebug::CoreOutPutString("Ãæµ¹ÇÔ");
	}
}


