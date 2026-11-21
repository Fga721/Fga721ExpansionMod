#include "Plant_Banana.h"

uintptr_t* hkBananaTargetCursorCtor(uintptr_t a1, uintptr_t a2, uintptr_t a3)
{
    const uintptr_t self = a1;

    CallFunc<void>(0x7608C4, self, a2);

    *reinterpret_cast<uint64_t*>(self + 0x38) = 0;
    *reinterpret_cast<uint64_t*>(self + 0x40) = a3;
    *reinterpret_cast<uintptr_t*>(self) = Fga721GetActualOffset(0x23AA320);

    ResourceDescriptorStorage descriptorInput{};
    {
        SexyString resourceName("POPANIM_EFFECTS_BANANA_RETICLE"); // modify the reticle popanim there
        CallFuncX8<uintptr_t>(0x105CEF0, reinterpret_cast<uintptr_t>(&resourceName), 0, reinterpret_cast<uintptr_t>(&descriptorInput));
    }

    const uintptr_t registry = CallFunc<uintptr_t>(0x14EAD90);

    ResourceDescriptorStorage descriptorResult{};

    CallFuncX8<uintptr_t>(0x14F39CC, registry, reinterpret_cast<uintptr_t>(&descriptorInput), reinterpret_cast<uintptr_t>(&descriptorResult));

    uintptr_t resource = 0;

    if (!CallFunc<uintptr_t>(0x14D926C, &descriptorResult))
    {
        const uint32_t resourceId = CallFunc<uint32_t>(0x14D9178, &descriptorResult);
        const uintptr_t resourceEntry = CallFunc<uintptr_t>(0x14F31A4, registry, resourceId);

        if (resourceEntry)
        {
            resource = CallFunc<uintptr_t>(0x14EDE00, resourceEntry, reinterpret_cast<uintptr_t>(&descriptorResult));
        }
    }

    CallFunc<uintptr_t>(0x14D9154, &descriptorResult);

    const uintptr_t rig = CallFunc<uintptr_t>(0x9D8DAC);
    const uintptr_t animation = CallFunc<uintptr_t>(0x9DA30C, resource, rig);

    SexyString animationName("banana_lock_recticle"); // and the label too

    RawDelegate3 animationDelegate{};
    animationDelegate.vtable = *reinterpret_cast<uintptr_t*>(Fga721GetActualOffset(0x2376668));

    CallFunc<void>(0x9DBEDC, animation, reinterpret_cast<uintptr_t>(&animationName), 0, reinterpret_cast<uintptr_t>(&animationDelegate));
    CallFunc<void>(0x7611D4, self, animation);

    const uintptr_t coordinateObject = *reinterpret_cast<uintptr_t*>(a3 + 8);
    auto* coordinates = reinterpret_cast<int32_t*>(coordinateObject + 0x58);
    auto* flags = reinterpret_cast<uint32_t*>(coordinateObject + 0x68);

    int32_t x;
    int32_t y;
    int32_t width;
    int32_t height;

    if ((*flags & 4) != 0)
    {
        x = coordinates[0];
        y = coordinates[1];
        width = coordinates[2];
        height = coordinates[3];
    }
    else
    {
        const uintptr_t vtable = *reinterpret_cast<uintptr_t*>(coordinateObject);
        const uintptr_t getRect = *reinterpret_cast<uintptr_t*>(vtable + 160);

        Rect rect{};
        CallIndirectX0X8(getRect, coordinateObject, &rect);

        x = rect.mX;
        y = rect.mY;
        width = rect.mWidth;
        height = rect.mHeight;

        coordinates[0] = x;
        coordinates[1] = y;
        *flags |= 4;
        coordinates[2] = width;
        coordinates[3] = height;
    }

    const uintptr_t coordinateManager = *reinterpret_cast<uintptr_t*>(Fga721GetActualOffset(0x25A4618));
    const int32_t inputCoordinates[4] = { x, y, width, height };
    int64_t scaledCoordinates[2]{};

    CallFuncX8<uint64_t>(0x6D0DF0, coordinateManager, reinterpret_cast<uintptr_t>(inputCoordinates), reinterpret_cast<uintptr_t>(scaledCoordinates));
    CallFunc<void>(0x7611DC, self, scaledCoordinates);

    int64_t position[2]{};
    const uintptr_t animationVTable = *reinterpret_cast<uintptr_t*>(animation);
    const uintptr_t getPosition = *reinterpret_cast<uintptr_t*>(animationVTable + 128);

    using GetPositionFn = void (*)(uintptr_t, int64_t*);
    reinterpret_cast<GetPositionFn>(getPosition)(animation, position);

    const auto* position32 = reinterpret_cast<const int32_t*>(position);

    const float centerX = static_cast<float>(position32[0]) + static_cast<float>(position32[2]) * 0.5f;
    const float centerY = static_cast<float>(position32[1]) + static_cast<float>(position32[3]) * 0.5f;

    const float finalX = CallFunc<float>(0x6D0E2C, coordinateManager, centerX);
    *reinterpret_cast<float*>(self + 0x38) = finalX;

    const float finalY = CallFunc<float>(0x6D0E2C, coordinateManager, centerY);
    *reinterpret_cast<float*>(self + 0x3C) = finalY;

    RawDelegate1Plant plantDelegate{};
    plantDelegate.vtable = *reinterpret_cast<uintptr_t*>(Fga721GetActualOffset(0x238E158));
    plantDelegate.callback = Fga721GetActualOffset(0x8ADB88);
    plantDelegate.field10 = 0;
    plantDelegate.self = self;
    plantDelegate.flag = 1;
    plantDelegate.padding = 0;
    plantDelegate.invoker = Fga721GetActualOffset(0x8ADD54);

    const uintptr_t delegateTarget = *reinterpret_cast<uintptr_t*>(Fga721GetActualOffset(0x2513070));

    CallFunc<void>(0x96C4D8, delegateTarget, Fga721GetActualOffset(0x126B934), &plantDelegate);

    return CallFunc<uintptr_t*>(0x14D9154, &descriptorInput);
}

void* hkBananaConstruct()
{
	auto* props = new BananaProps();

	typedef void* (*ctorWithThisPtr)(void*);
	ctorWithThisPtr baseCtor = (ctorWithThisPtr)Fga721GetActualOffset(0x611410);
	baseCtor(props);

	*reinterpret_cast<uintptr_t*>(props) = Fga721GetActualOffset(0x237E798);

	return props;
}

Reflection::CRefManualSymbolBuilder::BuildSymbolsFunc BananaProps::oBananaPropsBuildSymbols = nullptr;

void BananaProps::buildSymbols(Reflection::CRefManualSymbolBuilder* builder, Reflection::RClass* rclass)
{
	if (oBananaPropsBuildSymbols != nullptr)
	{
		oBananaPropsBuildSymbols(builder, rclass);
	}
}

void BananaProps::modInit()
{
	LOGI("Initializing BananaProps");
    Fga721HookFunction(0x8AD820, (void*)hkBananaTargetCursorCtor, nullptr);

	Fga721HookFunction(0x61DAD8, (void*)hkBananaConstruct, nullptr);
	Fga721HookFunction(0x61D70C, (void*)buildSymbols, (void**)&oBananaPropsBuildSymbols);
}