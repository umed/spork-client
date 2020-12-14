#pragma once

#include <QQuickImageProvider>

namespace Spork
{

class ImageProvider : public QQuickImageProvider
{
  public:
    ImageProvider();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
};

} // namespace Spork
