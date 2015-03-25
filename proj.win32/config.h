#pragma once
const float animationDuration = 0.2;
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
enum AnimalStatus
{
	IDLE,
	WALK,
	RUN,
	ATTACK,
	SKILL,
	HURT,
	DIE,
};

enum AnimalType
{
	PLAYER,
	ENEMY,
	NPC,
	MONSTER,
	BOSS,
};