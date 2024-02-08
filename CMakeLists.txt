cmake_minimum_required(VERSION 3.27)
project(2048)
set(CMAKE_CXX_STANDARD 23)
add_compile_options(-O2 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow -Wswitch-default -Wundef -Wno-unused -Wconversion -Wuseless-cast -Wno-missing-include-dirs)

add_library(g2048 STATIC 2048.cpp 2048.h)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()
set(APP_EXE game)

qt_add_executable(${APP_EXE} main.cpp)
qt_add_qml_module(${APP_EXE}
        URI gameModule
        VERSION 1.0
        SOURCES
            GameController.cpp
            GameController.h
            SaveController.cpp
            SaveController.h
        QML_FILES
            main.qml
)
target_link_libraries(${APP_EXE} PUBLIC g2048)
target_link_libraries(${APP_EXE} PRIVATE Qt6::Quick)
