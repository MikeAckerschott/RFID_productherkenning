cmake_minimum_required(VERSION 3.5)
project(statemachine)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/~/bcm2835)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/tools)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/states)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/parts)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/wx)

find_package(wxWidgets REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})

add_executable( statemachine
	src/parts/button.cpp
	src/parts/mcp2515.cpp
	src/parts/canTranslator.cpp

	src/tools/context.cpp
	src/tools/state.cpp
	src/tools/procesStatus.cpp
	
	src/states/idleState.cpp
	src/states/readMessageState.cpp
	src/states/setWorkspaceState.cpp
	src/states/validateIncomingMessageState.cpp
	src/states/awaitStartupResponseState.cpp

	src/wx/bFrame.cpp
	src/wx/MyApp.cpp
	src/wx/numericInputFrame.cpp
	src/wx/stationList.cpp

)

# added these lines
target_link_libraries(statemachine bcm2835 ${wxWidgets_LIBRARIES})