import QtQuick 2.3
import QtQuick.Controls 2.15
import QtMultimedia 5.15
import VideoProducer 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Spork")
    VideoProducer {
        id: videoProducer
    }
    // Column {
    //     Text {
    //         text: "hello world!"
    //     }

    // }
    VideoOutput {
        id: videoOutput
        source: videoProducer
        anchors.fill: parent
    }
}
