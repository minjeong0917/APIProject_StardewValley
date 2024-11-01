#pragma once

// Ό³Έν :
class ATownMap : public AActor
{
public:
	// constrcuter destructer
	ATownMap();
	~ATownMap();

	// delete Function
	ATownMap(const ATownMap& _Other) = delete;
	ATownMap(ATownMap&& _Other) noexcept = delete;
	ATownMap& operator=(const ATownMap& _Other) = delete;
	ATownMap& operator=(ATownMap&& _Other) noexcept = delete;

protected:

private:

};

