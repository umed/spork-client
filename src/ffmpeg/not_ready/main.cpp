#include <iostream>
#include <utility>

extern "C" {

#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavformat/avformat.h>
// #include <libswscale/swscale.h>
};

std::pair<AVCodecContext *, int> getVideoStreamCodecAndIndex(AVFormatContext *context)
{
    for (int i = 0; i < context->nb_streams; ++i) {
        if (context->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            return {context->streams[i]->codec, i};
        }
    }
    return {nullptr, -1};
}

static void SaveFrame(AVFrame *pFrame, int index)
{
    FILE *pFile;
    char szFilename[32];
    int y;

    // Open file
    sprintf(szFilename, "frame%d.ppm", index);
    pFile = fopen(szFilename, "wb");
    if (pFile == NULL)
        return;

    // Write header
    fprintf(pFile, "P6\n%d %d\n255\n", pFrame->width, pFrame->height);

    // Write pixel data
    for (y = 0; y < pFrame->height; y++)
        fwrite(pFrame->data[0] + y * pFrame->linesize[0], 1, pFrame->width * 3, pFile);

    // Close file
    fclose(pFile);
}

int main()
{
    avdevice_register_all();
    // avcodec_register_all();
    AVFormatContext *context = avformat_alloc_context();
    AVInputFormat *input_format = av_find_input_format("avfoundation");
    auto error_code = avformat_open_input(&context, "1", input_format, nullptr);
    if (error_code != 0)
        std::cout << av_err2str(error_code) << std::endl;

    auto [video_codec_context, video_index] = getVideoStreamCodecAndIndex(context);
    auto codec = avcodec_find_decoder(video_codec_context->codec_id);
    // AVCodecParserContext *parser = av_parser_init(codec->id);
    error_code = avcodec_open2(video_codec_context, codec, nullptr);
    if (error_code != 0)
        std::cout << av_err2str(error_code) << std::endl;

    AVFrame *frame = av_frame_alloc();
    AVPacket packet;
    av_init_packet(&packet);
    for (;;) {
        error_code = av_read_frame(context, &packet);
        if (error_code != 0)
            continue;
        if (error_code != 0)
            std::cout << av_err2str(error_code) << std::endl;

        int got_picture;
        // error_code = avcodec_decode_video2(video_codec_context, frame, &got_picture, &packet);
        error_code = avcodec_send_packet(video_codec_context, &packet);
        if (error_code != 0)
            std::cout << av_err2str(error_code) << std::endl;
        // for (int i = 0; packet.size > 0; i++) {
        error_code = avcodec_receive_frame(video_codec_context, frame);
        if (error_code != 0)
            std::cout << av_err2str(error_code) << std::endl;
        // auto filename = "frame" + std::to_string(i) + ".ppm";
        else {
            SaveFrame(frame, 0);
            break;
        }
    }
    // }
    // copy image

    av_free(frame);
    // av_free(frame_rgb);
    avformat_close_input(&context);
}
