set(TARGET count_diffs)

add_executable(${TARGET} count_diffs.cpp)

target_include_directories(${TARGET} PRIVATE ../include)
