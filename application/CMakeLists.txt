add_executable(application main.cpp MyTestComponent.cpp MyTestComponent.h
	VideoProcessorHost.cpp VideoProcessorHost.h
	"VideoFrameComponent.cpp" "VideoFrameComponent.h" "OGLFrameComponent.cpp" "OGLFrameComponent.h")
target_link_libraries(application PRIVATE common)
target_include_directories(application PRIVATE "../common")
