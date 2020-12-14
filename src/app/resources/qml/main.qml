import QtQuick 2.3
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Spork")
    Column {
        Text {
            text: "hello world!"
        }
        Image {
            source: "image://videoframe/red"
        }
    }
}
