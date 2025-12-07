cmake_minimum_required(VERSION 3.16)
project(Tanks2 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Test)

qt_standard_project_setup()

qt_add_resources(QRC_FILES resources.qrc)

qt_add_executable(Tanks2
    WIN32
    main.cpp

    ${QRC_FILES}

    src/game.h
    src/game.cpp
    src/mainmenu.h
    src/mainmenu.cpp
    src/fieldsizeselector.h
    src/fieldsizeselector.cpp
    src/gamefield.h
    src/gamefield.cpp
    src/levelmaker.h
    src/levelmaker.cpp
    src/objectpanel.h
    src/objectpanel.cpp
    src/gamescreen.h
    src/gamescreen.cpp
    src/gamescreencontroller.h
    src/gamescreencontroller.cpp
    src/actionpanel.h
    src/actionpanel.cpp
    src/levelselector.h
    src/levelselector.cpp
    src/levelmakercontroller.h
    src/levelmakercontroller.cpp
    src/NewFrameObjects.h
    src/gamestorage.h
    src/gamestorage.cpp
    src/imagesmanager.h
    src/imagesmanager.cpp
    src/jsonmanager.h
    src/jsonmanager.cpp
    src/tank.h
    src/tank.cpp
    src/wall.h
    src/wall.cpp
)

target_link_libraries(Tanks2
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

add_subdirectory(Tests)
