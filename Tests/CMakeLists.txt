project(GameTests LANGUAGES CXX)
enable_testing(true)

find_package(Qt6 REQUIRED COMPONENTS Test)

add_executable(GameTests
    GameTestsSrc/main.cpp
    GameTestsSrc/gametest.h
    GameTestsSrc/gametest.cpp
)

target_include_directories(GameTests PRIVATE ${CMAKE_SOURCE_DIR})

target_sources(GameTests PRIVATE
    ${CMAKE_SOURCE_DIR}/Utils/JsonManager/jsonmanager.cpp
    ${CMAKE_SOURCE_DIR}/Utils/GameStorage/gamestorage.cpp
    ${CMAKE_SOURCE_DIR}/Widgets/GameScreen/gamescreencontroller.cpp
    ${CMAKE_SOURCE_DIR}/Widgets/LevelMaker/levelmakercontroller.cpp
    ${CMAKE_SOURCE_DIR}/Objects/Tank/tank.cpp
    ${CMAKE_SOURCE_DIR}/Objects/Wall/wall.cpp
    ${CMAKE_SOURCE_DIR}/Utils/ImagesManager/imagesmanager.cpp
)

target_link_libraries(GameTests
    PRIVATE
        Qt6::Test
        Qt6::Core
        Qt6::Widgets
)

add_test(NAME GameTests COMMAND GameTests)
