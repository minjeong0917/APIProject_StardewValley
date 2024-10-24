#pragma once
#include "GameMode.h"

// ULevel : Actor 관리
class ULevel
{
public:
	friend class UEngineAPICore;
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	void Tick();
	void Render();

	// Actor 생성
	template<typename ActorType>
	ActorType* SpawnActor()
	{
		ActorType* NewActor = new ActorType();

		AActor* ActorPtr = dynamic_cast<AActor*>(NewActor);
		ActorPtr->World = this;

		NewActor->BeginPlay();
		AllActors.push_back(NewActor);
		return NewActor;
	}

protected:

private:
	// GameMode및 주인공 생성 및 세팅 후 AllAcotrs에 추가
	// GameModeType : 게임레벨 , MainPawnType : 주인공
	template<typename GameModeType, typename MainPawnType>
	void CreateGameMode()
	{
		GameMode = new GameModeType();
		MainPawn = new MainPawnType();

		MainPawn->World = this;
		GameMode->World = this;

		GameMode->BeginPlay();
		MainPawn->BeginPlay();

		AllActors.push_back(GameMode);
		AllActors.push_back(MainPawn);
	}

	class AGameMode* GameMode = nullptr;

	// 주인공
	AActor* MainPawn = nullptr;

	// Actor들 list로 관리
	std::list<AActor*> AllActors;
};

