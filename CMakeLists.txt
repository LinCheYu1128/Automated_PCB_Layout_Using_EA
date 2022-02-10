cmake_minimum_required(VERSION 3.10)

# set the project name
project(AcBel_Project)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/main.cpp
    
    src/Layout/Layout.cpp
    
    src/Layout/Placement/BinaryTree/BinaryTree.cpp
    src/Layout/Placement/BinaryTree/PlotBinaryTree.cpp
    src/Layout/Placement/BinaryTree/TreeNode.cpp
    src/Layout/Placement/Contour.cpp
    src/Layout/Placement/Component.cpp
    src/Layout/Placement/ComponentList.cpp

    src/Layout/Routing/Net.cpp
)

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/includes
)