#pragma once

#include <stdint.h>

struct FInfoProjectile
{
public:
	int32_t speed = 0;

	//�߻�ü�� �ִ� �����Ÿ��Դϴ�. 0�ΰ�� ������ �Ÿ�(��ü�� ȭ�� ��)��ŭ �����ϴ�
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

