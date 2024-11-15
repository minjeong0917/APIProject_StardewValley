#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>

// Ό³Έν :
class AText : public AActor
{
public:
	// constrcuter destructer
	AText();
	~AText();

	// delete Function
	AText(const AText& _Other) = delete;
	AText(AText&& _Other) noexcept = delete;
	AText& operator=(const AText& _Other) = delete;
	AText& operator=(AText&& _Other) noexcept = delete;
	void SetSprite(std::string _SprtieName, int _SpriteIndex, float _Scale);
	void SetValue(int _text);
	void SetOrder(int _Order);
	void SetTextScale(FVector2D _TextScale)
	{
		TextScale = _TextScale;
	}
	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetTextSpriteName(const std::string _Text);


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	class USpriteRenderer* TextSpriteRenderer = nullptr;
	std::vector<class USpriteRenderer*> Renders;
	std::string TextSpriteName;
	FVector2D TextScale;
};

