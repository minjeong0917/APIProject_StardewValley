#include "PreCompile.h"

#include "SelectedItem.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

ASelectedItem::ASelectedItem()
{
	ItemSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ItemSpriteRenderer->SetCameraEffect(false);
	ItemSpriteRenderer->SetOrder(ERenderOrder::SelectedItem);
	
}


ASelectedItem::~ASelectedItem()
{
}

void ASelectedItem::SetSprite(std::string _SprtieName, int _SpriteIndex, float _Scale)
{
	ItemSpriteRenderer->SetSprite(_SprtieName, _SpriteIndex);
	ItemSpriteRenderer->SetSpriteScale(_Scale, _SpriteIndex);

}