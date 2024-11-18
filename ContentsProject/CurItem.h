#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ActorComponent.h>
#include <EngineCore/ImageManager.h>

// Ό³Έν :
class ACurItem : public AActor
{
public:
	// constrcuter destructer
	ACurItem();
	~ACurItem();

	// delete Function
	ACurItem(const ACurItem& _Other) = delete;
	ACurItem(ACurItem&& _Other) noexcept = delete;
	ACurItem& operator=(const ACurItem& _Other) = delete;
	ACurItem& operator=(ACurItem&& _Other) noexcept = delete;
	void SetSprite(std::string _SprtieName, int _SpriteIndex, float _Scale);

protected:
	void BeginPlay() override;

private:
	class USpriteRenderer* ItemSpriteRenderer = nullptr;

};

