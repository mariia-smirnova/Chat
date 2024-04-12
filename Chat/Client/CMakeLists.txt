set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)
add_executable(Client ${PROJECT_SOURCES}
    message.h message.cpp message.ui
    login.h login.cpp login.ui)


target_link_libraries(Client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Network)
