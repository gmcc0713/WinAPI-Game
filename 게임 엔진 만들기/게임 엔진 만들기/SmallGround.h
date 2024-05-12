#pragma once
#include "Ground.h"
class SmallGround : public Ground
{
private:

public:
	SmallGround();
	virtual void Initialize(float x, float y, int divide = 0) override;

};

