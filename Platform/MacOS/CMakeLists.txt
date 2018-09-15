# ZHGameEngineCocoa
add_executable(ZHGameEngineCocoa MACOSX_BUNDLE
        CocoaApplication.mm 
        AppDelegate.m
        WindowDelegate.m
    )
find_library(COCOA_LIBRARY Cocoa required)
target_link_libraries(ZHGameEngineCocoa 
        Common 
        ${OPENGEX_LIBRARY} 
        ${OPENDDL_LIBRARY} 
        ${XG_LIBRARY} 
        ${COCOA_LIBRARY} 
        )