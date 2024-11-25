#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/2DCollision.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"
// Ό³Έν :
class ATitleButton : public AActor
{
public:
	// constrcuter destructer
	ATitleButton();
	~ATitleButton();

	// delete Function
	ATitleButton(const ATitleButton& _Other) = delete;
	ATitleButton(ATitleButton&& _Other) noexcept = delete;
	ATitleButton& operator=(const ATitleButton& _Other) = delete;
	ATitleButton& operator=(ATitleButton&& _Other) noexcept = delete;
	void SetSprite(std::string _SprtieName, int _SpriteIndex);
	void SetOrder(ERenderOrder _RenderOder);
	void SetScale(float _Scale);
	void SetCameraEffect(bool _Effect);

	void CollisionStay(AActor* _ColActor);
	void CollisionEnter(AActor* _ColActor);
	void CollisionEnd(AActor* _ColActor);

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
	U2DCollision* CollisionComponent = nullptr;
	USpriteRenderer* SpriteRenderer = nullptr;

	bool IsCollisionStay = false;
	bool IsCollisionEnter = false;
	bool IsCollisionEnd = false;
	bool IsClick = false;
};

