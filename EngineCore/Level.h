#pragma once
#include "GameMode.h"

// 설명 :
class ULevel
{
public:
	friend class USpriteRenderer;
	friend class UEngineAPICore;
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);
	void Render(float _DeltaTime);

	template<typename ActorType>
	ActorType* SpawnActor()
	{
		ActorType* NewActor = new ActorType();

		AActor* ActorPtr = dynamic_cast<AActor*>(NewActor);
		ActorPtr->World = this;

		BeginPlayList.push_back(ActorPtr);
		return NewActor;
	}

	void SetCameraToMainPawn(bool _IsCameraToMainPawn)
	{
		IsCameraToMainPawn = _IsCameraToMainPawn;
	}

	void SetCameraPivot(FVector2D _Pivot)
	{
		CameraPivot = _Pivot;
	}

protected:

private:
	void ScreenClear();
	void DoubleBuffering();

	// GameMode및 주인공 생성 및 세팅 후 AllAcotrs에 추가
	// GameModeType : 게임레벨 , MainPawnType : 주인공
	template<typename GameModeType, typename MainPawnType>
	void CreateGameMode()
	{
		GameMode = new GameModeType();
		MainPawn = new MainPawnType();

		MainPawn->World = this;
		GameMode->World = this;

		BeginPlayList.push_back(GameMode);
		BeginPlayList.push_back(MainPawn);
	}



	void PushRenderer(class USpriteRenderer* _Renderer);
	void ChangeRenderOrder(class USpriteRenderer* _Renderer, int _PrevOrder);

	class AGameMode* GameMode = nullptr;

	// 주인공
	class AActor* MainPawn = nullptr;

	// Actor들 list로 관리
	std::list<AActor*> AllActors;

	std::list<AActor*> BeginPlayList;

	bool IsCameraToMainPawn = true;

	FVector2D CameraPos;
	FVector2D CameraPivot;

	std::map<int, std::list<class USpriteRenderer*>> Renderers;
};

