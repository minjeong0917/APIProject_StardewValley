#include "PreCompile.h"
#include "TileMapGameMode.h"
#include <EngineCore/Level.h>

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>

ATileMapGameMode::ATileMapGameMode()
{
}

ATileMapGameMode::~ATileMapGameMode()
{
}

// 타일찍고 저장할 수 있는 레벨
void ATileMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	{
		GroundTileMap = GetWorld()->SpawnActor<ATileMap>();

	}

	{
		WallTileMap = GetWorld()->SpawnActor<ATileMap>();
		WallTileMap->Create("TileSet", { 100, 100 }, { 32, 32 });

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				WallTileMap->SetTileIndex({ y,x }, { 0, -6 }, { 32, 44 }, 2);
			}
		}
	}
}


void ATileMapGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsPress(VK_LBUTTON))
	{
		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
		WallTileMap->SetTileLocation(MousePos, 1);
	}

	if (true == UEngineInput::GetInst().IsPress('R'))
	{
		UEngineSerializer _Ser;
		WallTileMap->Serialize(_Ser);
		UEngineDirectory Dir;

		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Data");

		std::string SaveFilePath = Dir.GetPathToString() + "\\MapData.Data";
		UEngineFile NewFile = SaveFilePath;
		NewFile.FileOpen("wb");
		NewFile.Write(_Ser);
	}

	if (true == UEngineInput::GetInst().IsPress('T'))
	{
		UEngineDirectory Dir;

		if (false == Dir.MoveParentToDirectory("Resources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}

		Dir.Append("Data");

		std::string SaveFilePath = Dir.GetPathToString() + "\\MapData.Data";
		UEngineFile NewFile = SaveFilePath;
		NewFile.FileOpen("rb");

		UEngineSerializer Ser;
		NewFile.Read(Ser);


		WallTileMap->DeSerialize(Ser);
	}

	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		WallTileMap->AddActorLocation(FVector2D::LEFT * _DeltaTime * 100.0f);
	}

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		WallTileMap->AddActorLocation(FVector2D::RIGHT * _DeltaTime * 100.0f);
	}

	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		WallTileMap->AddActorLocation(FVector2D::UP * _DeltaTime * 100.0f);
	}

	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		WallTileMap->AddActorLocation(FVector2D::DOWN * _DeltaTime * 100.0f);
	}

}
