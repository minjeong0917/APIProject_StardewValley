#pragma once
#include "SceneComponent.h"

// 설명 :
class U2DCollision : public USceneComponent
{
public:
	// constrcuter destructer
	U2DCollision();
	~U2DCollision();

	// delete Function
	U2DCollision(const U2DCollision& _Other) = delete;
	U2DCollision(U2DCollision&& _Other) noexcept = delete;
	U2DCollision& operator=(const U2DCollision& _Other) = delete;
	U2DCollision& operator=(U2DCollision&& _Other) noexcept = delete;

	void BeginPlay() override;

	void ComponentTick(float _DeltaTime) override;

	template<typename EnumType>
	EnumType GetGroup()
	{
		return static_cast<EnumType>(CollisionGroup);
	}

	int GetGroup()
	{
		return CollisionGroup;
	}

	// 충돌체에게 충돌그룹을 지정안해주는건 의미가 없다.
	// 중간에 충돌 그룹이 바뀌어야 되면 이야기 부탁.
	template<typename EnumType>
	void SetCollisionGroup(EnumType _CollisionGroup)
	{
		SetCollisionGroup(static_cast<int>(_CollisionGroup));
	}

	void SetCollisionGroup(int _CollisionGroup)
	{
		CollisionGroup = _CollisionGroup;
	}

	template<typename EnumType>
	bool IsCollision(EnumType _OtherCollisionGroup)
	{
		return IsCollision(static_cast<int>(_OtherCollisionGroup));
	}

	template<typename EnumType>
	U2DCollision* CollisionOnce(EnumType _OtherCollisionGroup)
	{
		return CollisionOnce(static_cast<int>(_OtherCollisionGroup));
	}

	template<typename EnumType>
	bool Collision(EnumType _OtherCollisionGroup, std::vector<U2DCollision*>* _Result = nullptr)
	{
		return Collision(static_cast<int>(_OtherCollisionGroup), _Result);
	}

	bool IsCollision(int _OtherCollisionGroup);
	U2DCollision* Collision(int _OtherCollisionGroup);
	bool Collision(int _OtherCollisionGroup, std::vector<U2DCollision*>* _Result = nullptr);


protected:

private:
	int CollisionGroup = -1;
};

