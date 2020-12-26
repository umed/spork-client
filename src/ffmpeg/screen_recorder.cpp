#include "screen_recorder.h"

#include "platform_config.h"

#include <fmt/format.h>
#include <string>
#include <utility>
namespace
{

std::pair<AVCodecParameters *, int> getVideoStreamCodecAndIndex(AVFormatContext *context)
{
    for (int i = 0; i < context->nb_streams; ++i) {
        if (context->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            return {context->streams[i]->codecpar, i};
        }
    }
    return {nullptr, -1};
}

#ifdef _WIN32
const PlatformConfig PLATFORM_CONFIG = {"dshow", "video=screen-capture-recorder"};
#elif defined linux
const PlatformConfig PLATFORM_CONFIG = {"x11grab", ":0.0+10,20"};
#else
const PlatformConfig PLATFORM_CONFIG = {"avfoundation", "1"};
#endif

} // namespace

// pCodec = avcodec_find_decoder(pFormatCtx->streams[audioStream]->codecpar->codec_id);
// pCodecCtx = avcodec_alloc_context3(pCodec);
// avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[audioStream]->codecpar);
// avcodec_open2(pCodecCtx, pCodec, NULL);
ScreenRecorder::ScreenRecorder()
{
    avdevice_register_all();
    context = avformat_alloc_context();
    input_format = av_find_input_format(PLATFORM_CONFIG.input_format.c_str());
    auto error_code = avformat_open_input(&context, PLATFORM_CONFIG.url.c_str(), input_format, nullptr);
    if (error_code != 0) {
        std::string error_message = fmt::format("Failed to open input format: {}", av_err2str(error_code));
        throw std::runtime_error(error_message);
    }
    auto [codec_parameters, ignore_index] = getVideoStreamCodecAndIndex(context);
    auto codec = avcodec_find_decoder(codec_parameters->codec_id);
    codec_context = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codec_context, codec_parameters);
    error_code = avcodec_open2(codec_context, codec, nullptr);
    if (error_code != 0) {
        std::string error_message = fmt::format("Failed to open codec: {}", av_err2str(error_code));
        throw std::runtime_error(error_message);
    }
    frame = av_frame_alloc();
    av_init_packet(&packet);
}

ScreenRecorder::~ScreenRecorder()
{
    av_free(frame);
    avformat_close_input(&context);
}

AVFrame *ScreenRecorder::getFrame()
{
    for (;;) {
        auto error_code = av_read_frame(context, &packet);
        if (error_code != 0)
            continue;
        if (error_code != 0) {
            std::string error_message = fmt::format("Failed to read frame: {}", av_err2str(error_code));
            throw std::runtime_error(error_message);
        }

        error_code = avcodec_send_packet(codec_context, &packet);
        if (error_code != 0) {
            std::string error_message = fmt::format("Failed to send packet: {}", av_err2str(error_code));
            throw std::runtime_error(error_message);
        }
        error_code = avcodec_receive_frame(codec_context, frame);
        if (error_code == EAGAIN) {
            continue;
        }
        if (error_code != 0) {
            std::string error_message = fmt::format("Failed to read frame: {}", av_err2str(error_code));
            throw std::runtime_error(error_message);
        } else {
            return frame;
        }
    }
}
