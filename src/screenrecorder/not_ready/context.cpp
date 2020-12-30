#include "context.h"

namespace
{
void ContextDeleter(AVFormatContext *context)
{
    if (context)
        avformat_close_input(&context);
}
} // namespace

Context::Context()
    : context(avformat_alloc_context(), ContextDeleter)
{
}

AVFormatContext *Context::raw()
{
    return context.get();
}
