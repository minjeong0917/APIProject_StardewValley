#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"
// Ό³Έν :
class ATitleLogo : public AActor
{
public:
	// constrcuter destructer
	ATitleLogo();
	~ATitleLogo();

	// delete Function
	ATitleLogo(const ATitleLogo& _Other) = delete;
	ATitleLogo(ATitleLogo&& _Other) noexcept = delete;
	ATitleLogo& operator=(const ATitleLogo& _Other) = delete;
	ATitleLogo& operator=(ATitleLogo&& _Other) noexcept = delete;
	FVector2D GetScale();
	void SetCameraEffect(bool _Effect);


	void SetSprite(std::string _SptriteName, int _Index, float _Scale);

	void SetOrder(ERenderOrder _Order);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop = true);
	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false);
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	USpriteRenderer* SpriteRenderer = nullptr;
};

