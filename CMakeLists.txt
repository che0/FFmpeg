cmake_minimum_required(VERSION 2.6)
set(FFMPEG_SOURCE_DIR ${CMAKE_SOURCE_DIR})
set(BUILDTYPE SHARED)

include_directories(
	${CMAKE_SOURCE_DIR}
)

set(CMAKE_C_FLAGS "-D_ISOC99_SOURCE -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_POSIX_C_SOURCE=200112 -D_XOPEN_SOURCE=600 -DHAVE_AV_CONFIG_H -std=c99 -D_GNU_SOURCE=1 -D_REENTRANT -fPIC")

add_subdirectory(libavutil)
add_subdirectory(libavcodec)
add_subdirectory(libavformat)
add_subdirectory(writer)
