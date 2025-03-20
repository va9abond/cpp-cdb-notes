**Пример 1**
```cpp
namespace B { int x = 0; }
namespace C { int x = 0; }

namespace A {
    using namespace B;

    void foo()
    {
        using C::x;
        A::x = 1; // sets B::x
        x = 2;    // sets C::x
    }
}
```

- `x` *не квалифицированное имя*, его поиск выполняется *изнутри
наружу*
- `A::x` *квалифицированное имя*, его поиск выполняется по
*квалифицированному пространсту имен* (сначала в неймспейсе, а после
изнутри наружу)

**Пример 2**
```cpp
namespace A {
    struct std { struct Cout {}; static Cout cout; };

    void operator << (std::Cout, const char *) {
        ::std::cout << "World\n";
    }
}

int main()
{
    using A::std;
    ::std::cout << "Hello, "; // qualified std -> namespace
    std::cout << "Hello";     // unqualified std -> struct
}
```

В итоге получим именно `"Hello, World\n"`

**Пример 3**
```cpp
namespace N {
    template <typename T> struct Y {};
}
using N::Y;

template class Y<int>;    // GCC OK, clang ERROR
template class N::Y<int>; // both OK
```

- C++11 \[temp.expl.spec\] \[...\] Явная специализация шаблона, чей
`declator-id` не квалифицирован, должна быть объявлена в ближайшем
пространстве имен основного(*primary*) шаблона
- C++17 \[temp.expl.spec\] Явная специализация шаблона может быть
объявлена в любой области, где соответсвующий основной(*primary*)
шаблон может быть объявлен
- `clang` застрял в 2011 году
- **(??)** почему `template class Y<int>` а не `template struct Y<int>`

`clang` хочет, чтобы было так:
```cpp
namespace N {
    template <typename T> struct Y {};
    template struct Y<int> {};
}
```

**Пример 4**
```cpp
namespace N {
    template <typename T> struct Y;
}
using N::Y;

template <typename T> struct Y {};
```

- Вроде бы опять `GCC OK` и `clang ERROR`, но есть нюанс: `clang`
выдает совсем другую ошибку, и он прав. Так делать нельзя

>    ... error: declaration conflicts with target of using declaration
>    already in scope
>        n | template <typename T> struct Y {};

- Т.е. ошибка заключается в том, что я переобъявляю или переопределяю
структуру, которая уже объявлена или определена в этой области
дерективой `using N::Y;`

> Модули разрушают принятое всегда в стандарте тонкое умолчание,
> что процесс поиска имен всегда идет в текущем translation unit

Чеклист практикующего программиста (поиск имен)
- Какие имена и в каких областях видимости мы ищем
- В какой точке начинается поиск имени
- По каким правилам он происходит
- Где поиск имени заканчивается
- Что случается до и после поиска имен



