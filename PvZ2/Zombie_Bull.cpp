#include "Zombie_Bull.h"
#include "ZombieHelper.h"
#include "Board.h"

typedef void(*zombieBullHideLayer)(ZombieBull*, ZombieAnimRig_Bull*);
zombieBullHideLayer oZombieBullHideLayer = nullptr;

void HideCustomRiderLayer(ZombieBull* self, ZombieAnimRig_Bull* animRig) {

    auto* props = reinterpret_cast<ZombieBullProps*>(self->m_propertySheet.Get());

    if (!props) {
        return oZombieBullHideLayer(self, animRig);
    }

    std::vector<SexyString> HardcodedLayer = {
         "zombie_cowboy_hat_back",
         "zombie_cowboy_hat_front",
         "zombie_imp_arm_inner_lower",
         "zombie_imp_arm_inner_upper",
         "zombie_imp_arm_outer_lower",
         "zombie_imp_arm_outer_upper_01",
         "zombie_imp_arm_outer_upper_02",
         "zombie_imp_arms_outer_upper",
         "zombie_imp_eye",
         "zombie_imp_eye_sm",
         "zombie_imp_hand_inner",
         "zombie_imp_hand_outer",
         "zombie_imp_jaw",
         "zombie_imp_leg_inner_lower",
         "zombie_imp_leg_inner_upper",
         "zombie_imp_leg_outer_lower",
         "zombie_imp_leg_outer_upper",
         "zombie_imp_pupil",
         "zombie_imp_skull",
         "zombie_imp_toe_inner",
         "zombie_imp_toe_outer",
         "zombie_imp_torso",
         "zombie_imp_waist",
         "zombie_imp_leg_outer_upper",
         "_zombie_imp_head_top"
    };

    if (!props->RiderLayerToHide.empty()) {
        for (size_t i = 0; i < props->RiderLayerToHide.size(); i++) {
            const auto& layerStr = props->RiderLayerToHide[i];
            SexyString layerName(layerStr);
            SetAnimLayerVisible(animRig, layerName, false);
        }
    }
    else {
        for (size_t i = 0; i < HardcodedLayer.size(); i++) {
            const auto& layerStr = HardcodedLayer[i];
            SexyString layerName(layerStr);
            SetAnimLayerVisible(animRig, layerName, false);
        }
    }

}

typedef void(*zombieBullThrowRider)(ZombieBull*, int);
zombieBullThrowRider oZombieBullThrowRider = nullptr;


