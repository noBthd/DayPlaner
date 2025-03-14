cmake_minimum_required(VERSION 3.10)
project(DayPlanner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt/lib/cmake/Qt6")  
# set(nlohmann_json_DIR "/.vcpkg/vcpkg/installed/arm64-osx/share/nlohmann_json/nlohmann_jsonConfig.cmake")

find_package(Qt6 REQUIRED 
    COMPONENTS 
        Core 
        Gui 
        Widgets 
        Qml 
        QmlIntegration
        Quick
)

find_package(PostgreSQL REQUIRED)
# find_package(CURL REQUIRED)
# find_package(nlohmann_json CONFIG REQUIRED)

set(SOURCES
    src/main.cpp
    src/utils/passwordUtils.cpp
    src/sql/pgconn.cpp
    src/sql/user_query.cpp
    src/user.cpp
    src/reg_handler.cpp
)

set(INCLUDES
    inc/utils/passwordUtils.h
    inc/sql/pgconn.h
    inc/sql/user_query.h
    inc/user.h
    inc/reg_handler.h
)

qt_wrap_cpp(MOC_SOURCES ${INCLUDES})

add_executable(DayPlanner 
    ${MOC_SOURCES}
    ${SOURCES}
    ${INCLUDES}
)

qt_add_resources(RESOURCES 
    ui/main.qrc
)

target_sources(DayPlanner PRIVATE ${RESOURCES})

target_include_directories(DayPlanner 
    PRIVATE
        inc
        ${PostgreSQL_INCLUDE_DIRS}
)

target_link_libraries(DayPlanner 
    PRIVATE 
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets 
        Qt6::Qml 
        Qt6::QmlIntegration
        Qt6::Quick
        ${PostgreSQL_LIBRARIES}
        # CURL::libcurl
        # nlohmann_json::nlohmann_json
)