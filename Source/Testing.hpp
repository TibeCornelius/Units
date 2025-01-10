#include <type_traits>

struct T1
{
    double Value;
};
/*struct TT1
{
    double Value;
};*/
/*struct TT2
{
    double Value;
};*/
struct T2
{
    double Value;
};
struct T3
{
    double Value;
};
/*struct TT3
{
    double Value;
};*/


template <typename Unit1, typename Unit2>
struct TResultingUnit;

template<>
struct TResultingUnit<T1,T2>
{
    using type = T3;
};


template <>
struct TResultingUnit<T1,T3>
{
    using type = T2;
};

template <>
struct TResultingUnit<T2,T3>
{
    using type = T1;
};

template<typename Unit1, typename Unit2>
struct TV
{
    Unit1 x;
    Unit2 y;

    template<typename Multiplier>
    inline auto operator*( const Multiplier& scalar )
    {
        using ResultingUnit1 = typename TResultingUnit<Unit1,Multiplier>::type;
        using ResultingUnit2 = typename TResultingUnit<Unit2,Multiplier>::type;
        TV<ResultingUnit1, ResultingUnit2> Result;

        Result.x = {this->x.Value * scalar.Value};
        Result.y = {this->y.Value * scalar.Value};

        return Result;
    }

    static TV<Unit1,Unit2> Create( Unit1 x, Unit2 y )
    {
        TV<Unit1,Unit2> C = {x,y};
        return C;
    }

    void Print()
    {
        std::cout<<"X --> "<<x.Value<< " Y --> "<<y.Value<<"\n";
    }
};

#define MAKE_TV(x, y) TV<decltype(x), decltype(y)>::Create(x, y)


