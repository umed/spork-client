#include "videoproducer.h"

#include <QQmlEngine>

namespace Spork
{
namespace ScreenRecorder
{

VideoProducer::VideoProducer(QObject *parent)
    : QObject(parent)
    , surface(nullptr)
{
    startTimer(1000 / 60);
}

void VideoProducer::registerQmlType()
{
    qmlRegisterType<VideoProducer>("VideoProducer", 1, 0, "VideoProducer");
}

QAbstractVideoSurface *VideoProducer::videoSurface() const
{
    return surface;
}

void VideoProducer::setVideoSurface(QAbstractVideoSurface *surface_)
{
    if (surface != surface_ && surface && surface->isActive()) {
        surface->stop();
    }
    surface = surface_;
    if (surface) {
        auto frame = recorder.grabWindow();
        QImage image = QImage(frame->data[0], frame->width, frame->height, QImage::Format_ARGB32);
        surface->start(QVideoSurfaceFormat(image.size(), QVideoFrame::pixelFormatFromImageFormat(image.format())));
    }
}

void VideoProducer::timerEvent(QTimerEvent *)
{
    if (!surface)
        return;
    auto frame = recorder.grabWindow();
    QImage image = QImage(frame->data[0], frame->width, frame->height, QImage::Format_ARGB32);
    // image.save("img.jpg");
    surface->present(image);
}

VideoProducer::~VideoProducer() = default;

} // namespace ScreenRecorder
} // namespace Spork
