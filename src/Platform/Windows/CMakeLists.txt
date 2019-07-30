# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
# find_library(WINDOWS_D2D1 d2d1)
# add_executable(ZHGameEngine D2DApplication.cpp)
# target_link_libraries(ZHGameEngine Common ${WINDOWS_D2D1})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
find_library(WINDOWS_OPENGL glew32)
add_executable(ZHGameEngine OpenGLApplication.cpp)
target_link_libraries(ZHGameEngine Common ${WINDOWS_OPENGL})