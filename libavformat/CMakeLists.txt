add_library(ffmpeg_avformat ${BUILDTYPE} matroskadec.c matroskaenc.c matroska.c riff.c isom.c rmdec.c rm.c avc.c avlanguage.c metadata.c utils.c avio.c aviobuf.c options.c id3v2.c id3v1.c file.c)
target_link_libraries(ffmpeg_avformat ffmpeg_avcodec ffmpeg_avutil)
