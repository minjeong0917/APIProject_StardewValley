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
}

ACursor::~ACursor()
{
}

void ACursor::BeginPlay()
{

}
void ACursor::Tick(float _DeltaTime)
{

}