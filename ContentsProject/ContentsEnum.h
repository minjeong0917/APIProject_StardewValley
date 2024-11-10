#pragma once


enum class ERenderOrder
{
	COLMAP = -1001,
	BACKGROUND = -1000,
	PLAYER = 0,
	UI = 10000,
	UIFont = 10001,
	CURSOR = 100000

};

enum class ETileImage
{
	Dirt = 0,
	Tree001,
	End
};

enum class EPlayerDir
{
	Down,
	Left,
	Right,
	Up
};