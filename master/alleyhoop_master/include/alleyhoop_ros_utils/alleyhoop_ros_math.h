#ifndef ALLEYHOOPROSMATH_H_
#define ALLEYHOOPROSMATH_H_

namespace AlleyHoopROSUtils
{

    class AlleyHoopVector3
    {
        public:
            AlleyHoopVector3()
                : x(0.0f), y(0.0f), z(0.0f) {};
            AlleyHoopVector3(float _x, float _y, float _z)
                : x(_x), y(_y), z(_z) {};
            ~AlleyHoopVector3() = default;

            float x;
            float y;
            float z;
            
    };

    class AlleyHoopTransform
    {
        public:
            AlleyHoopTransform(){};
            ~AlleyHoopTransform() = default;
            AlleyHoopVector3 position;
            AlleyHoopVector3 rotation;
            AlleyHoopVector3 scale;
    };


}

#endif //!ALLEYHOOPROSMATH_H_