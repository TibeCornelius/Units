#include "Units.hpp"


namespace Units
{
    #pragma region BaseUnit
    //all implementation are in header file due to templates
    #pragma endregion
    #pragma region Kilogram
    Force Kilogram::operator*( const Acceleration& acceleration ) const
    {
        Force Force;
        Force.Value = this->Value * acceleration.Value;

        return Force;
    }
    Momentum Kilogram::operator* ( const Velocity& Velocity ) const
    {
        Momentum Momentum;
        Momentum.Value = this->Value * Velocity.Value;

        return Momentum;
    };
    #pragma endregion
    #pragma region Meters
    Velocity Meters::operator/( const Second& seconds ) const
    {
        Velocity Velocity;
        Velocity.Value = this->Value * seconds.Value;

        return Velocity;
    }
    #pragma endregion
    #pragma region Velocity

    Acceleration Velocity::operator/( const Second& seconds ) const
    {
        Acceleration Acceleration;
        Acceleration.Value = this->Value *  seconds.Value;

        return Acceleration;
    }
    Meters Velocity::operator*( const Second& seconds ) const
    {
        Meters Distance;
        Distance.Value = this->Value * seconds.Value;
        return Distance;
    };
    Momentum Velocity::operator*( const Kilogram& mass ) const
    {
        Momentum momentum;
        momentum.Value = this->Value * mass.Value;

        return momentum;
    };
    #pragma endregion
    #pragma region LeverArm
    Torque LeverArm::operator * ( const Force& distance ) const
    {
        Torque Torque;
        Torque.Value = distance.Value * this->Value;

        return Torque;
    }
    #pragma endregion
    #pragma region Acceleration
    Force Acceleration::operator*( const Kilogram& mass ) const
    {
        Force Force;
        Force.Value = this->Value * mass.Value;

        return Force;
    }
    #pragma endregion
    #pragma region Momentum
    Velocity Momentum::operator/( const Kilogram& mass ) const
    {
        Velocity velocity;
        velocity.Value = this->Value / mass.Value;

        return velocity;
    }

    #pragma endregion
    #pragma region Force
    Joule Force::operator*( const Meters& distance ) const
    {
        Joule Work_Energy;
        Work_Energy.Value = this->Value * distance.Value;

        return Work_Energy;
    }

    Torque Force::operator*( const LeverArm& distance ) const 
    {
        Torque Torque;
        Torque.Value =this->Value * distance.Value;
        
        return Torque;
    }
    #pragma endregion
}