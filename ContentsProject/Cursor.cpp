#include "PreCompile.h"

#include "Cursor.h"
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
		CollisionComponent->SetComponentScale(FVector2D{ 24,30 });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::CURSOR);
		CollisionComponent->SetCollisionType(ECollisionType::Rect);
		CollisionComponent->SetCameraEffect(false);

		DebugOn();
	}
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
}