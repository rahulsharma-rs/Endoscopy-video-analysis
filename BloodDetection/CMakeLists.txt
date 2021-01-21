project(BLOODTEST)
find_package(OpenCV REQUIRED)
add_executable(BLOODTEST bloodtest)
target_link_libraries(BLOODTEST ${OpenCV_LIBS})
