#include <math.h>
#include "VectorD2.hpp"
#include "Units.hpp"

using namespace Units;

namespace D2
{
    /*template<typename MatrixUnit>
    class Matrix2x2
    {
        public:
            MatrixUnit _a_1;
            MatrixUnit _a_2;
            MatrixUnit _b_1;
            MatrixUnit _b_2;

        inline static Matrix2x2<MatrixUnit> Create( MatrixUnit a_1, MatrixUnit a_2, MatrixUnit b_1, MatrixUnit b_2 )
        {
            Matrix2x2 CreatedMatrix;
            CreatedMatrix._a_1 = a_1;
            CreatedMatrix._a_2 = a_2;
            CreatedMatrix._b_1 = b_1;
            CreatedMatrix._b_2 = b_2;

            return CreatedMatrix;
        }

        template<typename VectorUnit>
        Vector<VectorUnit> operator *( Vector<VectorUnit> Vector )
        {
            Vector.x = _a_1 * Vector.x  + _a_2 * Vector.x ;
            Vector.y = _b_1  * Vector.x +  _b_2 * Vector.x ;

            return Vector;
        }
    };
    
    Matrix2x2<Scalar> CreateRotationMatrix( Radian AngleChange )
    {   
        Scalar a_1 = AngleChange.GetCos();
        Scalar a_2 = AngleChange.GetSin();
        Scalar b_1 = -AngleChange.GetSin();
        Scalar b_2 = AngleChange.GetCos();

        Matrix2x2<Scalar> Created;
        Created._a_1 = a_1;
        Created._a_2 =  a_2;
        Created._b_1 = b_1;
        Created._b_2 = b_2;

        return Created;
    }*/
}