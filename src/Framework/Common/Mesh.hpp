#pragma once
#include <vector>

namespace ZH
{
    struct Point
    {
        float x, y, z;
        Point(float x=0, float y=0, float z=0)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
    };

    // struct Triangle
    // {
    //     Point a, b, c;
    //     Triangle(Point a, Point b, Point c)
    //     {
    //         this->a = a;
    //         this->b = b;
    //         this->c = c;
    //     }
    //     Triangle(float* arr)
    //     {
    //         a = Point(arr[0], arr[1], arr[2]);
    //         b = Point(arr[3], arr[4], arr[5]);
    //         c = Point(arr[6], arr[7], arr[8]);
    //     }
    // };

    struct UV
    {
        float x, y, z;
        UV(float x=0, float y=0, float z=0)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
    };

    class Mesh
    {
        public:
            Mesh();
            ~Mesh();

            void addPoint(Point);
            void addPoint(float x, float y, float z=0);
            void addPoints(std::vector<Point>&);

            void addUV(UV);
            void addUV(float x, float y, float z=0);
            void addUVs(std::vector<UV>&);

            float* getUV();
            float* getPoints();
            inline bool isDirty() { return m_bDirty;}
            inline void setDirty(bool dirty) { m_bDirty = dirty; }
            inline int getPointNumber() { return m_vPoints.size(); }

        private:
            bool m_bDirty;
            std::vector<UV> m_vUV;
            std::vector<Point> m_vPoints;
    };
}
