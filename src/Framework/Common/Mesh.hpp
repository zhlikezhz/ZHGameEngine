#pragma once
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "Component.hpp"
#include <vector>

namespace ZH
{
    class Mesh : public Component
    {
        DECLARE_CLASS(Mesh)

        public:
            Mesh();
            ~Mesh();

            void addUV(glm::vec2 uv);
            void addUVs(std::vector<glm::vec2>&);

            void addPoint(glm::vec3);
            void addPoints(std::vector<glm::vec3>&);

            void addNormal(glm::vec3);
            void addNormals(std::vector<glm::vec3>&);

            void addIndex(unsigned int index);
            void addIndices(std::vector<unsigned int>&);

            inline std::vector<glm::vec2>& getUV() {return m_vUVs;}
            inline std::vector<glm::vec3>& getPoints() {return m_vPoints;}
            inline std::vector<glm::vec3>& getNormals() {return m_vNormals;}
            inline std::vector<unsigned int>& getIndices() {return m_uiIndices;}

            inline bool isDirty() { return m_bDirty;}
            inline void setDirty(bool dirty) { m_bDirty = dirty; }
            inline int getPointNumber() { return m_vPoints.size(); }

        private:
            bool m_bDirty;
            std::vector<glm::vec2> m_vUVs;
            std::vector<glm::vec3> m_vPoints;
            std::vector<glm::vec3> m_vNormals;
            std::vector<unsigned int> m_uiIndices;
    };
}
