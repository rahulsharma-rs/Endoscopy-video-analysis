project(SSR)
find_package(OpenCV REQUIRED)
add_executable(SSR histcomp)
target_link_libraries(SSR ${OpenCV_LIBS})
