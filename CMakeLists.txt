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
aux_source_directory(src/tinyengine/ecs ENGINE_SRC)
aux_source_directory(libs/glad/src      ENGINE_SRC)
aux_source_directory(libs/stb_image     ENGINE_SRC)
aux_source_directory(libs/miniaudio/    ENGINE_SRC)

add_library(${ENGINE_NAME} STATIC ${ENGINE_SRC})

set(GLFW_BUILD_SHARED_LIBRARY CACHE BOOL OFF "Build shared libraries")
set(GLFW_BUILD_DOCS CACHE BOOL OFF"Build the GLFW documentation")
set(GLFW_INSTALL CACHE BOOL OFF "Generate installation target")
add_subdirectory(libs/glfw)

target_include_directories(
    ${ENGINE_NAME}
    PUBLIC include libs/glad/include libs/stb_image libs/miniaudio # /usr/local/Cellar/glm/0.9.9.8/include
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

target_compile_options(
    ${ENGINE_NAME}
    PUBLIC $<$<STREQUAL:$<UPPER_CASE:"${CMAKE_BUILD_TYPE}">,"RELEASE">:-Os> -fno-rtti -fno-exceptions
)

################
# space sector
################
aux_source_directory(src/game GAME_SRC)
aux_source_directory(src/game/stages GAME_SRC)
aux_source_directory(src/game/controllers GAME_SRC)
add_executable(${PROJECT_NAME} ${GAME_SRC})

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE ${ENGINE_NAME}
)

target_compile_features(
    ${PROJECT_NAME}
    PUBLIC cxx_std_17
)

add_custom_target(
    CompressExe
    COMMAND strip ${PROJECT_NAME}
    COMMAND upx --best --ultra-brute ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    COMMENT "make SpaceSector more small"
    VERBATIM
)

#############
# unit test
#############
include(CTest)
add_subdirectory(tests)

###############
# install game
###############
install(
    PROGRAMS ${CMAKE_BINARY_DIR}/SpaceSector
    DESTINATION ${PROJECT_SOURCE_DIR}/output
)

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/assets
    DESTINATION ${PROJECT_SOURCE_DIR}/output
)