void hkZombieBullThrowRider(ZombieBull* self, int a2)
{
    if (!self) return;

    auto* props = reinterpret_cast<ZombieBullProps*>(self->m_propertySheet.Get());
    if (!props) {
        return oZombieBullThrowRider(self, a2);
    }

    SexyString name = props->RiderType;
    float distance = props->LaunchDistance;

    float launchApex = props->LaunchHeight;
    float launchTime = props->LaunchAirTime;

    if (name.empty()) {
        name = "west_bullrider";
    }

    if (!self->m_hasLaunched && !ZombieHasCondition(self, zombie_condition_shrinking) && !ZombieHasCondition(self, zombie_condition_shrunken))
    {
        auto* rig = reinterpret_cast<ZombieAnimRig_Bull*>(self->m_animRig.Get());
        HideCustomRiderLayer(self, rig);
        ZombieImp* spawnedRider = (ZombieImp*)AddZombie(name, -1, 6, -1);

        if (!spawnedRider) return;

        spawnedRider->m_getsUpFromLanding = props->UseGetUpAnim;

        SexyVector3 newCoords = SexyVector3(self->m_position.x, self->m_position.y, self->m_position.z);
        ZombieSetPosition(spawnedRider, &newCoords);

        typedef void (*ZombieThrowVirtual)(Zombie*, int, float, float, float, float, float);
        uintptr_t* vtable = *(uintptr_t**)spawnedRider;
        ZombieThrowVirtual virtualThrow = (ZombieThrowVirtual)(vtable[206]);

        float targetX, targetY, targetZ;

        if (ZombieHasCondition(self, zombie_condition_hypnotized)) {
            ZombieSetCondition(spawnedRider, zombie_condition_hypnotized, 0, 3.4028e38f, 0.0f);

            int teamflag = self->m_teamFlags;
            typedef void (*func10B013C)(Zombie*, int);
            auto* setTeamFlag = ((func10B013C)Fga721GetActualOffset(0x10B013C));
            setTeamFlag(spawnedRider, teamflag);

            typedef void* (*GetHypnoDataFunc)(Zombie*);
            GetHypnoDataFunc funGetHypnoData = (GetHypnoDataFunc)Fga721GetActualOffset(0xC3E6DC);
            void* hypnoData = funGetHypnoData(self);

            typedef void (*ApplyHypnoDataFunc)(Zombie*, void*);
            ApplyHypnoDataFunc funApplyHypnoData = (ApplyHypnoDataFunc)Fga721GetActualOffset(0xC41290);
            funApplyHypnoData(spawnedRider, hypnoData);

            targetX = self->m_position.x + distance;
            targetY = self->m_position.y;
            targetZ = self->m_position.z;

            if (targetX > 776.0f) {
                targetX = 776.0f;
            }
        }
        else {
            targetX = self->m_position.x - distance;
            targetY = self->m_position.y;
            targetZ = self->m_position.z;

            if (targetX < 232.0f) {
                targetX = 232.0f;
            }
        }
        virtualThrow(spawnedRider, 0, targetX, targetY, targetZ, launchTime, launchApex);

        self->m_hasLaunched = true;
    }
    else {
        LOGI("Already shrinking, shrunken or being thrown");
    }
}


void hkZombieBullPlayDeath(ZombieBull* self) {

    typedef void(*zombieFun197)(ZombieBull*);
    ((zombieFun197)Fga721GetActualOffset(0xC51A40))(self);
}

void* ZombieBullConstruct()
{
	auto* props = new ZombieBullProps();

	typedef void* (*ctorWithThisPtr)(void*);
	ctorWithThisPtr baseCtor = (ctorWithThisPtr)Fga721GetActualOffset(0xC136A4);
	baseCtor(props);

	*reinterpret_cast<int*>(uintptr_t(props)) = Fga721GetActualOffset(0x2432FA8);
	return props;
}

Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc ZombieBullProps::oZombieBullPropsBuildSymbols = nullptr;

void ZombieBullProps::buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass)
{
	oZombieBullPropsBuildSymbols(builder, rclass);
	RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieBullProps, BullRunAgainDelay);
	RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieBullProps, BullRammingDamage);
    RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieBullProps, LaunchHeight);
    RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieBullProps, LaunchAirTime);
	RT_CLASS_REGISTER_STRING_PROPERTY(ZombieBullProps, RiderType);
	RT_CLASS_REGISTER_STRING_VECTOR_PROPERTY(ZombieBullProps, RiderLayerToHide);
	RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieBullProps, LaunchDistance);
    RT_CLASS_REGISTER_STANDARD_PROPERTY(ZombieBullProps, UseGetUpAnim);
};

void ZombieBullProps::modInit()
{
	LOGI("Initializing ZombieBullProps");
    Fga721HookFunction(0xAE541C, (void*)HideCustomRiderLayer, (void**)&oZombieBullHideLayer);
    Fga721HookFunction(0xAE4FF8, (void*)hkZombieBullThrowRider, (void**)&oZombieBullThrowRider);
    Fga721HookFunction(0xAE3A64, (void*)hkZombieBullPlayDeath, nullptr);

	Fga721HookFunction(0xDAE1B0, (void*)ZombieBullConstruct, nullptr);
	Fga721HookFunction(0xDAE2F4, (void*)buildSymbols, (void**)&oZombieBullPropsBuildSymbols);
}
