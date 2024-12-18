#pragma once
#include <EngineCore/EngineAPICore.h>

class ContentsCore : public UContentsCore
{
public:
	// constrcuter destructer
	ContentsCore();
	~ContentsCore();

	// delete Function
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;



protected:
	void BeginPlay() override;
	void Tick() override;
	void ReadySprite();
private:

};

