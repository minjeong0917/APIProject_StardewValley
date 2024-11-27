#include "PreCompile.h"

#include "Slot.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>
#include <EnginePlatform/EngineInput.h>
#include "Player.h"
#include "SelectedItem.h"


ASlot::ASlot()
{
	{
		SlotSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SlotSpriteRenderer->SetCameraEffect(false);
		SlotSpriteRenderer->SetOrder(ERenderOrder::SLOT);
		SlotSpriteRenderer->SetComponentScale(FVector2D{ 16 * 3.5f, 16 * 3.5f });
	}
	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		//CollisionComponent->SetComponentLocation({ 0, 0 });

		CollisionComponent->SetComponentScale(FVector2D{ 14 * 3.5f, 14 * 3.5f });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::SLOT);
		CollisionComponent->SetCollisionType(ECollisionType::Rect);
		CollisionComponent->SetCameraEffect(false);


		DebugOn();
	}

	
	CollisionComponent->SetCollisionStay(std::bind(&ASlot::CollisionStay, this, std::placeholders::_1));
	CollisionComponent->SetCollisionEnd(std::bind(&ASlot::CollisionEnd, this, std::placeholders::_1));
	CollisionComponent->SetCollisionEnter(std::bind(&ASlot::CollisionEnter, this, std::placeholders::_1));



}

void ASlot::SetCollisionComponentScale(FVector2D Scale)
{
	CollisionComponent->SetComponentScale(Scale);

}
void ASlot::CollisionStay(AActor* _ColActor)
{
	IsStay = true;


	if (this->GetName() == "EmptySlot")
	{
		if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
		{
			IsSelectedItem = 2;
		}
	}
	else if (this->GetName() != "EmptySlot" && IsSelectedItem != 1)
	{
		if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON) )
		{
			SelectedItemName = GetName();
			SelectedItemSpriteName = GetItemSpriteName();
			SelectedItemIndex = GetItemIndex();
			SelecteItemScale = GetItemScale();

			IsSelectedItem = 1;
		}
	}
	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		if (this->GetName() == SelectedItemName)
		{
			IsEqualItem = true;
		}
	}
	if (true == UEngineInput::GetInst().IsUp(VK_LBUTTON))
	{
		IsEqualItem = false;
	}
	if (this->GetName() != "EmptySlot"&&true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		IsEqualItem = true;

	}


}

void ASlot::CollisionEnd(AActor* _ColActor)
{
	IsStay = false;
	IsSell = false;



}

void ASlot::CollisionEnter(AActor* _ColActor)
{

	if (this->GetName() != "EmptySlot")
	{
		//if (true == UEngineInput::GetInst().IsDown(VK_RBUTTON))
		//{
			IsSell = true;
		//}
	}

}

ASlot::~ASlot()
{
}


void ASlot::BeginPlay()
{


	Super::BeginPlay();


}

void ASlot::Tick(float _DeltaTime)
{


	Super::Tick(_DeltaTime);


}


void ASlot::SetOrder(ERenderOrder _RenderOder)
{
	SlotSpriteRenderer->SetOrder(_RenderOder);
}

void ASlot::CollisionDestroy()
{
	CollisionComponent->Destroy();
}




void ASlot::SetSprite(std::string _SprtieName, int _SpriteIndex)
{
	SlotSpriteRenderer->SetSprite(_SprtieName, _SpriteIndex);
}

void ASlot::SetComponentLocation(FVector2D _Location)
{
	SlotSpriteRenderer->SetComponentLocation(_Location);
}


void ASlot::SetScale(FVector2D _Scale)
{
	SlotSpriteRenderer->SetComponentScale(_Scale);
}

void ASlot::CountText()
{
	Text = GetWorld()->SpawnActor<AGold>();
	Text->SetActorLocation(GetActorLocation() + GetScale().Half());
	Text->SetTextSpriteName("Item.png");
	Text->SetOrder(ERenderOrder::SLOTFont);
	Text->SetTextScale({ 13, 15 });
	Text->SetValue(SlotItemCount, 1.3f);
}
void ASlot::CountTextLocation(FVector2D _Loc)
{
	Text->SetActorLocation(GetActorLocation() + GetScale().Half());
}

void ASlot::CountTextDestroy()
{
	if (Text != nullptr)
	{
		Text->Destroy();
		Text = nullptr;
	}

}

void ASlot::SetTextLocation(FVector2D _Location)
{
	Text->SetActorLocation(_Location);
}

void ASlot::SaveItemInfo(std::string _SpriteName, int _Index, FVector2D _Scale)
{
	ItemIndex = _Index;
	ItemSpriteName = _SpriteName;
	ItemScale = _Scale;
}

