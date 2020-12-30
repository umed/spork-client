#pragma once

extern "C" {
#include <libavcodec/packet.h>
#include <libavutil/frame.h>
}

struct AVFormatContext;
struct AVInputFormat;
struct AVCodecContext;
struct SwsContext;

namespace Spork
{
namespace ScreenRecorder
{

class Recorder
{
  private:
    AVFormatContext *context;
    AVInputFormat *input_format;
    AVCodecContext *codec_context;
    AVPacket packet;
    AVFrame *frame;
    AVFrame *frame_rgb;

    SwsContext *img_convert_ctx;

  public:
    Recorder();
    ~Recorder();

    AVFrame *grabWindow();
};

} // namespace ScreenRecorder
} // namespace Spork
