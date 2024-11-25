#pragma once
#include <EngineCore/Actor.h>
#include "ContentsEnum.h"

// Ό³Έν :
class AFade : public AActor
{
public:
	static AFade* MainFade;

public:
	// constrcuter destructer
	AFade();
	~AFade();

	// delete Function
	AFade(const AFade& _Other) = delete;
	AFade(AFade&& _Other) noexcept = delete;
	AFade& operator=(const AFade& _Other) = delete;
	AFade& operator=(AFade&& _Other) noexcept = delete;

	void FadeIn();

	void FadeOut();
	void SetOrder(ERenderOrder _Order);
	void SetAlphaChar(float _Alpha);

protected:

private:
	void LevelChangeStart() override;
	float FadeValue = 0.0f;
	float FadeDir = 1.0f;
	USpriteRenderer* BackSpriteRenderer;
	void FadeChange();

};

