set(AVCODEC_H ${FFMPEG_SOURCE_DIR}/libavcodec/avcodec.h)
set(CODEC_NAMES_SH ${FFMPEG_SOURCE_DIR}/libavcodec/codec_names.sh)
set(CONFIG_H ${FFMPEG_SOURCE_DIR}/config.h )
set(CODEC_NAMES_H ${FFMPEG_SOURCE_DIR}/libavcodec/codec_names.h)
add_custom_command(
	OUTPUT ${FFMPEG_SOURCE_DIR}/libavcodec/codec_names.h
	DEPENDS ${CONFIG_H}
	COMMAND ${CMAKE_C_COMPILER} ${CPPFLAGS} ${CFLAGS} -E ${AVCODEC_H} | ${CODEC_NAMES_SH} ${CONFIG_H} ${CODEC_NAMES_H}
)
add_library(ffmpeg_avcodec mpegaudiodata.c mpeg4audio.c raw.c utils.c codec_names.h imgconvert.c jrevdct.c pthread.c avpacket.c parser.c xiph.c options.c rawdec.c)
target_link_libraries(ffmpeg_avcodec pthread)
