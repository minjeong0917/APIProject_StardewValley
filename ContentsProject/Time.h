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

	int GetTimeSpeed()
	{
		return Speed;
	}
	void SetTimeSpeed(int _Speed)
	{
		Speed = _Speed;
	}
	bool AMCheck(int _Hour);
	int WeekCheck(int _Hour);
	int DayCheck(int _Hour);
	void Copy(ATime* _Time);
	void SetHours(int _Hour)
	{
		hours = _Hour;
	}


	void SetWeek(int _Week)
	{
		Week = _Week;
	}
	int GetWeek()
	{
		return Week;
	}

	void SetDay(int _Day)
	{
		Day = _Day;
	}

	int GetDay()
	{
		return Day;
	}
	void SetMinutes(float _Minutes)
	{
		minutes = _Minutes;
	}
	bool IsStop = false;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:

	int Week = 0;
	int Day = 1;
	int Speed = 1;
	float minutes = 0;
	int hours = 6;
	bool IsPM = false;
	int HourInfo = 0;
	std::string TextSpriteName;
	std::vector<class USpriteRenderer*> Renders;
	FVector2D TextScale;
	class USpriteRenderer* TimeSpriteRenderer = nullptr;
};

