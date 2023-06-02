add_library(field "")

file(GLOB FIELD_LEVEL_SOURCES *.cpp)
file(GLOB FIELD_LEVEL_HEADERS *.hpp *.h)

target_sources(field
    PRIVATE
    ${FIELD_LEVEL_SOURCES}
    PUBLIC
    ${FIELD_LEVEL_HEADERS})

target_include_directories(field
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR})