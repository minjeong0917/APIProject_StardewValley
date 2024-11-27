#include "PreCompile.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"

#include "CurItem.h"

ACurItem::ACurItem()
{
	CurItemSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
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


}

void ACurItem::Tick(float _DeltaTime)
{
	CurItemSpriteRenderer->SetOrder(GetActorLocation().Y + 91);

}
void ACurItem::Copy(ACurItem* _CurItem)
{
	if (nullptr != _CurItem->CurItemSpriteRenderer->GetSprite())
	{
		SetSprite(_CurItem->CurItemSpriteRenderer->GetCurSpriteName(), _CurItem->CurItemSpriteRenderer->GetCurIndex(), 3.0f);
	}
}