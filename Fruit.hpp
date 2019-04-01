#ifndef CUBBY_ENUMS_FRUIT_HPP
#define CUBBY_ENUMS_FRUIT_HPP

#include <string>

enum class Fruit
{
#define X(a) a,
#include "Fruit.def"
#undef X
};

const std::string FRUIT_STR[] = {
#define X(a) #a,
#include "Fruit.def"
#undef X
};

template <class T>
T StrToEnum(std::string);
template <class T>
std::string EnumToStr(T);

#define STR2ENUM(TYPE, ARRAY)                                                \
    template <>                                                              \
    inline TYPE StrToEnum<TYPE>(std::string str)                             \
    {                                                                        \
        for (std::size_t i = 0; i < (sizeof(ARRAY) / sizeof(ARRAY[0])); ++i) \
        {                                                                    \
            if (ARRAY[i] == str)                                             \
            {                                                                \
                return TYPE(i);                                              \
            }                                                                \
        }                                                                    \
                                                                             \
        return TYPE(0);                                                      \
    }

#define ENUM2STR(TYPE, ARRAY)                  \
    template <>                                \
    inline std::string EnumToStr<TYPE>(TYPE v) \
    {                                          \
        return ARRAY[static_cast<int>(v)];     \
    }

#define ENUM_AND_STR(TYPE, ARRAY) \
    STR2ENUM(TYPE, ARRAY)         \
    ENUM2STR(TYPE, ARRAY)

ENUM_AND_STR(Fruit, FRUIT_STR)

#endif