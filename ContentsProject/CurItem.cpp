#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"

#include "CurItem.h"

ACurItem::ACurItem()
{

}

ACurItem::~ACurItem()
{
}


void ACurItem::SetSprite(std::string _SprtieName, int _SpriteIndex, float _Scale)
{
	CurItemSpriteRenderer->SetSprite(_SprtieName, _SpriteIndex);
	CurItemSpriteRenderer->SetSpriteScale(_Scale, _SpriteIndex);

}
void ACurItem::BeginPlay()
{
	CurItemSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

}

void ACurItem::Tick(float _DeltaTime)
{
	CurItemSpriteRenderer->SetOrder(GetActorLocation().Y + 91);

}
