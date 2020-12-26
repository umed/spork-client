#pragma once

#include <string>

struct PlatformConfig {
    std::string input_format;
    std::string url;

    PlatformConfig(const std::string &input_format, const std::string &url)
        : input_format(input_format)
        , url(url)
    {
    }
};
