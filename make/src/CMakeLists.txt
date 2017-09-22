set(SOURCE_FILES "AETemplate.h" "DagUtils.cpp" "DagUtils.h" "icons.h" "ShellModCommand.cpp" "ShellModCommand.h" "ShellModNode.cpp" "ShellModNode.h" "Utils.h" "pluginMain.cpp"
)

find_package(Maya REQUIRED)

include_directories(${MAYA_INCLUDE_DIR})
link_directories(${MAYA_LIBRARY_DIR})
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES})

MAYA_PLUGIN(${PROJECT_NAME})
