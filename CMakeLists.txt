cmake_minimum_required(VERSION 3.10)

project(NEEP-MS)


add_executable(NEEP-MS 
    src/model/subject.cpp 
    src/model/student.cpp
    src/user/visitor.cpp
    src/user/worker.cpp
    src/user/manager.cpp
    # test/test_linkedlist.cpp
    test/test_user.cpp
    )

target_include_directories(NEEP-MS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)


