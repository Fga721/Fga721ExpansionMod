#pragma once
#include "Zombie.h"

class ZombieWithActionsProps : public ZombiePropertySheet
{
public:
	std::vector<Sexy::RtWeakPtr<Sexy::RtObject>> Actions;
};