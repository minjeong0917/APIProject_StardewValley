#pragma once
#include <EngineCore/GameMode.h>


// ���� ���� ���
class AFarmGameMode : public AGameMode
{
public:
	// constrcuter destructer
	AFarmGameMode();
	~AFarmGameMode();

	// delete Function
	AFarmGameMode(const AFarmGameMode& _Other) = delete;
	AFarmGameMode(AFarmGameMode&& _Other) noexcept = delete;
	AFarmGameMode& operator=(const AFarmGameMode& _Other) = delete;
	AFarmGameMode& operator=(AFarmGameMode&& _Other) noexcept = delete;

	void BeginPlay();

protected:

private:

};

