add_library(avformat SHARED matroskadec.c matroskaenc.c matroska.c riff.c isom.c rmdec.c rm.c avc.c flacenc_header.c avlanguage.c metadata.c utils.c avio.c aviobuf.c options.c id3v2.c id3v1.c)
target_link_libraries(avformat avcodec avutil)
