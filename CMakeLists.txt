cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(SpaceSector
        VERSION 0.1.0
        DESCRIPTION "a game made for 1M Game Competition")

##############
# tinyengine
##############
set(ENGINE_NAME tinyengine)

aux_source_directory(src/tinyengine     ENGINE_SRC)
aux_source_directory(src/component      ENGINE_SRC)
aux_source_directory(libs/glad/src      ENGINE_SRC)
aux_source_directory(libs/stb_image     ENGINE_SRC)

add_library(${ENGINE_NAME} STATIC ${ENGINE_SRC})

set(BUILD_SHARED_LIBS CACHE BOOL OFF "Build shared libraries")
set(GLFW_BUILD_DOCS CACHE BOOL OFF"Build the GLFW documentation")
set(GLFW_INSTALL CACHE BOOL OFF "Generate installation target")
add_subdirectory(libs/glfw)

target_include_directories(
    ${ENGINE_NAME}
    PRIVATE include/tinyengine
    PUBLIC libs/glad/include libs/stb_image # /usr/local/Cellar/glm/0.9.9.8/include
)

target_link_libraries(
    ${ENGINE_NAME}
    PUBLIC glfw
)

target_compile_features(
    ${ENGINE_NAME}
    PUBLIC cxx_std_17
)

target_compile_definitions(
    ${ENGINE_NAME}
    PUBLIC $<$<STREQUAL:$<UPPER_CASE:"${CMAKE_BUILD_TYPE}">,"DEBUG">:GAME_DEBUG>
)

################
# space sector
################
aux_source_directory(src/game GAME_SRC)
add_executable(${PROJECT_NAME} ${GAME_SRC})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE include
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE ${ENGINE_NAME}
)

target_compile_features(
    ${PROJECT_NAME}
    PUBLIC cxx_std_17
)

#############
# unit test
#############
include(CTest)
add_subdirectory(tests)
