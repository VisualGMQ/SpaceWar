macro(AddTest TEST_NAME TEST_FILE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    add_test(NAME ${TEST_NAME}
             COMMAND ${TEST_NAME})
    target_link_libraries(${TEST_NAME} PRIVATE ${ARGN})
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
endmacro()

AddTest(math math.cpp ${ENGINE_NAME})
AddTest(renderer renderer.cpp ${ENGINE_NAME})
AddTest(innerBmpFont innerBmpFont.cpp ${ENGINE_NAME})
AddTest(audio audio.cpp ${ENGINE_NAME})
