file(GLOB TOP_LEVEL_SOURCES *.cpp)
file(GLOB TOP_LEVEL_HEADERS *.hpp *.h)

add_executable(Minesweeper ${TOP_LEVEL_SOURCES} ${TOP_LEVEL_HEADERS})

add_subdirectory(tools)
add_subdirectory(field)

target_link_libraries(Minesweeper
    PRIVATE
    tools
    field)