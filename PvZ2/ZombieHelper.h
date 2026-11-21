#pragma once
#include "Zombie.h"
#include "Plant.h"
#include "SexyTypes.h"
#include "ZombieAnimRig.h"
#include "Board.h"
#include "ResourceManager.h"

// Zombie Helper Function Start Here

inline void* GetZombieTypeDirectory() {
	return *(void**)Fga721GetActualOffset(0x256A620);
};

inline void GetZombieType(Sexy::RtWeakPtr<uintptr_t>* a1, void* a2, SexyString* a3) {
	typedef uintptr_t(*getZombieType)(uintptr_t, SexyString*);
	getZombieType getZBType = (getZombieType)Fga721GetActualOffset(0x5E5924);
	uintptr_t getZomType = getZBType((uintptr_t)a2 + 8, a3);
	if ((uintptr_t)a2 + 16 != getZomType)
	{
		uintptr_t result = getZomType + 56;
		return a1->FromOther((Sexy::RtWeakPtr<uintptr_t>*)result);
	}
};
inline Zombie* AddZombie(SexyString type, int a3, char a4, int a5) {
	void* zTypeDirectory = GetZombieTypeDirectory();
	Board* board = Board::GetBoard();
	Sexy::RtWeakPtr<uintptr_t> zPtr;
	GetZombieType(&zPtr, zTypeDirectory, &type);
	typedef Zombie* (*addZombieByType)(Board*, Sexy::RtWeakPtr<uintptr_t>*, int, char, int);
	addZombieByType funAddZombieByType = (addZombieByType)Fga721GetActualOffset(0xAAE9F0);
	return funAddZombieByType(board, &zPtr, a3, a4, a5);
}

inline float ZombieFacing(Zombie* zombie) {
	if (!zombie->m_facing) {
		return 1.0f;
	}
	return -1.0f;
}

inline void ZombieEnterState(Zombie* zombie, int state, int a3) {
	CallFunc<void, Zombie*, int, int>(0xC3D428, zombie, state, a3);
}

inline bool ZombieIsDeadOrDying(Zombie* zombie) {
	return CallFunc<bool, Zombie*>(0xC3E204, zombie);
}

inline Zombie* ZombieAllowMovement(Zombie* zombie, bool isAllowed) {
	return CallFunc<Zombie*, Zombie*, bool>(0xC51F94, zombie, isAllowed);
}

inline Zombie* ZombieSetNoCollisionFlag(Zombie* zombie, bool isAllowed) {
	return CallFunc<Zombie*, Zombie*, bool>(0xC4C828, zombie, isAllowed);
}

inline Zombie* ZombieSetInvincibleStatusFlag(Zombie* zombie, bool isAllowed) {
	return CallFunc<Zombie*, Zombie*, bool>(0xC3CDC4, zombie, isAllowed);
}

inline Zombie* ZombieSetGrabbedByPtero(Zombie* zombie, bool isAllowed) {
	return CallFunc<Zombie*, Zombie*, bool>(0xC4C80C, zombie, isAllowed);
}

inline Zombie* ZombieSetUnmovableStatusFlag(Zombie* zombie, bool isAllowed) {
	return CallFunc<Zombie*, Zombie*, bool>(0xC4BBB4, zombie, isAllowed);
}

inline Zombie* ZombieFlippedAnim(Zombie* zombie, bool isFlipped) {
	return CallFunc<Zombie*, Zombie*, bool>(0xC41290, zombie, isFlipped);
}

inline void ZombieIsFlying(Zombie* zombie, bool isFlying) {
	CallFunc<void, Zombie*, bool>(0xC4C770, zombie, isFlying);
}

inline Zombie* ZombieUpdatePosition(Zombie* zombie, Sexy::SexyVector3* newPos) {
	return CallFunc<Zombie*, Zombie*, Sexy::SexyVector3*>(0x628278, zombie, newPos);
}

inline int ZombieSetPosition(Zombie* zombie, Sexy::SexyVector3* newPos) {
	return CallFunc<int, Zombie*, Sexy::SexyVector3*>(0x628058, zombie, newPos);
}

