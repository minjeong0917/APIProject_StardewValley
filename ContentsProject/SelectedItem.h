#pragma once

#include "Item.h"
#include "Gold.h"
#include <EngineCore/ImageManager.h>

// Ό³Έν :
class ASelectedItem : public AItem
{
public:
	// constrcuter destructer
	ASelectedItem();
	~ASelectedItem();

	// delete Function
	ASelectedItem(const ASelectedItem& _Other) = delete;
	ASelectedItem(ASelectedItem&& _Other) noexcept = delete;
	ASelectedItem& operator=(const ASelectedItem& _Other) = delete;
	ASelectedItem& operator=(ASelectedItem&& _Other) noexcept = delete;
	void SetSprite(std::string _SprtieName, int _SpriteIndex, float _Scale);

	void SetSelectedItemName(std::string _Name)
	{
		SelectedName= _Name;
	}

	void SetSelectedItemSpriteName(std::string _SpriteName)
	{
		SelectedSpriteName = _SpriteName;
	}

	void SetSelectedItemIndex(int _Index)
	{
		 SelectedIndex = _Index;
	}


	void SetSelectedItemCount(int _Count)
	{
		SelectedItemCount = _Count;
	}

	std::string GetSelectedItemName()
	{
		return SelectedName;
	}

	std::string GetSelectedItemSpriteName()
	{
		return SelectedSpriteName;
	}

	int GetSelectedItemIndex()
	{
		return SelectedIndex;
	}

	int GetSelectedItemCount()
	{
		return SelectedItemCount;
	}

	FVector2D GetSelectedScale()
	{
		return SelectedScale;
	}

	void SetSelectedScale(FVector2D _SelectedScale)
	{
		SelectedScale = _SelectedScale;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	class USpriteRenderer* ItemSpriteRenderer = nullptr;
	std::string SelectedName = "NONE";
	std::string SelectedSpriteName = "NONE";
	FVector2D SelectedScale{ 0,0 };
	int SelectedIndex = 0;
	int SelectedItemCount = 0;
	AGold* Text = nullptr;

};

