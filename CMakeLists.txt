cmake_minimum_required(VERSION 3.22)
project(2048)
set(CMAKE_CXX_STANDARD 23)
set(ALL_WARNINGS -O2 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow -Wswitch-default -Wundef -Wno-unused -Wconversion -Wuseless-cast -Wno-missing-include-dirs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
macro(set_compiler_warnings target)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        target_compile_options(${target} PUBLIC ${ALL_WARNINGS})
    endif()
endmacro()

add_library(g2048 STATIC 2048.cpp 2048.h)
set_compiler_warnings(g2048)

find_package(Qt6 REQUIRED COMPONENTS Quick Qml QuickControls2 QuickDialogs2 QuickLayouts QuickTemplates2)

qt_standard_project_setup(REQUIRES 6.5)
set(APP_EXE game)

qt_add_executable(${APP_EXE} main.cpp BoardModel.h BoardModel.cpp
    Types.h)

set_compiler_warnings(${APP_EXE})
qt_add_qml_module(${APP_EXE}
        URI gameModule
        VERSION 1.0
        SOURCES
            GameController.cpp
            GameController.h
            SaveController.cpp
            SaveController.h
        QML_FILES
            qml/EndDialog.qml
            qml/GameGrid.qml
            qml/GameHeader.qml
            qml/GameSettingsDialog.qml
            qml/Main.qml
            qml/MainMenu.qml
            qml/ResetDialog.qml
            qml/ScoresWindow.qml
            qml/Tile.qml
            qml/UndoDialog.qml
)
target_link_libraries(${APP_EXE} PUBLIC g2048 PRIVATE Qt6::Quick)
set_target_properties(${APP_EXE} PROPERTIES MACOSX_BUNDLE TRUE)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
