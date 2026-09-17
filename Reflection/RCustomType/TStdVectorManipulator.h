#pragma once

#include <vector>
#include <cstdint>

#include "Sexy/RtWeakPtr.h"
#include "Reflection/RType.h"

namespace Reflection::RCustomType
{
    struct UnkStruct
    {
    public:
        int m_unk1;
        int m_unk2;
        int m_unk3;
        int m_unk4;
        Sexy::RtWeakPtr<void>* m_weakPtrPtr;
    };

    struct VectorManipulatorStruct
    {
    public:
        UnkStruct* m_unkPtr;
        void* m_unkPtr2;
        bool m_unkBool;
    };

    template <typename T>
    class TStdVectorManipulator
    {
    public:
        using GenericVector = std::vector<T>;

        virtual void NullSub() {}

        void DestroyEffect(void* a1)
        {
            operator delete(a1);
        }

        bool UnkFunc(
            UnkStruct* a1,
            Sexy::RtWeakPtr<void>* a2,
            int* vecSize)
        {
            *vecSize = 0;

            using Func2 = int64_t(*)(UnkStruct*, void*);
            Func2 pFunc2 =
                (Func2)Fga721GetActualOffset(0x5B2AA4);

            uint64_t v10 = pFunc2(a1, a2);

            using Func3 = int64_t(*)(UnkStruct*, int64_t);
            Func3 pFunc3 =
                (Func3)Fga721GetActualOffset(0x14FEDCC);

            if (v10 && pFunc3(a1, v10) != 0)
            {
                using Func4 = int64_t(*)(UnkStruct*, int64_t);
                Func4 pFunc4 =
                    (Func4)Fga721GetActualOffset(0x14FEE04);

                *vecSize = static_cast<int>(pFunc4(a1, v10));
            }
            else
            {
                return false;
            }

            return true;
        }

        virtual bool Edit(
            GenericVector* vector,
            VectorManipulatorStruct* manipInfo,
            Sexy::RtWeakPtr<void>* unkWeakPtr,
            RType* reflectionType)
        {
            if (manipInfo->m_unkBool)
            {
                int vecSize = 0;

                if (UnkFunc(
                    manipInfo->m_unkPtr,
                    unkWeakPtr,
                    &vecSize))
                {
                    if (vecSize > 0)
                    {
                        vector->resize(vecSize);

                        for (int i = 0; i < vecSize; ++i)
                        {
                            T* element = &vector->at(i);

                            SexyString str;

                            reflectionType->Function11(
                                element,
                                manipInfo,
                                str);
                        }
                    }
                    manipInfo->m_unkPtr->m_weakPtrPtr--;

                    return true;
                }

                return false;
            }
            else
            {
                int** v19 =
                    *(int***)((int*)manipInfo + 4);

                using Sub262EC0 =
                    void(*)(int**, Sexy::RtWeakPtr<void>*, int, char);

                ((Sub262EC0)Fga721GetActualOffset(0x5B2440))(
                    v19,
                    unkWeakPtr,
                    static_cast<int>(vector->size()),
                    0xFD);

                if (!vector->empty())
                {
                    for (int i = 0;
                        i < static_cast<int>(vector->size());
                        ++i)
                    {
                        T* element = &vector->at(i);

                        SexyString str;

                        reflectionType->Function11(
                            element,
                            manipInfo,
                            str);
                    }
                }

                int* v17 = *v19;

                v19[2] =
                    (int*)((char*)v19[2] - 1);

                uint8_t v21 = 254;

                using Sub10D2100 =
                    int(*)(int*, uint8_t*, int);

                ((Sub10D2100)Fga721GetActualOffset(0x14F8794))(
                    v17,
                    &v21,
                    1);

                return true;
            }
        }

        int GetSize(GenericVector* vector)
        {
            return static_cast<int>(vector->size());
        }
    };
}