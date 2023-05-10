cmake_minimum_required(VERSION 3.21)
project(az_hold_em_Kyelse)

set(CMAKE_CXX_STANDARD 14)

include_directories(C:/Users/Kyelse/CLionProjects)

add_executable(az_hold_em_Kyelse 52Cards.hpp Player.hpp PokerHand.hpp Card.hpp
        main.cpp)
