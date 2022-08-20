cmake_minimum_required(VERSION 3.20)
project(cardgame)

set(CMAKE_CXX_STANDARD 14)

add_executable(cardgame Cards/card.cpp Cards/card.h Cards/RoyaltyCard.cpp Cards/RoyaltyCard.h Cards/AceCard.cpp Cards/AceCard.h System.cpp System.h Players/Player.cpp Players/Player.h Players/RealPlayer.cpp Players/RealPlayer.h Players/AIPlayer.cpp Players/AIPlayer.h Bank/Bank.cpp Bank/Bank.h
        main.cpp
        #SystemTests.cpp
        #Cards/matrix.cpp Cards/matrix.h
        Cards/RegularNumCard.cpp Cards/RegularNumCard.h SystemGUIfunctions.cpp GUImanager/GUImanager.cpp GUImanager/GUImanager.h GUImanager/Textbox.cpp GUImanager/Textbox.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Program Files/SFML/lib/cmake/SFML)
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Program Files/SFML/include)
target_link_libraries(cardgame sfml-system sfml-window sfml-graphics sfml-audio)