inline Zombie* ZombieAttachEffect(Zombie* zombie,
	const char* keyValue,
	const char* popAnimName,
	const char* labelName,
	Sexy::SexyVector3 effectPos,
	int renderLayer,
	bool playOnce,
	bool a8,
	int a9) {
	return CallFunc<Zombie*>(0x7BF03C,
		zombie,
		keyValue,
		popAnimName,
		labelName,
		&effectPos,
		renderLayer,
		playOnce,
		a8,
		a9);
}

inline int MakeRenderOrder(int a1, int a2, int a3) {
	return a1 + a3 + 10000 * a2;
}

inline void ZombieOnSpawn(Zombie* zombie) {
	CallFunc<void, Zombie*>(0xC3D1F0, zombie);
}

inline void ZombiePlaySoundEvent(RealObject* zombie, const SexyString& eventName, float delayDuration) {
	CallFunc<void*, RealObject*, const SexyString&, float>(0x10B0608, zombie, eventName, delayDuration);
}

inline void ZombieSetCondition(Zombie* zombie, int conditionID, int a3, float duration, float a5) {
	CallFunc<void, Zombie*, int, int, float, float>(0xC40CC0, zombie, conditionID, a3, duration, a5);
}

inline void ZombieRemoveCondition(Zombie* zombie, int conditionID) {
	CallFunc<void, Zombie*, int>(0xC420D0, zombie, conditionID);
}

inline void ZombieSetSpeedScale(Zombie* zombie, float scale) {
	CallFunc<void, Zombie*, float>(0xC484C0, zombie, scale);
}

inline bool ZombieHasCondition(Zombie* zombie, int condition) {
	return CallFunc<bool, Zombie*, int>(0xC3E44C, zombie, condition);
}

inline bool ZombieHasArmor(Zombie* zombie, const SexyString& armorName) {
	return CallFunc<bool, Zombie*, const SexyString&>(0xC3F2E4, zombie, armorName);
}

inline void ZombieApplyArmor(Zombie* zombie, const SexyString& armorName) {
	CallFunc<void, Zombie*, const SexyString&>(0xC3EE98, zombie, armorName);
}

// Zombie Anim Rig Helper Function Start From Here

inline bool SetAnimLayerVisible(PopAnimRig* animRig, const SexyString& layerName, bool visible) {
	return CallFunc<bool, PopAnimRig*, const SexyString&, bool>(0x9DB8D0, animRig, layerName, visible);
}

inline bool GetAnimRigSpritePosition(PopAnimRig* animRig, const SexyString& layerName, Sexy::SexyVector2* spritePos) {
	return CallFunc<bool, PopAnimRig*, const SexyString&, Sexy::SexyVector2*>(0x9DFBD4, animRig, layerName, spritePos);
}

inline bool GetAnimRigSpriteRect(PopAnimRig* animRig, const SexyString& layerName, Sexy::Rect* spriteRect) {
	return CallFunc<bool, PopAnimRig*, const SexyString&, Sexy::Rect*>(0x9E02A8, animRig, layerName, spriteRect);
}

inline bool IsAnimDone(PopAnimRig* animRig, int duration) {
	return CallFunc<bool, PopAnimRig*, int>(0x9DCBE8, animRig, duration);
}

inline void SetWalkSpeed(ZombieAnimRig* animRig, float speed) {
	return CallFunc<void, ZombieAnimRig*, float>(0x8DDAA4, animRig, speed);
}

// Find target in rect start here

inline void GetEntitiesInRectGrid(std::vector<BoardEntity*>* entities, uint typeID, Sexy::Rect* area) {
	CallFunc<void, std::vector<BoardEntity*>*, uint, Sexy::Rect*>(0x86F180, entities, typeID, area);
}

inline void GetEntitiesInRectPixel(std::vector<BoardEntity*>* entities, uint typeID, Sexy::Rect* area, int minRow, int maxRow) {
	CallFunc<void, std::vector<BoardEntity*>*, uint, Sexy::Rect*, int, int>(0x86F340, entities, typeID, area, minRow, maxRow);
}

