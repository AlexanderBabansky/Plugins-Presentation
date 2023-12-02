add_library(plugin SHARED dllmain.cpp "VideoProcessor.h" "VideoProcessor.cpp")
target_link_libraries(plugin PRIVATE common)
