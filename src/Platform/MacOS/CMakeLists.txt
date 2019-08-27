# ZHGameEngine
# add_executable(ZHGameEngine MACOSX_BUNDLE
#         CocoaApplication.mm 
#         AppDelegate.m
#         WindowDelegate.m
#     )
# find_library(COCOA_LIBRARY Cocoa required)
# target_link_libraries(ZHGameEngine 
#         Common 
#         ${OPENGEX_LIBRARY} 
#         ${OPENDDL_LIBRARY} 
#         ${XG_LIBRARY} 
#         ${COCOA_LIBRARY} 
#         )

add_executable(ZHGameEngine MACOSX_BUNDLE
        MacGLApplication.cpp
    )
find_library(GLAD_LIBRARY glad.a ${PROJECT_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(GLFW_LIBRARY libglfw3.a ${PROJECT_LIBRARY_DIR} NO_DEFAULT_PATH)
find_library(COCOA_LIBRARY Cocoa required)
find_library(IOKIT_LIBRARY IOKit required)
find_library(COREVIDEO_LIBRARY CoreVideo required)
find_library(ASSIMP_LIBRARY libassimp.dylib ${PROJECT_LIBRARY_DIR} NO_DEFAULT_PATH)
target_link_libraries(ZHGameEngine 
        Common 
        ${GLAD_LIBRARY}
        ${GLFW_LIBRARY}
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${COREVIDEO_LIBRARY}
        ${ASSIMP_LIBRARY}
        )
