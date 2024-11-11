#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>
// Ό³Έν :
class ATime : public AActor
{
public:
	// constrcuter destructer
	ATime();
	~ATime();

	// delete Function
	ATime(const ATime& _Other) = delete;
	ATime(ATime&& _Other) noexcept = delete;
	ATime& operator=(const ATime& _Other) = delete;
	ATime& operator=(ATime&& _Other) noexcept = delete;

	void SetTextSpriteName(const std::string _Text);

	void SetTextScale(FVector2D _TextScale)
	{
		TextScale = _TextScale;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);

	void SetValue(std::string _time);

	void SetHour(int _Hour);
	int SetMinute(float _DeltaTime);
	int Speed = 1;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	float minutes = 0;
	int hours = 22;
	bool IsPM = false;

	std::string TextSpriteName;
	std::vector<class USpriteRenderer*> Renders;
	FVector2D TextScale;
	class USpriteRenderer* TimeSpriteRenderer = nullptr;
};

