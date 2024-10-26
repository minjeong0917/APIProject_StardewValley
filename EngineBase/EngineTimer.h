#pragma once
#include <Windows.h>

class UEngineTimer
{
public:
	// constrcuter destructer
	UEngineTimer();
	~UEngineTimer();

	// delete Function
	UEngineTimer(const UEngineTimer& _Other) = delete;
	UEngineTimer(UEngineTimer&& _Other) noexcept = delete;
	UEngineTimer& operator=(const UEngineTimer& _Other) = delete;
	UEngineTimer& operator=(UEngineTimer&& _Other) noexcept = delete;

	// float형 DeltaRime값 반환
	float GetDeltaTime()
	{
		return fDeltaTime;
	}

	// double형 DeltaTime값 반환
	double GetDoubleDeltaTime()
	{
		return DeltaTime;
	}

	void TimeCheck();
	void TimeStart();
	float End();
	double DEnd();

protected:

private:
	LARGE_INTEGER Count = LARGE_INTEGER(); 
	LARGE_INTEGER PrevTime = LARGE_INTEGER();
	LARGE_INTEGER CurTime = LARGE_INTEGER();

	double TimeCounter = 0.0f;
	double DeltaTime = 0.0;
	float fDeltaTime = 0.0f;
};