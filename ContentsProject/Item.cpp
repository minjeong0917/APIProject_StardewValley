#include "PreCompile.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include <EngineBase/EngineRandom.h>
#include "Item.h"
#include "Player.h"
#include "PlayerUI.h"
#include "FarmGameMode.h"

AItem::AItem()
{
	ItemSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

}

AItem::~AItem()
{
}
void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	GainItem(_DeltaTime);

	if (false == IsIn)
	{
		Force(_DeltaTime);
	}
	DestroyItem();

}
void AItem::SetCameraEffect(bool _IsCamera)
{
	ItemSpriteRenderer->SetCameraEffect(_IsCamera);

}

void AItem::ItemSetSprite(std::string _SprtieName, int _SpriteIndex, float _Scale)
{
	ItemSpriteRenderer->SetSprite(_SprtieName, _SpriteIndex);
	ItemSpriteRenderer->SetSpriteScale(_Scale, _SpriteIndex);

}
void AItem::SetOrder(float _Order)
{
	ItemSpriteRenderer->SetOrder(_Order);

}

void AItem::GainItemInfo(std::string _ItemName, std::string _SpriteName, int _ItemIndex, float _ItemScale)
{
	GainItemIndex = _ItemIndex;
	GainItemSpriteName = _SpriteName;
	GainItemScale = _ItemScale;
	GainItemName = _ItemName;
}

void AItem::GainItem(float _DeltaTime)
{
	Time += _DeltaTime;
	if (Time >= 0.5f)
	{
		FVector2D ItemLocation = GetActorLocation();
		APlayer* Player = GetWorld()->GetPawn<APlayer>();

		float PlayerLocationX = Player->GetActorLocation().X;
		float PlayerLocationY = Player->GetActorLocation().Y - 20;

		FVector2D PlayerLocation = { PlayerLocationX , PlayerLocationY };
		FVector2D ItemToPlayerDir = PlayerLocation - ItemLocation;

		float ItemToPlayerDistanceX = std::abs(ItemToPlayerDir.X);
		float ItemToPlayerDistanceY = std::abs(ItemToPlayerDir.Y);
		if (ItemToPlayerDistanceX < 20.0f || ItemToPlayerDistanceY < 20.0f)
		{
			IsIn = true;
			ItemToPlayerDir.Normalize();
			AddActorLocation(ItemToPlayerDir * _DeltaTime * 500);

		}

	}
}

void AItem::DestroyItem()
{
	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	FVector2D PlayerLocation = Player->GetActorLocation();
	FVector2D ItemLocation = GetActorLocation();
	FVector2D ItemToPlayerDir = PlayerLocation - ItemLocation;

	float ItemToPlayerDistanceX = std::abs(ItemToPlayerDir.X);
	float ItemToPlayerDistanceY = std::abs(ItemToPlayerDir.Y);

	if (ItemToPlayerDistanceX < 1.f || ItemToPlayerDistanceY < 1.f)
	{
		Player->AddItem(this);
	}
	
}


bool AItem::ItemTypeCheck(EItemType _ItemType)
{
	if (_ItemType == EItemType::DUPivot)
	{
		return false;
	}
	else if(_ItemType > EItemType::DUPivot)
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

EItemType AItem::SetItemType(std::string _ItemName)
{
	if ("Wood" == _ItemName)
	{
		Item = EItemType::Wood;
		return Item;
	}
	else if ("ParsnipSeed" == _ItemName||"BeanStarter" == _ItemName || "CauliflowerSeed" == _ItemName || "PotatoSeed" == _ItemName || "KaleSeed" == _ItemName || "RhubarbSeed" == _ItemName || "GarlicSeed" == _ItemName)
	{
		Item = EItemType::Seed;
		return Item;
	}
	else if ("parsnip" == _ItemName || "GreenBean" == _ItemName || "Cauliflower" == _ItemName || "Potato" == _ItemName || "Kale" == _ItemName || "Rhubarb" == _ItemName || "Garlic" == _ItemName)
	{
		Item = EItemType::Crop;
		return Item;

	}
	else if ("Hoe" == _ItemName || "Axe" == _ItemName || "WateringCan" == _ItemName)
	{
		Item = EItemType::Tools;
		return Item;

	}

	return Item;

}

void AItem::SetForce()
{
	UEngineRandom Random;
	FVector2D RandomDir = { Random.RandomInt(-1, 1),  Random.RandomInt(-1, 1) };
	ForceDir = /*(_TileLocation - _PlayerLocation) +*/ RandomDir;
	ForceDir.Normalize();

	Speed = Random.Randomfloat(10.0f, 80.0f);
	CurSpeed = Speed;
	CurUpForce = UpForce;

	UpForceDir = FVector2D::UP;
}



void AItem::Force(float _DeltaTime)
{
	CurSpeed -= _DeltaTime * SlowSpeed;

	if (0.0f >= Speed)
	{
		Speed = 0.0f;
	}

	CurUpForce -= _DeltaTime * UpSlowSpeed;

	if (-UpForce < CurUpForce && JumpCount == 0)
	{
		AddActorLocation(ForceDir * _DeltaTime * Speed);
		AddActorLocation(UpForceDir * _DeltaTime * CurUpForce);
	}
	else if (-UpForce > CurUpForce && JumpCount == 0)
	{
		++JumpCount;
		UpForce = 200.0f;
		CurUpForce = 200.0f;
	}

	if (-UpForce < CurUpForce && JumpCount == 1)
	{
		AddActorLocation(UpForceDir * _DeltaTime * CurUpForce);
		CurSpeed = Speed / 2;
		AddActorLocation(ForceDir * _DeltaTime * Speed);

	}
	else if (-UpForce > CurUpForce && JumpCount == 1)
	{
		++JumpCount;
		UpForce = 100.0f;
		CurUpForce = 100.0f;
	}

	if (-UpForce < CurUpForce && JumpCount == 2)
	{
		AddActorLocation(UpForceDir * _DeltaTime * CurUpForce);
		CurSpeed = Speed / 4;
		AddActorLocation(ForceDir * _DeltaTime * Speed);

	}
	else if (-UpForce > CurUpForce && JumpCount == 2)
	{
		++JumpCount;
	}
}