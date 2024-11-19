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
	CurItemSpriteRenderer->SetOrder(ERenderOrder::SLOT);

}

void ACurItem::Tick(float _DeltaTime)
{

}

bool ACurItem::ItemTypeCheck(EItemType _ItemType)
{
	if (_ItemType == EItemType::DUPivot)
	{
		return false;
	}
	else if (_ItemType > EItemType::DUPivot)
	{
		// 한개만
		return false;

	}
	else if (_ItemType < EItemType::DUPivot)
	{
		// 여러개 
		return true;

	}
	return false;

}

EItemType ACurItem::SetItemType(std::string _ItemName)
{
	if ("Wood" == _ItemName)
	{
		ItemType = EItemType::Wood;
		return ItemType;
	}
	else if ("Seeds" == _ItemName)
	{
		ItemType = EItemType::Crop;
		return ItemType;

	}
	else if ("parsnip" == _ItemName)
	{
		ItemType = EItemType::Crop;
		return ItemType;

	}
	else if ("Hoe" == _ItemName)
	{
		ItemType = EItemType::Tools;
		return ItemType;

	}
	return ItemType;

}