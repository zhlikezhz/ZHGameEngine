# ZHGameEngine
add_executable(ZHGameEngine MACOSX_BUNDLE
        CocoaApplication.mm 
        AppDelegate.m
        WindowDelegate.m
    )
find_library(COCOA_LIBRARY Cocoa required)
target_link_libraries(ZHGameEngine 
        Common 
        ${OPENGEX_LIBRARY} 
        ${OPENDDL_LIBRARY} 
        ${XG_LIBRARY} 
        ${COCOA_LIBRARY} 
        )