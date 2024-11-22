#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
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
	void SetComponentScale(FVector2D _Scale);
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop = true);
	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false);
	FVector2D GetScale()
	{
		return Scale;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	class USpriteRenderer* SpriteRenderer = nullptr;
	FVector2D Scale = { 0,0 };

};

