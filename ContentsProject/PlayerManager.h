#pragma once

// Ό³Έν :
class PlayerManager
{
public:
	// constrcuter destructer
	~PlayerManager();

	// delete Function
	PlayerManager(const PlayerManager& _Other) = delete;
	PlayerManager(PlayerManager&& _Other) noexcept = delete;
	PlayerManager& operator=(const PlayerManager& _Other) = delete;
	PlayerManager& operator=(PlayerManager&& _Other) noexcept = delete;

	static PlayerManager& GetInst()
	{
		static PlayerManager Inst = PlayerManager();
		return Inst;
	}


	int GetGold()
	{
		return PlayerGold;
	}
	void SetGold(int _Value)
	{
		PlayerGold = _Value;
	}


	float GetSpeed()
	{
		return Speed;
	}
	void SetSpeed(float _Speed)
	{
		Speed = _Speed;
	}



protected:

private:
	PlayerManager();

	int PlayerGold = 200;
	float Speed = 220.0f;
};

