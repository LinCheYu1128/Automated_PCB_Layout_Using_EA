cmake_minimum_required(VERSION 3.10)

# set the project name
project(AcBel_Project)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/BinaryTree/BinaryTree.cpp
    src/BinaryTree/PlotBinaryTree.cpp
    src/Component.cpp
    src/ComponentList.cpp
    src/Contour.cpp
    src/TreeNode.cpp
    src/main.cpp
)

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/includes
)