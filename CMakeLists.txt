macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} gtest gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")

# source
add_subdirectory(src)
add_subdirectory(test)

# data
configure_file(data/test.txt src/test.txt COPYONLY)
configure_file(data/miniSQLTest.txt src/miniSQLTest.txt COPYONLY)
configure_file(data/miniSQLTest/instruction0.txt src/instruction0.txt COPYONLY)
configure_file(data/miniSQLTest/instruction1.txt src/instruction1.txt COPYONLY)
configure_file(data/miniSQLTest/instruction2.txt src/instruction2.txt COPYONLY)
configure_file(data/miniSQLTest/instruction3.txt src/instruction3.txt COPYONLY)
configure_file(data/miniSQLTest/instruction4.txt src/instruction4.txt COPYONLY)
configure_file(data/miniSQLTest/instruction5.txt src/instruction5.txt COPYONLY)
configure_file(data/miniSQLTest/instruction6.txt src/instruction6.txt COPYONLY)
configure_file(data/miniSQLTest/instruction7.txt src/instruction7.txt COPYONLY)
configure_file(data/miniSQLTest/instruction8.txt src/instruction8.txt COPYONLY)
configure_file(data/miniSQLTest/instruction9.txt src/instruction9.txt COPYONLY)
configure_file(data/miniSQLTest/student.txt src/student.txt COPYONLY)

include_directories(BEFORE src) # This is needed for gtest.


