#--[Tests lists
file(GLOB test_srcs_temp ${PROJECT_SOURCE_DIR}/test/*/*Test.cpp)

set(test_srcs "")

foreach(test_src_temp ${test_srcs_temp} )
    string(REPLACE "//" "/" test_src ${test_src_temp})
    list(APPEND test_srcs ${test_src})
endforeach(test_src_temp ${test_srcs_temp})

############################################################
# --[ Gmock
set(GMOCK_DIR  "${PROJECT_SOURCE_DIR}/extern/gmock")
file(GLOB gmock_srcs  ${GMOCK_DIR}/*.cc)
include_directories(SYSTEM ${GMOCK_DIR})
add_library(gtest EXCLUDE_FROM_ALL ${gmock_srcs})
target_link_libraries(gtest ${CMAKE_THREAD_LIBS_INIT})

############################################################
set(CTEST_FLAGS "")
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} ${CTEST_FLAGS} --verbose)

############################################################
foreach(test_src ${test_srcs} )
    # get test file name
    get_filename_component(test_bare_name ${test_src} NAME)
    string(REPLACE ".cpp" "" test_bare_name_without_extension ${test_bare_name})
    string(REPLACE "\"" "" test_name ${test_bare_name_without_extension})

    # create executable
    add_executable(${test_name} EXCLUDE_FROM_ALL ${test_src})
    add_dependencies(check ${test_name})

    # link libraries
    target_link_libraries(${test_name} gtest)

    # set target properties
    set_target_properties(${test_name}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
            COMMAND ${test_name}
            )

    # add test
    add_test(${test_name} ${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS}
            --suppressions=${MEMORYCHECK_SUPPRESSIONS_FILE} ${CMAKE_BINARY_DIR}/test/${test_name}
            --gtest_color=yes --gtest_output=xml:${CMAKE_BINARY_DIR}/test/unit_${test_name}.xml)
    add_test(${test_name} ${CMAKE_BINARY_DIR}/test/${test_name} --gtest_color=yes
            --gtest_output=xml:${CMAKE_BINARY_DIR}/test/${test_name}.xml)

endforeach(test_src ${test_srcs})

