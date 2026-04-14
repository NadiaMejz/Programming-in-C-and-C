cmake_minimum_required(VERSION 3.27)
project(nadia2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(classes)

add_executable(nadia2
        classes/DBColumn.hpp
        classes/DBRow.hpp
        classes/DBRowValue.hpp
        classes/DBTable.hpp
        classes/Join.hpp
        deleteRecord.cpp
        generateNewTable.cpp
        getColumnByName.cpp
        getData.cpp
        getTableByName.cpp
        GlobalHeader.hpp
        main.cpp
        putData.cpp
        read.cpp
        save.cpp)
