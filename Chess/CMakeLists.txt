# CMakeList.txt : CMake project for Chess, include source and define
# project specific logic here.
#

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Core Quick REQUIRED)

# Add source to this project's executable.
add_executable (Chess 
    "main.cpp" 
    "Qml/qml.qrc" 
    "Headers/EnumPkg.h" 
    "Headers/StructPkg.h" 
    "Headers/ChessCls.h" 
    "Sources/ChessCls.cpp" 
    "Headers/UiCls.h" 
    "Sources/UiCls.cpp" 
    "Headers/UiChessIfc.h" 
    "Headers/ConstPkg.h")

target_link_libraries(Chess PRIVATE Qt6::Core Qt6::Quick)

qt6_add_resources(Chess
    qml.qrc)

# Copy all QML files from the source directory to the binary directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Qml/ DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

target_include_directories(Chess PRIVATE ${CMAKE_SOURCE_DIR}/Chess)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Chess PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
