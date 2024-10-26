#include "PreCompile.h"
#include "EngineTimer.h"

UEngineTimer::UEngineTimer()
{
	// ���� ���� ī���� �� üũ
	QueryPerformanceFrequency(&Count);

	TimeCounter = static_cast<double>(Count.QuadPart);

	QueryPerformanceCounter(&PrevTime);
	QueryPerformanceCounter(&CurTime);

}

UEngineTimer::~UEngineTimer()
{
}

// Ÿ�̸� ����(PrevTime)���� ���� �ð�(CurTime)������ �ð� üũ �Լ�
void UEngineTimer::TimeCheck()
{
	QueryPerformanceCounter(&CurTime);
	double Tick = static_cast<double>(CurTime.QuadPart - PrevTime.QuadPart);
	
	// DetaTime = ( ���� �ð� - ���� �ð� ) / �ʴ� ī���� ��
	DeltaTime = Tick / TimeCounter;

	// float�� DeltaTime
	fDeltaTime = static_cast<float>(DeltaTime);

	PrevTime.QuadPart = CurTime.QuadPart;
}

// Ÿ�̸� ����
void UEngineTimer::TimeStart()
{
	QueryPerformanceCounter(&PrevTime);
}

// �ð� üũ �� float�� DeltaTime �� ��ȯ�ϵ��� �ϴ� �Լ� ����
float UEngineTimer::End()
{
	TimeCheck();
	return GetDeltaTime();
}

// �ð� üũ �� Double�� DeltaTime �� ��ȯ�ϵ��� �ϴ� �Լ� ����
double UEngineTimer::DEnd()
{
	TimeCheck();
	return GetDoubleDeltaTime();
}
