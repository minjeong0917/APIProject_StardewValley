#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class ATree : public AActor
{
public:
	// constrcuter destructer
	ATree();
	~ATree();

	// delete Function
	ATree(const ATree& _Other) = delete;
	ATree(ATree&& _Other) noexcept = delete;
	ATree& operator=(const ATree& _Other) = delete;
	ATree& operator=(ATree&& _Other) noexcept = delete;

protected:

private:

};

