set(TARGET compressor)

add_executable(${TARGET} compressor.cpp)

target_include_directories(${TARGET} PRIVATE ../include)
