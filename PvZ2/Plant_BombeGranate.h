#pragma once
#include "PlantFramework.h"
#include "Plant.h"
#include "Griditem.h"

class PlantBombegranate : public PlantFramework
{
public:
};

class BombegranateProps : public PlantPropertySheet
{
public:
	SexyString GriditemType = "bombegranateseeds";
	bool CanDoDamage = true;
	static void* vftable;
	static Sexy::RtClass* s_rtClass;
	static void modInit();

	RT_CLASS_CONSTRUCT_FUNCTION_BEGIN(BombegranateProps, 0x611410);
	RT_CLASS_CONSTRUCT_FUNCTION_END();

	RT_CLASS_BUILD_SYMBOLS_BEGIN(PlantPropertySheet);
	RT_CLASS_REGISTER_STRING_PROPERTY(BombegranateProps, GriditemType);
	RT_CLASS_REGISTER_STANDARD_PROPERTY(BombegranateProps, CanDoDamage)
	RT_CLASS_BUILD_SYMBOLS_END();

	RT_CLASS_REGISTER_CLASS_FUNCTION(BombegranateProps);
	RT_CLASS_GET_CLASS_FUNCTION(BombegranateProps, 0x60FCD0);
};

class GridItemBombegranateSeeds : public GridItemAnimation
{
public:
	int m_damage;
	int m_plantLevel;
	int m_plantMasteryLevel;
	char pad_krishna[4];
	Sexy::RtWeakPtr<GameObject> m_parent;
};
static_assert(sizeof(GridItemBombegranateSeeds) == 344);
static_assert(offsetof(GridItemBombegranateSeeds, m_damage) == 320);
static_assert(offsetof(GridItemBombegranateSeeds, m_plantMasteryLevel) == 328);
static_assert(offsetof(GridItemBombegranateSeeds, m_parent) == 336);