set(TARGET tail)

add_executable(${TARGET} tail.cpp)

target_include_directories(${TARGET} PRIVATE ../include)
