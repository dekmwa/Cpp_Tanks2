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
    ${CMAKE_SOURCE_DIR}/src/jsonmanager.cpp
    ${CMAKE_SOURCE_DIR}/src/gamestorage.cpp
    ${CMAKE_SOURCE_DIR}/src/gamescreencontroller.cpp
    ${CMAKE_SOURCE_DIR}/src/levelmakercontroller.cpp
    ${CMAKE_SOURCE_DIR}/src/tank.cpp
    ${CMAKE_SOURCE_DIR}/src/wall.cpp
    ${CMAKE_SOURCE_DIR}/src/imagesmanager.cpp
)

target_link_libraries(GameTests
    PRIVATE
        Qt6::Test
        Qt6::Core
        Qt6::Widgets
)

add_test(NAME GameTests COMMAND GameTests)
