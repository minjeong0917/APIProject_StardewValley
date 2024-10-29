#pragma once
#include <EngineCore/Actor.h>

class AFarmMap : public AActor
{
public:
	// constrcuter destructer
	AFarmMap();
	~AFarmMap();

	// delete Function
	AFarmMap(const AFarmMap& _Other) = delete;
	AFarmMap(AFarmMap&& _Other) noexcept = delete;
	AFarmMap& operator=(const AFarmMap& _Other) = delete;
	AFarmMap& operator=(AFarmMap&& _Other) noexcept = delete;

protected:

private:

};

