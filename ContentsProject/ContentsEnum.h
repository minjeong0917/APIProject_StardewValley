#pragma once


enum class ERenderOrder
{
	COLMAP = -1001,
	BACKGROUND = -1000,
	PLAYER = 0,
	UI = 10000,
	UIFont = 10001,
	INVEN = 20000,
	SLOT = 20001,
	SLOTITEM = 20002,
	CURSLOT = 20003,
	SLOTFont = 20004,
	SelectedItem = 20004,
	CURSOR = 100000

};

enum class ETileImage
{
	Dirt = 0,
	Tree001,
	Crops,
	End
};

enum class EPlayerDir
{
	Down,
	Left,
	Right,
	Up
};

enum class ECollisionGroup
{
	CURSOR,
	SLOT,

};

enum class EItemType
{
	Crop,
	Wood,
	DUPivot,
	EmptySlot,
	Tools,
};