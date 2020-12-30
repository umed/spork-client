#include "recorder.h"

#include "platform_config.h"

#include <fmt/format.h>
#include <string>
#include <utility>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libavutil/pixfmt.h>
#include <libswscale/swscale.h>
}

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

namespace Spork
{
namespace ScreenRecorder
{

Recorder::Recorder()
{
    // FIXME: fix memory leak in case of errors
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
    frame_rgb = av_frame_alloc();
    av_image_alloc(frame_rgb->data, frame_rgb->linesize, codec_context->width, codec_context->height,
                   AVPixelFormat::AV_PIX_FMT_BGRA, 32);
    frame_rgb->height = codec_context->height;
    frame_rgb->width = codec_context->width;
    frame_rgb->format = AVPixelFormat::AV_PIX_FMT_BGRA;
    av_init_packet(&packet);

    img_convert_ctx =
        sws_getContext(codec_context->width, codec_context->height, codec_context->pix_fmt, codec_context->width,
                       codec_context->height, AVPixelFormat::AV_PIX_FMT_BGRA, SWS_BICUBIC, NULL, NULL, NULL);
}

Recorder::~Recorder()
{
    av_free(frame);
    // FIXME: possible memory leak
    // av_freep(frame_rgb->data[0]);
    av_free(frame_rgb);
    avformat_close_input(&context);
}

AVFrame *Recorder::grabWindow()
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
            sws_scale(img_convert_ctx, frame->data, frame->linesize, 0, codec_context->height, frame_rgb->data,
                      frame_rgb->linesize);
            return frame_rgb;
        }
    }
}

} // namespace ScreenRecorder
} // namespace Spork
