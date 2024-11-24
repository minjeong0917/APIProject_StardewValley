#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>

#include "ContentsEnum.h"



ATitleGameMode::ATitleGameMode()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		SpriteRenderer->SetSprite("TitleBackGround.png");
		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);

		FVector2D Scale = SpriteRenderer->GetComponentScale();

		SpriteRenderer->SetComponentLocation({ Scale.Half().X, 0.0f });
	}
	DebugOn();

}

ATitleGameMode::~ATitleGameMode()
{
}


void ATitleGameMode::BeginPlay()
{
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	Super::BeginPlay();

	Cursor = GetWorld()->SpawnActor<ACursor>();

	Logo = GetWorld()->SpawnActor<ATitleLogo>();
	Logo->SetSprite("Logo.png", 0, 1.0f);
	Logo->SetOrder(ERenderOrder::BACKGROUND);
	Logo->SetActive(false);

	LogoAnimation = GetWorld()->SpawnActor<ATitleLogo>();
	LogoAnimation->SetOrder(ERenderOrder::LOGO);
	LogoAnimation->SetSprite("LogoAnimation", 0, 1.0f);
	LogoAnimation->CreateAnimation("TiltleLogoAni", "LogoAnimation", { 1,2,1,0, 1,2,1,0, 1,2,1,0 }, { 0.1f,0.1f ,0.1f , 0.1f,0.1f ,0.1f ,0.1f,0.1f ,0.1f ,0.1f,0.1f ,5.0f }, true);

	Tree = GetWorld()->SpawnActor<ATitleLogo>();
	Tree->SetSprite("Tree.png", 0, 1.0f);
	Tree->SetOrder(ERenderOrder::LOGO);
	Tree->SetActorLocation({ Size.Half().X, Size.Half().Y+ Tree->GetScale().Half().Y});

	Mountain_1 = GetWorld()->SpawnActor<ATitleLogo>();
	Mountain_1->SetSprite("Mountain1.png", 0, 1.0f);
	Mountain_1->SetOrder(ERenderOrder::TitleUI1);
	Mountain_1->SetActorLocation({ Size.Half().X, Size.Half().Y + Mountain_1->GetScale().Y });

	Mountain_2 = GetWorld()->SpawnActor<ATitleLogo>();
	Mountain_2->SetSprite("Mountain2.png", 0, 1.0f);
	Mountain_2->SetOrder(ERenderOrder::TitleUI2);
	Mountain_2->SetActorLocation({ Size.Half().X, Size.Half().Y + Mountain_2->GetScale().Y });

	NewButton = GetWorld()->SpawnActor<ATitleButton>();
	NewButton->SetSprite("NewButton.png", 0);
	NewButton->SetOrder(ERenderOrder::LOGO);
	NewButton->SetActive(false);


}


void ATitleGameMode::Tick(float _DeltaTime)
{

	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	Cursor->SetActorLocation({ MousePos.X + 10, MousePos.Y + 15 });

	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Farm");
	}
	if (true == UEngineInput::GetInst().IsDown(VK_F1))
	{
		UEngineDebug::SwitchIsDebug();
	}


	CameraMove(_DeltaTime);

	FVector2D Location = FVector2D::UP;
	TreePos += Location * _DeltaTime * 30;
	UIMove(Tree, _DeltaTime, TreePos);

	Mountain1Pos += Location * _DeltaTime * 80;
	UIMove(Mountain_1, _DeltaTime, Mountain1Pos);

	Mountain2Pos += Location * _DeltaTime * 100;
	UIMove(Mountain_2, _DeltaTime, Mountain2Pos);
}

void ATitleGameMode::UIMove(ATitleLogo* _ATitleLogo, float _DeltaTime, FVector2D Pos)
{
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	_ATitleLogo->SetActorLocation({ Size.Half().X, Size.Y  -100 + Pos.Y });
	CameraPos = GetWorld()->GetCameraPos();
	UEngineDebug::CoreOutPutString(std::to_string(_ATitleLogo->GetActorLocation().Y - _ATitleLogo->GetTransform().Scale.Y));

	if (CameraPos.Y <= (_ATitleLogo->GetActorLocation().Y * (-1.0f)) - _ATitleLogo->GetTransform().Scale.Y + CameraPos.Y)
	{
		_ATitleLogo->Destroy();
		_ATitleLogo = nullptr;

	}
}


void ATitleGameMode::CameraMove(float _DeltaTime)
{
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	GetWorld()->SetCameraToMainPawn(false);


	CameraPos = GetWorld()->GetCameraPos();
	FVector2D Location = FVector2D::UP;

	FVector2D Scale = SpriteRenderer->GetComponentScale();

	CameraPos += Location * _DeltaTime * Speed;
	UEngineDebug::CoreOutPutString(std::to_string(CameraPos.Y));


	if (CameraPos.Y <= -Scale.Y + Size.Y + Size.Half().Y)
	{
		CameraPos.Y = -Scale.Y + Size.Y + Size.Half().Y;

		IsArrive = true;
		Logo->SetActive(true);
		Logo->SetActorLocation({ Size.Half().X, CameraPos.Half().Y - Logo->GetScale().Half().Y - 80 });

		NewButton->SetActive(true);
		NewButton->SetActorLocation({ Size.Half().X - 350 ,Size.Half().Y + 250 });

		LogoAnimation->SetActorLocation({ Size.Half().X, CameraPos.Half().Y - Logo->GetScale().Half().Y - 80 });
		LogoAnimation->ChangeAnimation("TiltleLogoAni");
	}

	GetWorld()->SetCameraPos(CameraPos);


}