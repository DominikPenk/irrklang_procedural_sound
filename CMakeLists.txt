cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(ProcedrualSound LANGUAGES CXX)


# Download and extract irrKlang (TODO: Implement this for all OSes)
set(IRRKLANG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/irrKlang)
if(NOT EXISTS ${IRRKLANG_ROOT})
    message (STATUS "Downloading irrKlang")
    file(DOWNLOAD 
        https://www.ambiera.at/downloads/irrKlang-64bit-1.6.0.zip
        ${CMAKE_CURRENT_SOURCE_DIR}/irrKlang.zip
        TIMEOUT 60
        SHOW_PROGRESS
        TLS_VERIFY ON)
    file(ARCHIVE_EXTRACT INPUT ${CMAKE_CURRENT_SOURCE_DIR}/irrKlang.zip
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
    file(REMOVE ${CMAKE_CURRENT_SOURCE_DIR}/irrKlang.zip)
    file(RENAME irrKlang-64bit-1.6.0 irrKlang)
endif()

add_library(irrKlang INTERFACE)
target_include_directories(irrKlang INTERFACE ${IRRKLANG_ROOT}/include)
target_link_directories(irrKlang INTERFACE ${IRRKLANG_ROOT}/lib/Winx64-visualStudio)
target_link_libraries(irrKlang INTERFACE irrKlang)

file(GLOB SRC src/*.h src/*.cpp)
add_executable(ProcedrualSound ${SRC})
target_link_libraries(ProcedrualSound PUBLIC irrKlang)
target_compile_features(ProcedrualSound PUBLIC cxx_std_17)
target_compile_definitions(ProcedrualSound  PRIVATE -DMEDIA_DIR="${IRRKLANG_ROOT}/media/")
add_custom_command(TARGET ProcedrualSound POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${IRRKLANG_ROOT}/bin/winx64-visualStudio/irrKlang.dll"
        $<TARGET_FILE_DIR:ProcedrualSound>)