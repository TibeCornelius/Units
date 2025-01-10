




template<int Meter,int Second>
struct Unit
{
    double Value;


    inline Unit<Meter,Second> operator+( Unit<Meter,Second>& Other )
    {
        return { this->Value + Other.Value };
    }

    inline Unit<Meter,Second> operator-( Unit<Meter,Second>& other )
    {
        return { this->Value - other.Value };
    }

    template <int OtherMeters, int OtherSeconds>
    constexpr auto operator*(const Unit<OtherMeters, OtherSeconds>& other) const {
        return Unit<Meter + OtherMeters, Second + OtherSeconds>(Value * other.Value);
    }

    inline void PrintType() const
    {
        std::cout<<"Meters^"<< Meter << " Seconds "<< Second<<"\n";
    }
};