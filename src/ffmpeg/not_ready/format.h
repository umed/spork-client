#pragma once

struct AVInputFormat;

class Format
{
  private:
    AVInputFormat *format;

  public:
    Format(Context &context, const PlatformConfig &config);
    ~Format() = default;

    Format(Format &other) = delete;
    Format &operator=(Format &other) = delete;

    AVInputFormat *raw();
};
