cmake_minimum_required(VERSION 3.21)
project(Systemy_operacyjne_2__projekt)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(model)

add_executable(Systemy_operacyjne_2__projekt
        model/Cook.cpp
        model/Cook.h
        model/DeliveryMan.cpp
        model/DeliveryMan.h
        model/Oven.cpp
        model/Oven.h
        model/Shelf.cpp
        model/Shelf.h
        model/SimulationModel.cpp
        model/SimulationModel.h
        model/Sink.cpp
        model/Sink.h
        model/ThermalBag.cpp
        model/ThermalBag.h
        model/Worktop.cpp
        model/Worktop.h
        controller/Controller.cpp
        model/Entity.cpp model/Entity.h)
