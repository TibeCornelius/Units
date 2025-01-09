
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
struct ResultingUnit;

template<>
struct ResultingUnit<T1,T2>
{
    using type = T3;
};

template<>
struct ResultingUnit<T1, const double>
{
    using type = T3;
};

/*template <>
struct ResultingUnit<TT1,TT2>
{
    using type = TT3;
};*/

template<typename Unit>
struct TV
{
    Unit x;
    Unit y;

    template<typename Multiplier>
    inline auto operator*( const Multiplier& scalar )
    {
        using ResultingUnit = typename ResultingUnit<Unit,Multiplier>::type;
        TV<ResultingUnit> Result;

        Result.x = {this->x.Value * scalar.Value};
        Result.y = {this->y.Value * scalar.Value};

        return Result;
    }
};


