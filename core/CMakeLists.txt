
add_library(browser_core STATIC
    BrowserCore.cpp
    BrowserCore.h
    TabManager.cpp
    TabManager.h
    Event.h
    Identifier.h
    Tab.cpp
    Tab.h
    TabHistory.cpp
    TabHistory.h
    TabIdGenerator.cpp
    TabIdGenerator.h
    Url.h
)

target_include_directories(browser_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
