#include "PreCompile.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"
#include <EngineBase/EngineRandom.h>
#include "Item.h"

AItem::AItem()
{

	ItemSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ItemSpriteRenderer->SetOrder(ERenderOrder::UI);
}

AItem::~AItem()
{
}
void AItem::BeginPlay()
{

}

void AItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Force(_DeltaTime);
}


void AItem::SetSprite(std::string _SprtieName, int _SpriteIndex, float _Scale)
{
	ItemSpriteRenderer->SetSprite(_SprtieName, _SpriteIndex);
	ItemSpriteRenderer->SetSpriteScale(_Scale, _SpriteIndex);

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