inline void GetEntitiesInGridSquare(std::vector<BoardEntity*>& entities, uint typeID, Zombie* zombie) {
	int gX = static_cast<int>((zombie->m_position.x - 200.0f) / 64.0f);
	int gY = static_cast<int>((zombie->m_position.y - 160.0f) / 76.0f);

	Sexy::Rect scanRect;
	scanRect.mX = gX;
	scanRect.mY = gY;
	scanRect.mWidth = 1;
	scanRect.mHeight = 1;
	GetEntitiesInRectGrid(&entities, typeID, &scanRect);
}

// Plant helper start here

inline void PlantSetCondition(PlantGroup* plant, int conditionID, float duration, float a4) {
	CallFunc<void, PlantGroup*, int, float, float>(0x13399F8, plant, conditionID, duration, a4);
}

inline void* GetDefaultPlantSpawnArgs() {
	return (void*)Fga721GetActualOffset(0x2513080);
};

class BoardPlanting {
public:
	virtual void Function1() {};
	virtual void Function2() {};
};

inline BoardPlanting* GetBoardPlantingInstance()
{
	typedef BoardPlanting* (*getBoardPlanting)(BoardPlanting*);
	getBoardPlanting GetBoardPlanting = (getBoardPlanting)Fga721GetActualOffset(0x9B9A50);
	BoardPlanting* boardPtr = *(BoardPlanting**)Fga721GetActualOffset(0x256AD20);
	if (!boardPtr) {
		boardPtr = new BoardPlanting;
		GetBoardPlanting(boardPtr);
		return boardPtr;
	}
	return boardPtr;
}
inline Plant* AddPlant(SexyString type, int column, int row) {
	void* a5 = GetDefaultPlantSpawnArgs();
	BoardPlanting* board = GetBoardPlantingInstance();
	typedef Plant* (*addPlantByType)(BoardPlanting*, int, int, SexyString*, void*);
	addPlantByType funAddPlantByType = (addPlantByType)Fga721GetActualOffset(0x9BB46C);
	return funAddPlantByType(board, column, row, &type, a5);
}

// griditem, collectable and projectiles helper starts here

inline GridItem* AddGridItem(SexyString type, int gridX, int gridY) {
	Board* board = Board::GetBoard();
	typedef GridItem* (*addGridItemByType)(Board*, SexyString, int, int);
	addGridItemByType funAddGridItemByType = (addGridItemByType)Fga721GetActualOffset(0xAA230C);
	return funAddGridItemByType(board, type, gridX, gridY);
}

inline bool CanSpawnGridItemAt(int col, int row, bool displacePlant, bool canAddOnMold) {
	Board* board = Board::GetBoard();
	typedef bool (*addGridItemByType)(Board*, int, int, bool, bool);
	addGridItemByType funAddGridItemByType = (addGridItemByType)Fga721GetActualOffset(0xAA2D10);
	return funAddGridItemByType(board, col, row, displacePlant, canAddOnMold);
}

inline void SpawnCollectable(SexyString CollectableType, Sexy::SexyVector3 spawnPos)
{
	CallFunc<void, Board*, SexyString, Sexy::SexyVector3*>(0xAA4180, Board::GetBoard(), CollectableType, &spawnPos);
}

inline Projectile* AddProjectile(Sexy::RtWeakPtr<ProjectilePropertySheet>* type, BoardEntity* owner, float mX, float mY, float mZ) {
	Board* board = Board::GetBoard();
	typedef Projectile* (*addProjectileByType)(Board*, Sexy::RtWeakPtr<ProjectilePropertySheet>*, BoardEntity*, float, float, float);
	addProjectileByType funAddProjectileByType = (addProjectileByType)Fga721GetActualOffset(0xAAE5B4);
	return funAddProjectileByType(board, type, owner, mX, mY, mZ);
}
inline float FirePultProjectile(Projectile* proj, SexyVector3 targetPos, float projHeight, float projAirTime) {
	return CallFunc<float, Projectile*, SexyVector3*, float, float>(0xCA2D50, proj, &targetPos, projHeight, projAirTime);
}