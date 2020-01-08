#ifndef ALLEYHOOPROSMATH_H_
#define ALLEYHOOPROSMATH_H_

namespace AlleyHoopROSUtils
{

    class Vector3
    {
        public:
            Vector3()
                : x(0.0f), y(0.0f), z(0.0f) {};
            Vector3(float _x, float _y, float _z)
                : x(_x), y(_y), z(_z) {};
            ~Vector3() = default;

            float x;
            float y;
            float z;
            
    };

    class Transform
    {
        public:
            Transform(){};
            ~Transform() = default;
            Vector3 position;
            Vector3 rotation;
            Vector3 scale;
    };


}

#endif //!ALLEYHOOPROSMATH_H_