cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(HTRApp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(OpenCV_DIR "/home/DKuzn/QtProjects/HTRApp/build")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories("eigen")
include_directories("include/HTRApp")

add_executable(HTRApp
    src/main.cpp
    include/HTRApp/mainwindow.cpp
    include/HTRApp/mainwindow.h
    include/HTRApp/mainwindow.ui
    include/HTRApp/paintscene.cpp
    include/HTRApp/paintscene.h
    include/HTRApp/neuralnetwork.cpp
    include/HTRApp/neuralnetwork.h
    include/HTRApp/image.cpp
    include/HTRApp/image.h
)
add_executable(train_net
    src/train.cpp
    include/HTRApp/dataset.cpp
    include/HTRApp/dataset.h
    include/HTRApp/datasetitem.cpp
    include/HTRApp/datasetitem.h
    include/HTRApp/neuralnetwork.cpp
    include/HTRApp/neuralnetwork.h
)

target_link_libraries(HTRApp Qt5::Widgets)
target_link_libraries(HTRApp ${OpenCV_LIBS})

set_property(TARGET HTRApp PROPERTY CXX_STANDARD 11)
