#include "format.h"

#include "context.h"
#include "platform_config.h"

#include <string>

extern "C" {
#include <libavdevice/avdevice.h>
#include <libavformat/avformat.h>
}

Format::Format(Context &context, const PlatformConfig &config)
{
    avdevice_register_all();
    format = av_find_input_format(config.input_format.c_str());
    auto context_raw = context.raw();
    auto error_code = avformat_open_input(&context_raw, config.url.c_str(), format, nullptr);
    if (error_code != 0) {
        std::string error_message = av_err2str(error_code);
    }
}
