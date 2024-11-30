#include "PreCompile.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include "ShippingGameMode.h"
#include "ContentsEnum.h"
#include "PlayerManager.h"




AShippingGameMode::AShippingGameMode()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::GoldBACKGROUND);
		SpriteRenderer->SetSprite("ShippingScreen.png");
		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);

		FVector2D Scale = SpriteRenderer->GetComponentScale();

		SpriteRenderer->SetComponentLocation({ Scale.Half().X,Scale.Half().Y });
	}
	DebugOn();
}

AShippingGameMode::~AShippingGameMode()
{
}

void AShippingGameMode::BeginPlay()
{
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	Super::BeginPlay();

	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	Player->SetBackImage("ShippingScreen.png");


	Cursor = GetWorld()->SpawnActor<ACursor>();


	FarmingBox = GetWorld()->SpawnActor<AUI>();
	FarmingBox->SetComponentScale({546.f , 105.f });
	FarmingBox->SetSprite("GoldTextBox.png", 0, 1.0f);
	FarmingBox->SetOrder(ERenderOrder::GoldBox);
	FarmingBox->SetActorLocation({ Size.Half().X, FarmingBox->GetScale().Half().Y + 50.f });
	FarmingBox->SetActive(false);

	FarmingText = GetWorld()->SpawnActor<AGold>();
	FarmingText->SetActorLocation({ Size.Half().X - 240.f, FarmingBox->GetActorLocation().Y});
	FarmingText->SetTextSpriteName("AlphabetBold.png");
	FarmingText->SetOrder(ERenderOrder::GoldBoxText);
	FarmingText->SetTextScale({ 24, 48 });
	FarmingText->SetText2("Farming");
	FarmingText->SetActive(false);

	FarmingGold = GetWorld()->SpawnActor<AGold>();
	FarmingGold->SetActorLocation({ Size.Half().X + 192.f,  FarmingBox->GetActorLocation().Y +2});
	FarmingGold->SetTextSpriteName("Gold3.png");
	FarmingGold->SetOrder(ERenderOrder::GoldBoxText);
	FarmingGold->SetTextScale({ 22, 33 });
	//FarmingGold->SetValue(123456, 3.5f);
	FarmingGold->SetActive(false);


	FaragingBox = GetWorld()->SpawnActor<AUI>();
	FaragingBox->SetComponentScale({ 546.f , 105.f });
	FaragingBox->SetSprite("GoldTextBox.png", 0, 1.0f);
	FaragingBox->SetOrder(ERenderOrder::GoldBox);
	FaragingBox->SetActorLocation({ Size.Half().X, FarmingBox->GetActorLocation().Y + FarmingBox->GetScale().Y + 2.f});
	FaragingBox->SetActive(false);

	FaragingText = GetWorld()->SpawnActor<AGold>();
	FaragingText->SetActorLocation({ Size.Half().X - 240.f,  FaragingBox->GetActorLocation().Y });
	FaragingText->SetTextSpriteName("AlphabetBold.png");
	FaragingText->SetOrder(ERenderOrder::GoldBoxText);
	FaragingText->SetTextScale({ 24, 48 });
	FaragingText->SetText2("Faraging");
	FaragingText->SetActive(false);

	FaragingGold = GetWorld()->SpawnActor<AGold>();
	FaragingGold->SetActorLocation({ Size.Half().X + 192.f,  FaragingBox->GetActorLocation().Y + 2 });
	FaragingGold->SetTextSpriteName("Gold3.png");
	FaragingGold->SetOrder(ERenderOrder::GoldBoxText);
	FaragingGold->SetTextScale({ 22, 33 });
	//FaragingGold->SetValue(123456, 3.5f);
	FaragingGold->SetActive(false);


	FishingBox = GetWorld()->SpawnActor<AUI>();
	FishingBox->SetComponentScale({ 546.f , 105.f });
	FishingBox->SetSprite("GoldTextBox.png", 0, 1.0f);
	FishingBox->SetOrder(ERenderOrder::GoldBox);
	FishingBox->SetActorLocation({ Size.Half().X, FaragingBox->GetActorLocation().Y + FarmingBox->GetScale().Y + 2.f });
	FishingBox->SetActive(false);

	FishingText = GetWorld()->SpawnActor<AGold>();
	FishingText->SetActorLocation({ Size.Half().X - 240.f,FishingBox->GetActorLocation().Y });
	FishingText->SetTextSpriteName("AlphabetBold.png");
	FishingText->SetOrder(ERenderOrder::GoldBoxText);
	FishingText->SetTextScale({ 24, 48 });
	FishingText->SetText2("Fishing");
	FishingText->SetActive(false);

	FishingGold = GetWorld()->SpawnActor<AGold>();
	FishingGold->SetActorLocation({ Size.Half().X + 192.f,  FishingBox->GetActorLocation().Y + 2 });
	FishingGold->SetTextSpriteName("Gold3.png");
	FishingGold->SetOrder(ERenderOrder::GoldBoxText);
	FishingGold->SetTextScale({ 22, 33 });
	//FishingGold->SetValue(123456, 3.5f);
	FishingGold->SetActive(false);


	MiningBox = GetWorld()->SpawnActor<AUI>();
	MiningBox->SetComponentScale({ 546.f , 105.f });
	MiningBox->SetSprite("GoldTextBox.png", 0, 1.0f);
	MiningBox->SetOrder(ERenderOrder::GoldBox);
	MiningBox->SetActorLocation({ Size.Half().X, FishingBox->GetActorLocation().Y + FarmingBox->GetScale().Y + 2.f });
	MiningBox->SetActive(false);

	MiningText = GetWorld()->SpawnActor<AGold>();
	MiningText->SetActorLocation({ Size.Half().X - 240.f,MiningBox->GetActorLocation().Y });
	MiningText->SetTextSpriteName("AlphabetBold.png");
	MiningText->SetOrder(ERenderOrder::GoldBoxText);
	MiningText->SetTextScale({ 24, 48 });
	MiningText->SetText2("Mining");
	MiningText->SetActive(false);

	MiningGold = GetWorld()->SpawnActor<AGold>();
	MiningGold->SetActorLocation({ Size.Half().X + 192.f,  MiningBox->GetActorLocation().Y + 2 });
	MiningGold->SetTextSpriteName("Gold3.png");
	MiningGold->SetOrder(ERenderOrder::GoldBoxText);
	MiningGold->SetTextScale({ 22, 33 });
	//MiningGold->SetValue(123456, 3.5f);
	MiningGold->SetActive(false);


	OtherBox = GetWorld()->SpawnActor<AUI>();
	OtherBox->SetComponentScale({ 546.f , 105.f });
	OtherBox->SetSprite("GoldTextBox.png", 0, 1.0f);
	OtherBox->SetOrder(ERenderOrder::GoldBox);
	OtherBox->SetActorLocation({ Size.Half().X, MiningBox->GetActorLocation().Y + FarmingBox->GetScale().Y + 2.f });
	OtherBox->SetActive(false);

	OtherText = GetWorld()->SpawnActor<AGold>();
	OtherText->SetActorLocation({ Size.Half().X - 240.f,OtherBox->GetActorLocation().Y });
	OtherText->SetTextSpriteName("AlphabetBold.png");
	OtherText->SetOrder(ERenderOrder::GoldBoxText);
	OtherText->SetTextScale({ 24, 48 });
	OtherText->SetText2("Other");
	OtherText->SetActive(false);

	OtherGold = GetWorld()->SpawnActor<AGold>();
	OtherGold->SetActorLocation({ Size.Half().X + 192.f,  OtherBox->GetActorLocation().Y + 2 });
	OtherGold->SetTextSpriteName("Gold3.png");
	OtherGold->SetOrder(ERenderOrder::GoldBoxText);
	OtherGold->SetTextScale({ 22, 33 });
	//OtherGold->SetValue(123456, 3.5f);
	OtherGold->SetActive(false);


	TotalBox = GetWorld()->SpawnActor<AUI>();
	TotalBox->SetComponentScale({ 546.f , 105.f });
	TotalBox->SetSprite("GoldTextBox.png", 0, 1.0f);
	TotalBox->SetOrder(ERenderOrder::GoldBox);
	TotalBox->SetActorLocation({ Size.Half().X, OtherBox->GetActorLocation().Y + FarmingBox->GetScale().Y + 2.f });
	TotalBox->SetActive(false);

	TotalText = GetWorld()->SpawnActor<AGold>();
	TotalText->SetActorLocation({ Size.Half().X - 240.f,TotalBox->GetActorLocation().Y });
	TotalText->SetTextSpriteName("AlphabetBold.png");
	TotalText->SetOrder(ERenderOrder::GoldBoxText);
	TotalText->SetTextScale({ 24, 48 });
	TotalText->SetText2("Total");
	TotalText->SetActive(false);

	TotalGold = GetWorld()->SpawnActor<AGold>();
	TotalGold->SetActorLocation({ Size.Half().X + 192.f,  TotalText->GetActorLocation().Y + 2 });
	TotalGold->SetTextSpriteName("Gold3.png");
	TotalGold->SetOrder(ERenderOrder::GoldBoxText);
	TotalGold->SetTextScale({ 22, 33 });
	//TotalGold->SetValue(123456, 3.5f);
	TotalGold->SetActive(false);

	OKButton = GetWorld()->SpawnActor<AUI>();
	OKButton->SetComponentScale({ 64.f , 64.f });
	OKButton->SetCollisionComponentScale({ 64.f , 64.f });
	OKButton->SetSprite("OKButton.png", 0, 1.0f);
	OKButton->SetOrder(ERenderOrder::GoldBox);
	OKButton->SetActorLocation({ Size.X - 300.f, TotalText->GetActorLocation().Y + 2 });
	OKButton->SetCollisionComponentLocation({ 0.0f , 0.0f });
	OKButton->SetActive(false);

}
void AShippingGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	APlayer* Player = GetWorld()->GetPawn<APlayer>();

	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	Cursor->SetActorLocation({ MousePos.X + 10, MousePos.Y + 15 });

	MiningGold->SetValue(Player->PlayerUI->MiningGold, 3.5f);
	FarmingGold->SetValue(Player->PlayerUI->FarmingGold, 3.5f);
	FaragingGold->SetValue(Player->PlayerUI->FaragingGold, 3.5f);
	FishingGold->SetValue(Player->PlayerUI->FishingGold, 3.5f);
	OtherGold->SetValue(Player->PlayerUI->OtherGold, 3.5f);
	TotalGold->SetValue(Player->PlayerUI->TotalGold, 3.5f);

	

	Player->PlayerUI->MinTime->IsStop = false;
	Player->PlayerUI->HourTime->IsStop = false;


	Time += _DeltaTime * 1.5f;
	if (Time > 1.0f && Time <= 2.0)
	{
		FarmingBox->SetActive(true);
		FarmingText->SetActive(true);
		FarmingGold->SetActive(true);
	}
	else if (Time > 2.0f && Time <= 3.0)
	{
		FaragingBox->SetActive(true);
		FaragingText->SetActive(true);
		FaragingGold->SetActive(true);
	}
	else if (Time > 3.0f && Time <= 4.0f)
	{
		FishingBox->SetActive(true);
		FishingText->SetActive(true);
		FishingGold->SetActive(true);
	}
	else if (Time > 4.0f && Time <= 5.0f)
	{
		MiningBox->SetActive(true);
		MiningText->SetActive(true);
		MiningGold->SetActive(true);
	}
	else if (Time > 5.0f && Time <= 6.0f)
	{
		OtherBox->SetActive(true);
		OtherGold->SetActive(true);
		OtherText->SetActive(true);
	}
	else if (Time > 6.0f)
	{
		TotalBox->SetActive(true);
		TotalGold->SetActive(true);
		TotalText->SetActive(true);
		OKButton->SetActive(true);
	}

	if (true == OKButton->GetIsCollisionEnter())
	{
		if (IsPlayOnce == false)
		{
			//BGMPlayer = UEngineSound::Play("TitleButtonHover.wav");
			IsPlayOnce = true;

		}
		OKButton->SetSprite("OKButton.png", 0, 1.1f);
	}

	if (true == OKButton->GetIsCollisionEnd())
	{
		IsPlayOnce = false;

		OKButton->SetSprite("OKButton.png", 0, 1.0f);
	}

	if (true == OKButton->GetIsClick())
	{
		if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
		{
			Time = 0;

			int CurGold = PlayerManager::GetInst().GetGold();
			PlayerManager::GetInst().SetGold(CurGold + Player->PlayerUI->TotalGold);
			Player->PlayerUI->PlayerUIUnActive(true);

			Player->PlayerUI->FarmingGold = 0;
			Player->PlayerUI->FaragingGold = 0;
			Player->PlayerUI->FishingGold = 0;
			Player->PlayerUI->MiningGold = 0;
			Player->PlayerUI->OtherGold = 0;
			Player->PlayerUI->TotalGold = 0;

			FarmingBox->SetActive(false);
			FaragingBox->SetActive(false);
			FishingBox->SetActive(false);
			MiningBox->SetActive(false);
			OtherBox->SetActive(false);
			TotalBox->SetActive(false);
			OKButton->SetActive(false);
			FarmingText->SetActive(false);
			FaragingText->SetActive(false);
			FishingText->SetActive(false);
			MiningText->SetActive(false);
			OtherText->SetActive(false);
			TotalText->SetActive(false);
			FarmingGold->SetActive(false);
			FaragingGold->SetActive(false);
			FishingGold->SetActive(false);
			MiningGold->SetActive(false);
			OtherGold->SetActive(false);
			TotalGold->SetActive(false);


			UEngineAPICore::GetCore()->OpenLevel("House");
			UEngineSound::AllSoundOff();
		}

	}

}