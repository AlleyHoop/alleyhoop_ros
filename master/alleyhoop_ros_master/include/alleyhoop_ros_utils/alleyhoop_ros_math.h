#ifndef ALLEYHOOPROSMATH_H_
#define ALLEYHOOPROSMATH_H_

namespace AlleyHoopROSUtils
{
    //* A utility class for positioning
    /**
     * holds values x, y, and z
    */
    class Vector3
    {
        public:
            Vector3();
            Vector3(float _x, float _y, float _z);
            ~Vector3() = default;

            float x;
            float y;
            float z;
            
    };

    //* A utility class for positioning
    /**
     * hold values position, rotation, and scale
    */
    class Transform
    {
        public:
            Transform(){};
            Transform(Vector3 _position, Vector3 _rotation, Vector3 _scale)
                : position(_position), rotation(_rotation), scale(_scale)
            {};
            ~Transform() = default;
            Vector3 position;
            Vector3 rotation;
            Vector3 scale;
    };


}

#endif //!ALLEYHOOPROSMATH_H_