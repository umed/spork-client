#include <QAbstractVideoSurface>

#include "recorder.h"

namespace Spork
{
namespace ScreenRecorder
{

class VideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
  private:
    Recorder recorder;

  public:
    QList<QVideoFrame::PixelFormat>
    supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
    bool present(const QVideoFrame &frame);
};

} // namespace ScreenRecorder
} // namespace Spork
