#include "PreCompile.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"
#include "InventoryBar.h"
#include "Slot.h"

AInventoryBar::AInventoryBar()
{
	InvenBarSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	InvenBarSpriteRenderer->SetCameraEffect(false);
	InvenBarSpriteRenderer->SetOrder(ERenderOrder::UI);
	InvenBarSpriteRenderer->SetSprite("UI", 3);
	InvenBarSpriteRenderer->SetComponentScale(FVector2D{ 203 * 3.5f, 26 * 3.5f } );
}

AInventoryBar::~AInventoryBar()
{
}

void AInventoryBar::BeginPlay()
{
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	Super::BeginPlay();

	ASlot* Slot_1 = GetWorld()->SpawnActor<ASlot>();
	Slot_1->SetSprite("UI", 5);
	Slot_1->SetActorLocation({ Size.Half().iX() - 311, Size.iY() - 81 });
	AllSlots.push_back(Slot_1);

	ASlot* Slot_2 = GetWorld()->SpawnActor<ASlot>();
	Slot_2->SetSprite("UI", 5);
	Slot_2->SetActorLocation({ Size.Half().iX() - 255, Size.iY() - 81 });
	AllSlots.push_back(Slot_2);

	ASlot* Slot_3 = GetWorld()->SpawnActor<ASlot>();
	Slot_3->SetSprite("UI", 5);
	Slot_3->SetActorLocation({ Size.Half().iX() - 199, Size.iY() - 81 });
	AllSlots.push_back(Slot_3);

	ASlot* Slot_4 = GetWorld()->SpawnActor<ASlot>();
	Slot_4->SetSprite("UI", 5);
	Slot_4->SetActorLocation({ Size.Half().iX() - 143, Size.iY() - 81 });
	AllSlots.push_back(Slot_4);

	ASlot* Slot_5 = GetWorld()->SpawnActor<ASlot>();
	Slot_5->SetSprite("UI", 5);
	Slot_5->SetActorLocation({ Size.Half().iX() - 87, Size.iY() - 81 });
	AllSlots.push_back(Slot_5);

	ASlot* Slot_6 = GetWorld()->SpawnActor<ASlot>();
	Slot_6->SetSprite("UI", 5);
	Slot_6->SetActorLocation({ Size.Half().iX() - 31, Size.iY() - 81 });
	AllSlots.push_back(Slot_6);

	ASlot* Slot_7 = GetWorld()->SpawnActor<ASlot>();
	Slot_7->SetSprite("UI", 5);
	Slot_7->SetActorLocation({ Size.Half().iX() + 25, Size.iY() - 81 });
	AllSlots.push_back(Slot_7);

	ASlot* Slot_8 = GetWorld()->SpawnActor<ASlot>();
	Slot_8->SetSprite("UI", 5);
	Slot_8->SetActorLocation({ Size.Half().iX() + 81, Size.iY() - 81 });
	AllSlots.push_back(Slot_8);

	ASlot* Slot_9 = GetWorld()->SpawnActor<ASlot>();
	Slot_9->SetSprite("UI", 5);
	Slot_9->SetActorLocation({ Size.Half().iX() + 137, Size.iY() - 81 });
	AllSlots.push_back(Slot_9);

	ASlot* Slot_10 = GetWorld()->SpawnActor<ASlot>();
	Slot_10->SetSprite("UI", 5);
	Slot_10->SetActorLocation({ Size.Half().iX() + 193, Size.iY() - 81 });
	AllSlots.push_back(Slot_10);

	ASlot* Slot_11 = GetWorld()->SpawnActor<ASlot>();
	Slot_11->SetSprite("UI", 5);
	Slot_11->SetActorLocation({ Size.Half().iX() + 249, Size.iY() - 81 });
	AllSlots.push_back(Slot_11);

	ASlot* Slot_12 = GetWorld()->SpawnActor<ASlot>();
	Slot_12->SetSprite("UI", 5);
	Slot_12->SetActorLocation({ Size.Half().iX() + 305, Size.iY() - 81 });
	AllSlots.push_back(Slot_12);

}

void AInventoryBar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

