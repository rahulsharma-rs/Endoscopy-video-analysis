project(FRAMEEXTRACTION)
find_package(OpenCV REQUIRED)
add_executable(FRAMEEXTRACTION break)
target_link_libraries(FRAMEEXTRACTION ${OpenCV_LIBS})
