cmake_minimum_required(VERSION 3.16)
project(Tanks2 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Test)

qt_standard_project_setup()

qt_add_resources(QRC_FILES resources.qrc)

qt_add_executable(Tanks2
    WIN32
    main.cpp

    ${QRC_FILES}

    Game/game.h Game/game.cpp
    Widgets/MainMenu/mainmenu.h Widgets/MainMenu/mainmenu.cpp
    Widgets/FieldSizeSelector/fieldsizeselector.h Widgets/FieldSizeSelector/fieldsizeselector.cpp
    Widgets/GameField/gamefield.h Widgets/GameField/gamefield.cpp
    Widgets/LevelMaker/levelmaker.h Widgets/LevelMaker/levelmaker.cpp
    Widgets/ObjectPanel/objectpanel.h Widgets/ObjectPanel/objectpanel.cpp
    Widgets/GameScreen/gamescreen.h Widgets/GameScreen/gamescreen.cpp
    Widgets/GameScreen/gamescreencontroller.h Widgets/GameScreen/gamescreencontroller.cpp
    Widgets/ActionPanel/actionpanel.h Widgets/ActionPanel/actionpanel.cpp
    Widgets/LevelSelector/levelselector.h Widgets/LevelSelector/levelselector.cpp

    Utils/GameStorage/gamestorage.h Utils/GameStorage/gamestorage.cpp
    Utils/ImagesManager/imagesmanager.h Utils/ImagesManager/imagesmanager.cpp
    Utils/JsonManager/jsonmanager.h Utils/JsonManager/jsonmanager.cpp

    Objects/Wall/wall.h Objects/Wall/wall.cpp
    Objects/Tank/tank.h Objects/Tank/tank.cpp
    Widgets/LevelMaker/levelmakercontroller.h Widgets/LevelMaker/levelmakercontroller.cpp
)

target_link_libraries(Tanks2
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

add_subdirectory(Tests)
