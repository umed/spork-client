#pragma once

#include <functional>
#include <memory>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavformat/avformat.h>
#include <libavutil/frame.h>
}

class ScreenRecorder
{
    template <typename T>
    using UniquePtr = std::unique_ptr<T, std::function<void(T *)>>;

  private:
    AVFormatContext *context;
    AVInputFormat *input_format;
    AVCodecContext *codec_context;

    AVPacket packet;
    AVFrame *frame;

  public:
    ScreenRecorder();
    ~ScreenRecorder();

    AVFrame *getFrame();
};
