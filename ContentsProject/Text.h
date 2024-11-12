#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>

// Ό³Έν :
class AText : public AActor
{
public:
	// constrcuter destructer
	AText();
	~AText();

	// delete Function
	AText(const AText& _Other) = delete;
	AText(AText&& _Other) noexcept = delete;
	AText& operator=(const AText& _Other) = delete;
	AText& operator=(AText&& _Other) noexcept = delete;

	class USpriteRenderer* TextSpriteRenderer = nullptr;
protected:

private:

};

