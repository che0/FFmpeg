#include <stdio.h>
#include "libavformat/avformat.h"

#undef printf

int main()
{
	extern AVOutputFormat ff_matroska_audio_muxer;
	av_register_output_format(&ff_matroska_audio_muxer);
	AVFormatContext * oc = avformat_alloc_context();
	AVOutputFormat * fmt = av_guess_format("matroska", "mka", "audio/x-matroska");
	if (fmt == NULL)
	{
		printf("FAIL!\n");
		return 1;
	}
	oc->oformat = fmt;
	
	AVDictionary * options = NULL;
	int ret = avformat_write_header(oc, &options);
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
		packet.stream_index= 0;
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