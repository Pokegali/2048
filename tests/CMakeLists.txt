find_package(Qt6 REQUIRED COMPONENTS Core Test)

qt_standard_project_setup()
qt_add_executable(test_2048 Test2048.cpp Test2048.h)
set_compiler_warnings(test_2048)
target_link_libraries(test_2048 PUBLIC g2048 PRIVATE Qt6::Core Qt6::Test)
target_include_directories(test_2048 PRIVATE ..)
add_test(NAME test_2048 COMMAND test_2048)
