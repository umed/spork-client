#pragma once

#include <functional>
#include <memory>

extern "C" {
#include <libavformat/avformat.h>
}

class Context
{
  private:
    using ContextPtr = std::unique_ptr<AVFormatContext, std::function<void(AVFormatContext *)>>;
    ContextPtr context;

  public:
    Context();
    ~Context() = default;

    Context(Context &other) = delete;
    Context &operator=(Context &other) = delete;

    AVFormatContext *raw();
};
