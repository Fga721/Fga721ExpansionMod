#include "Plant_BombeGranate.h"
#include "ZombieHelper.h"
#include "GridItem.h"
#include "Board.h"
#include <cmath>

typedef void(*BombeGranateUseAction)(PlantFramework*, const SexyString&, const SexyString&);
BombeGranateUseAction oBombeGranateUseAction = nullptr;

void* BombegranateProps::vftable = __null;
Sexy::RtClass* BombegranateProps::s_rtClass = __null;;

void hkBombeGranateUseAction(PlantBombegranate* self, const SexyString& animName, const SexyString& actionName)
{
    auto* props = reinterpret_cast<BombegranateProps*>(self->m_plant->m_propertySheet.Get());

    if (props->GriditemType == "bombegranateseeds")
    {
        return oBombeGranateUseAction(self, animName, actionName);
    }

    if (actionName == "use_action") {
        int spawnPosX = static_cast<int>(std::round((self->m_plant->m_position.x - 540.0f) / GRID_TILE_WIDTH)) + 5;
        int spawnPosY = static_cast<int>(std::round((self->m_plant->m_position.y - 540.0f) / GRID_TILE_HEIGHT)) + 5;

        const SexyString& GIType = props->GriditemType;

        if (props->CanDoDamage == true)
        {
            CallFunc<void, PlantBombegranate*>(0xF31D70, self);
        }

        for (int x = -1; x <= 1; x++) {
            for (int y = 0; y <= 2; y++) {
                if (spawnPosX + x >= 0 && spawnPosX + x < 9)
                {
                    if (spawnPosY - y >= 0 && spawnPosY - y < 5)
                    {
                        if (CanSpawnGridItemAt(spawnPosX + x, spawnPosY - y, false, false))
                        {
                            auto* griditem = AddGridItem(GIType, spawnPosX + x, spawnPosY - y);
                        }
                    }
                }
            }
        }
    }
}

void BombegranateProps::modInit()
{
    LOGI("Initializing BombegranateProps");
    vftable = CopyVFTable(Fga721GetActualOffset(0x237D620), 14);
    PatchVFTable(vftable, (void*)BombegranateProps::StaticGetType, 0);
    BombegranateProps::StaticGetType();

    Fga721HookFunction(0xF31D00, (void*)hkBombeGranateUseAction, (void**)&oBombeGranateUseAction);
}