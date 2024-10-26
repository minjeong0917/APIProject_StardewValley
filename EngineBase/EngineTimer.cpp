#include "PreCompile.h"
#include "EngineTimer.h"

UEngineTimer::UEngineTimer()
{
	// 현재 성능 카운터 빈도 체크
	QueryPerformanceFrequency(&Count);

	TimeCounter = static_cast<double>(Count.QuadPart);

	QueryPerformanceCounter(&PrevTime);
	QueryPerformanceCounter(&CurTime);

}

UEngineTimer::~UEngineTimer()
{
}

// 타이머 시작(PrevTime)부터 현재 시간(CurTime)까지의 시간 체크 함수
void UEngineTimer::TimeCheck()
{
	QueryPerformanceCounter(&CurTime);
	double Tick = static_cast<double>(CurTime.QuadPart - PrevTime.QuadPart);
	
	// DetaTime = ( 현재 시간 - 시작 시간 ) / 초당 카운터 수
	DeltaTime = Tick / TimeCounter;

	// float형 DeltaTime
	fDeltaTime = static_cast<float>(DeltaTime);

	PrevTime.QuadPart = CurTime.QuadPart;
}

// 타이머 시작
void UEngineTimer::TimeStart()
{
	QueryPerformanceCounter(&PrevTime);
}

// 시간 체크 후 float형 DeltaTime 값 반환하도록 하는 함수 실행
float UEngineTimer::End()
{
	TimeCheck();
	return GetDeltaTime();
}

// 시간 체크 후 Double형 DeltaTime 값 반환하도록 하는 함수 실행
double UEngineTimer::DEnd()
{
	TimeCheck();
	return GetDoubleDeltaTime();
}
