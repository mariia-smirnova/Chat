add_executable(Server
  main.cpp
  myserver.h myserver.cpp
)
target_link_libraries(Server Qt${QT_VERSION_MAJOR}::Core Qt6::Network)
