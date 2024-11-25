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
	Logo->SetOrder(ERenderOrder::LOGO);
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

	Cloud = GetWorld()->SpawnActor<ATitleLogo>();
	Cloud->SetSprite("Cloud.png", 0, 3.0f);
	Cloud->SetOrder(ERenderOrder::Cloud);
	Cloud->SetCameraEffect(false);

	Cloud3 = GetWorld()->SpawnActor<ATitleLogo>();
	Cloud3->SetSprite("Cloud.png", 0, 6.0f);
	Cloud3->SetOrder(ERenderOrder::Cloud);
	Cloud3->SetCameraEffect(false);

	Cloud2 = GetWorld()->SpawnActor<ATitleLogo>();
	Cloud2->SetSprite("Cloud.png", 0, 5.0f);
	Cloud2->SetOrder(ERenderOrder::Cloud);
	Cloud2->SetCameraEffect(false);
	Cloud2->SetActive(false);

	NewButton = GetWorld()->SpawnActor<ATitleButton>();
	NewButton->SetSprite("NewButton.png", 0);
	NewButton->SetOrder(ERenderOrder::LOGO);
	NewButton->SetActive(false);


}


void ATitleGameMode::Tick(float _DeltaTime)
{
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	Cursor->SetActorLocation({ MousePos.X + 10, MousePos.Y + 15 });

	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown(VK_F1))
	{
		UEngineDebug::SwitchIsDebug();
	}

	CameraMove(_DeltaTime);

	FVector2D Vector = FVector2D::ZERO;
	FVector2D UPLocation = FVector2D::UP;
	FVector2D DownLocation = FVector2D::DOWN;
	FVector2D LeftLocation = FVector2D::LEFT;

	TreePos += UPLocation * _DeltaTime * 30;
	UIMove(Tree, _DeltaTime, TreePos);

	Mountain1Pos += UPLocation * _DeltaTime * 80;
	UIMove(Mountain_1, _DeltaTime, Mountain1Pos);

	Mountain2Pos += UPLocation * _DeltaTime * 100;
	UIMove(Mountain_2, _DeltaTime, Mountain2Pos);

	Vector = DownLocation + LeftLocation;
	Vector.Normalize();

	if (Cloud != nullptr)
	{
		CloudPos += Vector * _DeltaTime * 120;
		Cloud->SetActorLocation({ Size.X + CloudPos.X,  CloudPos.Y + Size.Half().Y});

		UEngineDebug::CoreOutPutString(std::to_string(Size.Y - CameraPos.Y));
		UEngineDebug::CoreOutPutString(std::to_string(Cloud->GetActorLocation().Y));

		if (Size.Y  <= Cloud->GetActorLocation().Y - Cloud->GetScale().Half().Y)
		{
			Cloud->Destroy();
			Cloud = nullptr;
		}
	}

	if (Cloud3 != nullptr)
	{
		FVector2D Scale = SpriteRenderer->GetComponentScale();

		if (CameraPos.Y > -Scale.Y + Size.Y + Size.Half().Y )
		{
			Cloud3Pos += Vector * _DeltaTime * 80;
			Cloud3->SetActorLocation({ Size.X + Cloud3Pos.X,  Cloud3Pos.Y - 150});

			UEngineDebug::CoreOutPutString(std::to_string(Size.Y - CameraPos.Y));
			UEngineDebug::CoreOutPutString(std::to_string(Cloud3->GetActorLocation().Y));

			return;
		}
		else
		{
			Cloud3Pos += LeftLocation * _DeltaTime * 80;
			Cloud3->SetActorLocation({ Size.X + Cloud3Pos.X,  Cloud3Pos.Y - 150 });
		}

		if (Size.X <= Cloud3->GetActorLocation().X - Cloud3->GetScale().Half().X)
		{
			Cloud3->Destroy();
			Cloud3 = nullptr;
		}
	}

	if (true == NewButton->GetIsCollisionEnter())
	{
		NewButton->SetSprite("NewButtonHover.png", 0);
		NewButton->SetScale(1.6f);
	}

	if (true == NewButton->GetIsCollisionEnd())
	{
		NewButton->SetSprite("NewButton.png", 0);
		NewButton->SetScale(1.5f);
	}

	if (true == NewButton->GetIsClick())
	{
		UEngineAPICore::GetCore()->OpenLevel("Farm");
	}
}

void ATitleGameMode::UIMove(ATitleLogo* _ATitleLogo, float _DeltaTime, FVector2D Pos)
{
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	_ATitleLogo->SetActorLocation({ Size.Half().X, Size.Y  -100 + Pos.Y });
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

	FVector2D DownLocation = FVector2D::DOWN;
	LogoPos += DownLocation * _DeltaTime * 100;
	Logo->SetActive(true);
	Logo->SetCameraEffect(false);
	Logo->SetActorLocation({ Size.Half().X, LogoPos.Y - Logo->GetScale().Y-73});


	if (CameraPos.Y <= -Scale.Y + Size.Y + Size.Half().Y)
	{
		CameraPos.Y = -Scale.Y + Size.Y + Size.Half().Y;

		IsArrive = true;
		Logo->SetCameraEffect(true);
		Logo->SetActive(true);
		Logo->SetActorLocation({ Size.Half().X, CameraPos.Half().Y - Logo->GetScale().Half().Y - 80 });

		NewButton->SetActive(true);
		NewButton->SetActorLocation({ Size.Half().X - 350 ,Size.Half().Y + 230 });

		LogoAnimation->SetActorLocation({ Size.Half().X, CameraPos.Half().Y - Logo->GetScale().Half().Y - 80 });
		LogoAnimation->ChangeAnimation("TiltleLogoAni");

		FVector2D LeftLocation = FVector2D::LEFT;
		Cloud2->SetActive(true);
		Cloud2Pos += LeftLocation * _DeltaTime * 30;
		Cloud2->SetActorLocation({ Size.X+ Cloud2->GetScale().Half().X + Cloud2Pos.X, Size.Y - 100 });
	}

	GetWorld()->SetCameraPos(CameraPos);

}