#pragma once
#include "BoardEntity.h"
#include "PropertySheetBase.h"
#include "StringRestrictionSet.h"
#include "ObjectTypeDescriptor.h"
#include <vector>
#include <cstdint>

class GridItemType;
class GridItemPropertySheet;

class GridItem : public BoardEntity
{
public:
	//GridItemConditionTracker m_conditionTracker;
	char m_pad5[144];
	Sexy::RtWeakPtr<GridItemType> m_type;
	float m_health;
	float m_healthMax;
	Sexy::Point m_gridLocation;
	Sexy::RtWeakPtr<GridItemPropertySheet> m_propertySheet;

	static GridItem* SpawnGridItemAt(const SexyString& gridItemName, int gridPosX, int gridPosY)
	{
		typedef GridItem* (*funcAA230C)(Board*, SexyString, int, int);
		funcAA230C func_AA230C = (funcAA230C)Fga721GetActualOffset(0xAA230C);
		return func_AA230C(Board::GetBoard(), gridItemName, gridPosX, gridPosY);
	}
};

static_assert(sizeof(GridItem) == 304);
static_assert(offsetof(GridItem, m_pad5) == 128);
static_assert(offsetof(GridItem, m_type) == 272);
static_assert(offsetof(GridItem, m_gridLocation) == 288);

class GridItemPropertySheet : public PropertySheetBase
{
public:
	float Hitpoints = 1000.0f;
	float HitRectOffsetX;
	float HitRectOffsetWidth;
	BoardEntityHeight Height = BoardEntityHeight::normal;
	bool CanBeMowed;
	PlantingRestrictionSet PlantingRestrictions;
	GridItemRestrictionSet GridItemsOverride;
};

static_assert(sizeof(GridItemPropertySheet) == 152);
static_assert(offsetof(GridItemPropertySheet, Hitpoints) == 40);
static_assert(offsetof(GridItemPropertySheet, CanBeMowed) == 56);
static_assert(offsetof(GridItemPropertySheet, PlantingRestrictions) == 64);
static_assert(offsetof(GridItemPropertySheet, GridItemsOverride) == 112);

class GridItemType : public ObjectTypeDescriptor
{
public:
	SexyString GridItemClass;
	std::vector<SexyString> ResourceGroups;
	std::vector<SexyString> AudioGroups;
	Sexy::RtWeakPtr<GridItemPropertySheet> Properties;
	char m_pad[8];
};

static_assert(sizeof(GridItemType) == 120);
static_assert(offsetof(GridItemType, GridItemClass) == 32);