cmake_minimum_required(VERSION 3.8)
project(RPG)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        JsonBox/Convert.h
        JsonBox/Escaper.h
        JsonBox/Grammar.h
        JsonBox/IndentCanceller.h
        JsonBox/Indenter.h
        JsonBox/JsonParsingError.h
        JsonBox/JsonWritingError.h
        JsonBox/OutputFilter.h
        JsonBox/SolidusEscaper.h
        JsonBox/Value.h
        Convert.cpp
        Escaper.cpp
        IndentCanceller.cpp
        Indenter.cpp
        JsonBox.h
        JsonBox/Export.h
        JsonParsingError.cpp
        JsonWritingError.cpp
        SolidusEscaper.cpp
        Value.cpp entity.h entityManager.h entityManager.cpp item.h item.cpp armor.h armor.cpp weapon.h weapon.cpp main.cpp inventory.h)

add_executable(RPG ${SOURCE_FILES})