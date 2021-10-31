set(TARGET lru_cache)

add_executable(${TARGET} lru_cache.h lru_cache.cpp)

target_compile_features(${TARGET} PRIVATE cxx_std_17)
