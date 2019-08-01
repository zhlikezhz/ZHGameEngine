#pragma once
#include <vector>

namespace ZH
{
    struct Triangle
    {
        float x, y, z;
        Triangle(float x=0, float y=0, float z=0)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
    };

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

            void addTriangle(Triangle);
            void addTriangle(float x, float y, float z=0);
            void addTriangles(std::vector<Triangle>&);

            void addUV(UV);
            void addUV(float x, float y, float z=0);
            void addUVs(std::vector<UV>&);

            float* getUV();
            float* getTriangles();
            inline bool isDirty() { return m_bDirty;}
            inline int getTriangleNumber() { return m_vTriangles.size(); }

        private:
            bool m_bDirty;
            std::vector<UV> m_vUV;
            std::vector<Triangle> m_vTriangles;
    };
}
