set(TARGET intersection)

add_executable(${TARGET} intersection.cpp)

target_compile_features(${TARGET} PRIVATE cxx_std_17)

target_include_directories(${TARGET} PRIVATE ../include)
