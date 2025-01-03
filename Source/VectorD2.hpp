#pragma once
#include <cstdlib>
#include <cmath>
#include<iostream>
#include<concepts>
#include "Units.hpp"

namespace D2
{
    template<typename VectorUnit>
    struct Vector
    {

        VectorUnit x;
        VectorUnit y;

        friend inline bool operator==( const Vector<VectorUnit>& V_1, const Vector<VectorUnit>& V_2 ) { return (V_1.x.Value == V_2.x.Value && V_1.y.Value == V_2.y.Value); }
        friend inline bool operator!=( const Vector<VectorUnit>& V_1, const Vector<VectorUnit>& V_2 ) { return (V_1.x.Value != V_2.x.Value || V_1.y.Value != V_2.y.Value); }
        inline Vector<VectorUnit> operator * ( const Units::Scalar& scalar )
        {
            Vector<VectorUnit> Result;
            Result.x = this->x * scalar.Value;
            Result.y = this->y * scalar.Value;
            return Result;
        }
        template<typename MultiplierUnit,typename ResultingUnit>//Represents a non mathematical unit 
        inline Vector<ResultingUnit> operator * ( const MultiplierUnit& scalar )
        {
            Vector<ResultingUnit> Result;
            Result.x = this->x * scalar.Value;
            Result.y = this->y * scalar.Value;
            return Result;
        }
        
        static Vector<VectorUnit> Create( VectorUnit x, VectorUnit y )
        {
            Vector<VectorUnit> createdVector;
            createdVector.x.Value = x.Value;
            createdVector.y.Value = y.Value;

            return createdVector;
        }
        static Vector<VectorUnit> Create( double x, double y )
        {
            Vector<VectorUnit> createdVector;
            createdVector.x.Value = x;
            createdVector.y.Value = y;

            return createdVector;
        }

        static VectorUnit GetMagnitude( const Vector<VectorUnit> vector )
        {
            VectorUnit magnitude = 
            { 
                std::sqrt(vector.x.Value * vector.x.Value + vector.y.Value * vector.y.Value),
            };
            return magnitude;
        }
        
        static Vector<VectorUnit> Addition( Vector<VectorUnit> vector, const Vector<VectorUnit> V_Addition )
        {
            vector.x.Value += V_Addition.x.Value;
            vector.y.Value += V_Addition.y.Value;

            return vector;
        }
        
        static void Print( Vector<VectorUnit> vector )
        {
            std::cout << "x --> " << vector.x.Value << "\ny --> " << vector.y.Value << "\n";
        }
        static void Print( Vector<VectorUnit> vector, std::string VectorName )
        {
            std::cout << "x --> " << vector.x.Value << "\ny --> " << vector.y.Value << "\n";
        }
        static Vector<VectorUnit> TakeFLoorValue( Vector<VectorUnit> vector )
        {
            vector.x.Value = static_cast<int>(vector.x.Value);
            vector.y.Value = static_cast<int>(vector.y.Value);

            return vector;
        }
        template<typename ReturnType, typename ScalarType>
        static inline Vector<ReturnType> ScalarDivide( Vector<VectorUnit> vector, ScalarType scalar )
        {
            Vector<ReturnType> ResultingVector;
            ResultingVector.x = vector.x / scalar;
            ResultingVector.y = vector.y / scalar;

            return ResultingVector;
        } 
        template <typename NewVectorUnit , typename ScalarMultiplier>//when multiplying the original unit, your unit will change in to the "new vector unit"
        static Vector<NewVectorUnit> ScalarMultiply( Vector<VectorUnit> vector, const ScalarMultiplier Scalar )
        {
            Vector<NewVectorUnit> result;
            result.x = vector.x * Scalar ;
            result.y = vector.x * Scalar ;

            return result;
        }
        static double GetDotProduct( Vector<VectorUnit> vector1, Vector<VectorUnit> vector2 )
        {
            double x = vector1.x.Value * vector2.x.Value;
            double y = vector1.y.Value * vector2.y.Value;

            return x + y;
        }
        static double GetAngleWithVectorInRadian( Vector<VectorUnit> vector1, Vector<VectorUnit> vector2  )
        {
            double dotProduct = GetDotProduct(vector1, vector2);
            auto magnitudeV1 = GetMagnitude(vector1);
            auto magnitudeV2 = GetMagnitude(vector2);

            double angleInRadian = std::acos(dotProduct / (magnitudeV1.Value * magnitudeV2.Value));
            return angleInRadian;
        }
    };
}

// Define hash specialization in the std namespace
namespace std 
{
    template<typename VectorUnit>
    struct hash<D2::Vector<VectorUnit>>
    {
        std::size_t operator()(const D2::Vector<VectorUnit>& Vector ) const 
        {
            constexpr std::size_t prime = 31;
            std::size_t h1 = std::hash<double>()( Vector.x.Value );
            std::size_t h2 = std::hash<double>()( Vector.y.Value );
            return h1 + prime * h2;
        }
    };
}