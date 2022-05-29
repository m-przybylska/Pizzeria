cmake_minimum_required(VERSION 3.21)
project(Systemy_operacyjne_2__projekt)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(pizzeria)

add_executable(Systemy_operacyjne_2__projekt
        pizzeria/Cook.cpp
        pizzeria/Cook.h
        pizzeria/DeliveryMan.cpp
        pizzeria/DeliveryMan.h
        pizzeria/Oven.cpp
        pizzeria/Oven.h
        pizzeria/Shelf.cpp
        pizzeria/Shelf.h
        pizzeria/SimulationModel.cpp
        pizzeria/SimulationModel.h
        pizzeria/Sink.cpp
        pizzeria/Sink.h
        pizzeria/ThermalBag.cpp
        pizzeria/ThermalBag.h
        pizzeria/Worktop.cpp
        pizzeria/Worktop.h
        pizzeria/Controller.cpp
        pizzeria/Entity.cpp pizzeria/Entity.h)
