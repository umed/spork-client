#include "videosurface.h"

namespace Spork
{
namespace ScreenRecorder
{

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    Q_UNUSED(handleType);
    return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB24;
}

bool VideoSurface::present(const QVideoFrame &frame)
{
    auto av_frame = recorder.grabWindow();
    frame;
    return true;
}

} // namespace ScreenRecorder
} // namespace Spork
