#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
// Ό³Έν :
class APlayerToolsAnimation : public AActor
{
public:
	// constrcuter destructer
	APlayerToolsAnimation();
	~APlayerToolsAnimation();

	// delete Function
	APlayerToolsAnimation(const APlayerToolsAnimation& _Other) = delete;
	APlayerToolsAnimation(APlayerToolsAnimation&& _Other) noexcept = delete;
	APlayerToolsAnimation& operator=(const APlayerToolsAnimation& _Other) = delete;
	APlayerToolsAnimation& operator=(APlayerToolsAnimation&& _Other) noexcept = delete;

	
	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false);
protected:

private:
	class USpriteRenderer* SpriteRenderer;

};

