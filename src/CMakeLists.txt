add_subdirectory(Framework)
add_subdirectory(Platform)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable(GraphicEngine main.cpp)

add_subdirectory(Example)
find_library(LUA lualib.lib ${PROJECT_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(GLAD_LIBRARY glad.lib ${PROJECT_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(GLFW_LIBRARY glfw3.lib ${PROJECT_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(ASSIMP_LIBRARY assimp-vc141-mt.lib ${PROJECT_LIBRARY_DIR} NO_DEFAULT_PATH)
target_link_libraries(GraphicEngine
		Platform
		Example
		Core
		Lua
		${LUA}
		${GLAD_LIBRARY}
		${GLFW_LIBRARY}
		${ASSIMP_LIBRARY}
		)