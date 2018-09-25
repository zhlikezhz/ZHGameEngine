set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_executable(ZHGameEngine Win32Application.cpp)
target_link_libraries(ZHGameEngine Common)