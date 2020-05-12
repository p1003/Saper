cmake_minimum_required(VERSION 3.15)
project(Saper)

set(CMAKE_CXX_STANDARD 14)

#set(SFML_ROOT C:/Users/p1003/Desktop/AGH/C++/Saper/SFML)
set(SFML_STATIC_LIBRARIES TRUE)

set(SFML_DIR "SFML/lib/cmake/SFML")

set(CMAKE_MODULE_PATH "$(CMAKE_CURRENT_LIST_DIR)/cmake_modules")

find_package(SFML 2.5 REQUIRED COMPONENTS audio graphics window system)
add_executable(Saper main.cpp GameClasses/Board.cpp GameClasses/Board.h GameClasses/Block.cpp GameClasses/Block.h config.h DrawableClasses/Visualizer.cpp DrawableClasses/Visualizer.h DrawableClasses/Menu.cpp DrawableClasses/Menu.h DrawableClasses/InfoBar.cpp DrawableClasses/InfoBar.h GameClasses/SaperGame.cpp GameClasses/SaperGame.h)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Saper sfml-graphics sfml-audio sfml-window sfml-system)
    #target_link_libraries(Saper ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()