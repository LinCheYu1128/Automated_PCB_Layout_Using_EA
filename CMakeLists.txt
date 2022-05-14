cmake_minimum_required(VERSION 3.10)

# set the project name
project(AcBel_Project)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/main.cpp
    # Layout
    src/Layout/Layout.cpp
    # Layout -> Placement
    src/Layout/Placement/BinaryTree/BinaryTree.cpp
    src/Layout/Placement/BinaryTree/PlotBinaryTree.cpp
    src/Layout/Placement/BinaryTree/TreeNode.cpp
    src/Layout/Placement/Contour.cpp
    src/Layout/Placement/Component.cpp
    src/Layout/Placement/ComponentList.cpp
    # Layout -> Routing
    src/Layout/Routing/Net.cpp
    src/Layout/Routing/NetList.cpp
    # GA
    src/GA/GA.cpp
    src/GA/GA_Parameter.cpp
    src/GA/Crossover/Crossover.cpp
    src/GA/Mutation/Mutation.cpp
    # MOEAD
    # src/MOEAD/MOEAD.cpp
    # src/MOEAD/MOEAD_Parameter.cpp
    # console
    src/console.cpp
    # src/GL.cpp

)

# find_package(OpenGL REQUIRED)
# find_package(GLUT REQUIRED)
# include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

# target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/includes
        ${PROJECT_SOURCE_DIR}/includes/GA
        ${PROJECT_SOURCE_DIR}/includes/Layout
        # ${PROJECT_SOURCE_DIR}/includes/MOEAD
)