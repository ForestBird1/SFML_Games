#pragma once

#include <stdint.h>

struct FInfoProjectile
{
public:
	int32_t speed = 0;

	//발사체의 최대 사정거리입니다. 0인경우 지정된 거리(대체로 화면 밖)만큼 나갑니다
	int32_t range = 0;
};

class SV_Projectile
{
#pragma region Init
public:
	SV_Projectile();
	~SV_Projectile();
private:
	FInfoProjectile _info_proj;

#pragma endregion

};

