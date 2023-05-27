cmake_minimum_required(VERSION 3.24.2)
project(lab4b C)

set(CMAKE_C_STANDARD 11)

add_executable(lab5 main.c controller/ComputerNetworkGraph.c controller/ComputerNetworkGraph.h view/ResponsesHandler.c view/ResponsesHandler.h view/DialogHelper.c view/DialogHelper.h Utils.c Utils.h view/CommandHelper.c view/CommandHelper.h model/FileHelper.c model/FileHelper.h model/MyVector.c model/MyVector.h view/GrpahVisHelper.c view/GrpahVisHelper.h controller/ComputerNetworkGraph.c view/DialogHelper.h)
