#include <stdio.h>
#include "libavformat/avformat.h"

#undef printf

static AVStream *add_audio_stream(AVFormatContext *oc, enum CodecID codec_id)
{
    AVCodecContext *c;
    AVStream *st;

    st = avformat_new_stream(oc, NULL);
    if (!st) {
        printf("Could not alloc stream\n");
        return NULL;
    }
    st->id = 1;

    c = st->codec;
    c->codec_id = codec_id;
    c->codec_type = AVMEDIA_TYPE_AUDIO;

    /* put sample parameters */
    c->sample_fmt = AV_SAMPLE_FMT_S16;
    c->bit_rate = 64000;
    c->sample_rate = 44100;
    c->channels = 2;

    // some formats want stream headers to be separate
    if (oc->oformat->flags & AVFMT_GLOBALHEADER)
        c->flags |= CODEC_FLAG_GLOBAL_HEADER;

    return st;
}

int main()
{
	extern AVOutputFormat ff_matroska_audio_muxer;
	av_register_output_format(&ff_matroska_audio_muxer);
	extern URLProtocol ff_file_protocol;
	ffurl_register_protocol(&ff_file_protocol, sizeof(ff_file_protocol));
	
	AVOutputFormat * fmt = av_guess_format("matroska", "mka", "audio/x-matroska");
	if (fmt == NULL)
	{
		printf("FAIL!\n");
		return 1;
	}
	
	AVFormatContext * oc;
	const char * filename = "/tmp/output.mka";
	int ret = avformat_alloc_output_context2(&oc, fmt, NULL, filename);
	if (ret < 0)
	{
		printf("FAIL!\n");
		return 1;
	}
	
	AVStream * avs = add_audio_stream(oc, CODEC_ID_AAC);
	if (avs == NULL)
	{
		printf("FAIL!\n");
		return 1;
	}
	
	av_dump_format(oc, 0, filename, 1);
	
	ret = avio_open(&oc->pb, filename, AVIO_FLAG_WRITE);
	if (ret < 0) {
            printf("FAIL! Could not open '%s'\n", filename);
            return 1;
        }
	
	AVDictionary * options = NULL;
	ret = avformat_write_header(oc, &options);
	if (ret != 0)
	{
		AVDictionaryEntry * cur;
		for (cur = NULL; cur = av_dict_get(options, NULL, cur, 0), cur != NULL; )
		{
			printf("%s -> %s\n", cur->key, cur->value);
		}
		printf("FAIL!\n");
	}
	
	char foo[512];
	int i;
	for (i = 0; i < 500; i++)
	{
		AVPacket packet;
		av_init_packet(&packet);
		packet.size = sizeof(foo);
		packet.stream_index = 0;
		packet.data = foo;
		packet.flags |= AV_PKT_FLAG_KEY;
		
		ret = av_write_frame(oc, &packet);
		if (ret != 0)
		{
			printf("FAIL!\n");
			return 1;
		}
	}
	
	av_write_trailer(oc);
	avformat_free_context(oc);
	return 0;
}