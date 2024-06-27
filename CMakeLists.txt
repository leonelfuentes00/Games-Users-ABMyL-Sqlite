cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Especificar la versión de C++ que se utilizará (por ejemplo, C++11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Agregar la ruta a los archivos de encabezado de SQLite
include_directories(D:/Todo/Coding/SQLite/include)  # Ajusta esta ruta según la ubicación real

# Agregar archivos fuente de tu proyecto
set(SOURCES
    src/main.cpp  # Reemplaza con tus archivos fuente
    src/SqliteDatabaseHandler.cpp
    # Agrega más archivos según sea necesario
)

# Generar el ejecutable
add_executable(MyProject ${SOURCES})

# Enlazar con la biblioteca SQLite
target_link_libraries(MyProject sqlite3)
