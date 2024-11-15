#include "PreCompile.h"

#include "Time.h"
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"
#include <EngineBase/EngineTimer.h>
#include <EnginePlatform/EngineInput.h>

ATime::ATime()
{
	for (size_t i = 0; i < 10; i++)
	{
		USpriteRenderer* Sprite = CreateDefaultSubObject<USpriteRenderer>();
		Sprite->SetCameraEffect(false);
		Renders.push_back(Sprite);
	}
	minutes = 0.0;
}

ATime::~ATime()
{

}

void ATime::SetTextSpriteName(const std::string _Text)
{
	TextSpriteName = _Text;

	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetSprite(TextSpriteName);
	}

}

void ATime::BeginPlay()
{
	Super::BeginPlay();

	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	SetOrder(ERenderOrder::UIFont);
	SetTextScale({ 20, 26 });

}

void ATime::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == UEngineInput::GetInst().IsDown('P'))
	{
		Speed += 100;
	}
	else if (true == UEngineInput::GetInst().IsDown('M'))
	{
		if (Speed > 1)
		{
			Speed -= 100;
		}
	}
}

void ATime::SetOrder(int _Order)
{
	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetOrder(_Order);
	}
}

void ATime::SetValue(std::string _Time)
{
	if (Renders.size() <= _Time.size())
	{
		MSGASSERT("자리수를 넘겼습니다.");
		return;
	}

	FVector2D Pos = FVector2D::ZERO;

	for (size_t i = _Time.size(); i > 0; i--)
	{
		char Value = _Time[i - 1] - '0';
		Renders[i - 1]->SetSprite(TextSpriteName, Value);
		Renders[i - 1]->SetComponentScale(TextScale);
		Renders[i - 1]->SetComponentLocation(Pos);
		Pos.X -= TextScale.X;
		Renders[i - 1]->SetActive(true);
	}

	for (size_t i = _Time.size(); i < Renders.size(); i++)
	{
		Renders[i]->SetActive(false);
	}
}


int ATime::SetMinute(float _DeltaTime)
{
	minutes += _DeltaTime * Speed;
	int Min = static_cast<int>(minutes / 60) * 10;  

	std::string Number = std::to_string(Min);

	if (Min < 10)
	{
		Number = '0' + std::to_string(Min);
	}

	SetValue(Number);

	if (Min >= 60)
	{
		Min = 0;
		minutes = 0;
		++hours;

		return hours;
	}
	if (26 <= hours)
	{
		hours = 6;
	}
	return hours;
}

void ATime::SetHour(int _Hour)
{
	int Hour = 0;
	if (_Hour >= 6 && _Hour <= 12)
	{
		Hour = _Hour;
	}
	else if (_Hour > 12 && _Hour < 24)
	{
		Hour = _Hour - 12;
	}
	else if (_Hour >= 24 && _Hour < 26)
	{
		Hour = _Hour - 24;
	}

	std::string Number = std::to_string(Hour);
	SetValue(Number);
}

bool ATime::AMCheck(int _Hour)
{
	if (_Hour >= 6 && _Hour < 12)
	{
		return true;
	}
	else if (_Hour >= 12 && _Hour < 24)
	{
		return false;
	}
	else if (_Hour >= 24 && _Hour < 26)
	{
		return true;
	}
}

int ATime::WeekCheck(int _Hour)
{

	if (_Hour >= 26)
	{
		if (Week >= 6)
		{
			Week = 0;
			return Week;
		}

		 ++Week;
		 return Week;
	}
	 return Week;
}

int ATime::DayCheck(int _Hour)
{
	if (_Hour >= 26)
	{
		if (Day >= 30)
		{
			Day = 1;
			return Day;
		}
		++Day;
		return Day;
	}
	return Day;
}
