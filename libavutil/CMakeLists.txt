add_library(avutil SHARED integer.c mathematics.c dict.c parseutils.c avstring.c pixdesc.c mem.c log.c samplefmt.c audioconvert.c eval.c random_seed.c lfg.c opt.c rational.c md5.c imgutils.c crc.c utils.c lzo.c)
target_link_libraries(avutil m)
