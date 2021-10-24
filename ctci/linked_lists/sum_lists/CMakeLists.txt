set(TARGET sum_lists)

add_executable(${TARGET} sum_lists.cpp)

target_include_directories(${TARGET} PRIVATE ../include)
