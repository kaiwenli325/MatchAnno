cmake_minimum_required(VERSION 3.16)

project(AnnoTool VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(MatchAnno
    Sources/AnnoTool.cpp
    Sources/main.cpp
    Sources/MainMark.cpp
    Sources/MainScene.cpp
    Sources/MainView.cpp
    Sources/MiniMark.cpp
    Sources/MiniScene.cpp
    Sources/MiniView.cpp
    Sources/MyTableWidget.cpp
    Sources/Resources/resources.qrc
    Sources/Resources/resources.rc
)


target_link_libraries(MatchAnno PRIVATE Qt6::Widgets)

set_target_properties(MatchAnno PROPERTIES
    WIN32_EXECUTABLE ON
)
