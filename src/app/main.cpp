#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "imageprovider.h"
#include "videoproducer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Spork::ScreenRecorder::VideoProducer::registerQmlType();

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:///");

    // engine.addImageProvider("videoframe", new Spork::ImageProvider);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
