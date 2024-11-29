#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

#include "ContentsEnum.h"

// Ό³Έν :
class AUI : public AActor
{
public:
	// constrcuter destructer
	AUI();
	~AUI();

	// delete Function
	AUI(const AUI& _Other) = delete;
	AUI(AUI&& _Other) noexcept = delete;
	AUI& operator=(const AUI& _Other) = delete;
	AUI& operator=(AUI&& _Other) noexcept = delete;
	void SetSprite(std::string _SpriteName, int _Index, float _Scale);
	void SetOrder(ERenderOrder _Order);
	void SetPivotType(PivotType _Type);
	void SetPivot(FVector2D _Pivot);

	void SetComponentScale(FVector2D _Scale);
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop = true);
	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false);
	FVector2D GetScale()
	{
		return Scale;
	}

	FVector2D GetLocation();

	void SetCollisionActive(bool _IsActive = false);
	void SetCollisionComponentScale(FVector2D _Scale);
	void SetCollisionComponentLocation(FVector2D _Location);

	void CollisionEnter(AActor* _ColActor);
	void CollisionEnd(AActor* _ColActor);
	void CollisionStay(AActor* _ColActor);
	bool GetIsCollisionStay()
	{
		return IsCollisionStay;
	}

	bool GetIsCollisionEnter()
	{
		return IsCollisionEnter;
	}


	bool GetIsCollisionEnd()
	{
		return IsCollisionEnd;
	}

	bool GetIsClick()
	{
		return IsClick;
	}
protected:

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	class USpriteRenderer* SpriteRenderer = nullptr;
	U2DCollision* CollisionComponent = nullptr;

	FVector2D Scale = { 0,0 };
	FVector2D Location = { 0,0 };

	bool IsCollisionStay = false;
	bool IsCollisionEnter = false;
	bool IsCollisionEnd = false;
	bool IsClick = false;


};

