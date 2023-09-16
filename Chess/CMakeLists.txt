# CMakeList.txt : CMake project for Chess, include source and define
# project specific logic here.
#

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
    "Sources/UiCls.cpp")

target_link_libraries(Chess PRIVATE Qt6::Core Qt6::Quick)

qt6_add_resources(Chess
    qml.qrc)

# Use configure_file to copy QML files to the build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Qml/main.qml ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/main.qml COPYONLY)

target_include_directories(Chess PRIVATE ${CMAKE_SOURCE_DIR}/Chess)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Chess PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
