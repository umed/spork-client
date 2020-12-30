#pragma once

#include "recorder.h"

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>

namespace Spork
{
namespace ScreenRecorder
{

class VideoProducer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)
  private:
    QAbstractVideoSurface *surface;
    QVideoSurfaceFormat format;

    Recorder recorder;

  public:
    VideoProducer(QObject *parent = nullptr);
    ~VideoProducer();

    QAbstractVideoSurface *videoSurface() const;
    void setVideoSurface(QAbstractVideoSurface *surface_);

    static void registerQmlType();

  protected:
    void timerEvent(QTimerEvent *) override;
};

} // namespace ScreenRecorder
} // namespace Spork
