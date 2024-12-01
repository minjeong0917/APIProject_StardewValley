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

void ASelectedItem::BeginPlay()
{
	Super::BeginPlay();
	//Text = GetWorld()->SpawnActor<AGold>();
}

void ASelectedItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void ASelectedItem::SetPrice(std::string _ItemName)
{
    if (_ItemName == "ParsnipSeed")
    {
        ItemPrice = 20;
    }
    else if (_ItemName == "BeanStarter")
    {
        ItemPrice = 60;
    }
    else if (_ItemName == "CauliflowerSeed")
    {
        ItemPrice = 80;
    }
    else if (_ItemName == "PotatoSeed")
    {
        ItemPrice = 50;
    }
    else if (_ItemName == "KaleSeed")
    {
        ItemPrice = 70;

    }
    else if (_ItemName == "GarlicSeed")
    {
        ItemPrice = 40;

    }
    else if (_ItemName == "RhubarbSeed")
    {
        ItemPrice = 100;
    }
    else if (_ItemName == "parsnip")
    {
        ItemPrice = 35;
    }
    else if (_ItemName == "GreenBean")
    {
        ItemPrice = 40;
    }
    else if (_ItemName == "Cauliflower")
    {
        ItemPrice = 175;
    }
    else if (_ItemName == "Potato")
    {
        ItemPrice = 80;
    }
    else if (_ItemName == "Kale")
    {
        ItemPrice = 110;
    }
    else if (_ItemName == "Rhubarb")
    {
        ItemPrice = 220;
    }
    else if (_ItemName == "Garlic")
    {
        ItemPrice = 60;
    }
    else if (_ItemName == "Wood")
    {
        ItemPrice = 60;
    }
}
