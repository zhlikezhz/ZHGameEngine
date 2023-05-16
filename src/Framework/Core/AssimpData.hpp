#ifndef __FRAMEWORK_CORE_ASSIMPDATA__
#define __FRAMEWORK_CORE_ASSIMPDATA__
#include "Core/TypeDefine.hpp"
#include "assimp/scene.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include <vector>

namespace UpPower
{
	class AssimpData
	{
	public:
		static AssimpData* CreateFromFile(const char* filename);
		static AssimpData* CreateFromMemory(const char* buffer, int length);

	public:
		void AddUV(glm::vec2 uv);
		void AddUVs(std::vector<glm::vec2>&);

		void AddPoint(glm::vec3);
		void AddPoints(std::vector<glm::vec3>&);

		void AddNormal(glm::vec3);
		void AddNormals(std::vector<glm::vec3>&);

		void AddIndex(uint index);
		void AddIndices(std::vector<uint>&);

		inline std::vector<glm::vec2>& GetUV() {return m_UVs;}
		inline std::vector<glm::vec3>& GetPoints() {return m_Points;}
		inline std::vector<glm::vec3>& GetNormals() {return m_Normals;}
		inline std::vector<uint>& GetIndices() {return m_uiIndices;}

		inline bool IsDirty() { return m_bDirty;}
		inline void SetDirty(bool dirty) { m_bDirty = dirty; }
		inline size_t GetPointNumber() { return m_Points.size(); }

	protected:
		void InitMesh(const aiMesh* mesh);
		void InitFromScene(const aiScene* scene);
		void LoadFromFile(const char* filename);
		void LoadFromMemory(const uchar* buffer, int length);

	protected:
		bool m_bDirty;
		std::vector<glm::vec2> m_UVs;
		std::vector<glm::vec3> m_Points;
		std::vector<glm::vec3> m_Normals;
		std::vector<uint> m_uiIndices;

	private:
		AssimpData();
		~AssimpData();
	};
}

#endif