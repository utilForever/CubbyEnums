# CubbyEnums

A special way to convert string<->enum in C++ using X Macro technique and template specialization

References:
- https://docs.microsoft.com/en-us/cpp/cpp/compiler-limits?view=vs-2017
- https://stackoverflow.com/questions/207976/how-to-easily-map-c-enums-to-strings

## How To Use

1. Create a file for enumerator such as `Fruit.def`.

2. Define enumerators in `X(enumerator)` format.

```C++
X(APPLE)
X(BANANA)
X(ORANGE)
X(MANGO)
X(GRAPE)
X(PEAR)
```

3. Create a header file to declare enumeration and string array.

4. Declare enumeration and string array.

```C++
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
```

5. To provide string<->enum, declare template function `StrToEnum` and `EnumToStr`.

```C++
template <class T>
T StrToEnum(std::string);
template <class T>
std::string EnumToStr(T);
```

6. Define macro for template specialization.

```C++
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
```

7. Define enumeration and string array using macro `ENUM_AND_STR`.

```C++
ENUM_AND_STR(Fruit, FRUIT_STR)
```

8. Finish! Let's try to use it!

```C++
#include "Fruit.hpp"

#include <iostream>

int main()
{
	Fruit fruit = StrToEnum<Fruit>("MANGO");
	std::cout << EnumToStr(fruit) << std::endl;

	fruit = Fruit::APPLE;
	std::cout << EnumToStr(fruit) << std::endl;
	
	return 0;
}
```

## How To Contribute

Contributions are always welcome, either reporting issues/bugs or forking the repository and then issuing pull requests when you have completed some additional coding that you feel will be beneficial to the main project. If you are interested in contributing in a more dedicated capacity, then please contact me.

## Contact

You can contact me via e-mail (utilForever at gmail.com). I am always happy to answer questions or help with any issues you might have, and please be sure to share any additional work or your creations with me, I love seeing what other people are making.

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2019 [Chris Ohk](http://www.github.com/utilForever).

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
