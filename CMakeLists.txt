cmake_minimum_required(VERSION 3.24.2)
project(lab4b C)

set(CMAKE_C_STANDARD 11)

add_executable(lab5 main.c controller/ComputerNetworkGraph.c controller/ComputerNetworkGraph.h ResponsesHandler.c ResponsesHandler.h view/DialogHelper.c view/DialogHelper.h Utils.c Utils.h view/commandsHelper/MainMenu.c view/commandsHelper/MainMenu.h model/FileHelper.c model/FileHelper.h model/MyVector.c model/MyVector.h view/GrpahVisHelper.c view/GrpahVisHelper.h controller/ComputerNetworkGraph.c view/DialogHelper.h view/commandsHelper/GraphInteraction.c view/commandsHelper/GraphInteraction.h view/commandsHelper/ComputerModifications.c view/commandsHelper/ComputerModifications.h view/commandsHelper/ConnectionModifications.c view/commandsHelper/ConnectionModifications.h view/commandsHelper/consts1.h view/commandsHelper/consts2.h view/commandsHelper/consts3.h)
