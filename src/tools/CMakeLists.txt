add_library(tools "")

file(GLOB TOOL_LEVEL_SOURCES *.cpp)
file(GLOB TOOL_LEVEL_HEADERS *.hpp *.h)

target_sources(tools
    PRIVATE
    ${TOOL_LEVEL_SOURCES}
    PUBLIC
    ${TOOL_LEVEL_HEADERS})

target_include_directories(tools
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR})