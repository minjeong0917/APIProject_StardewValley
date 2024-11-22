#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SpriteRenderer.h>
// Ό³Έν :
class AGold : public AActor
{
public:
	// constrcuter destructer
	AGold();
	~AGold();

	// delete Function
	AGold(const AGold& _Other) = delete;
	AGold(AGold&& _Other) noexcept = delete;
	AGold& operator=(const AGold& _Other) = delete;
	AGold& operator=(AGold&& _Other) noexcept = delete;

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

	void SetValue(int _Gold);
	void SetText(std::string _Text);

	int GetTextOverCount()
	{
		return TextOverCount;
	}
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::string TextSpriteName;
	USpriteRenderer* Sprite = nullptr;
	FVector2D TextScale;

	int TextOverCount = 0;
	std::vector<class USpriteRenderer*> Renders;
};

