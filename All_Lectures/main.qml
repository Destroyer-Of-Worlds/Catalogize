import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TreeView {
        anchors.fill: parent;
        model: myModel
        TableViewColumn{
            title:"Course"
            role: "display"
            width:500
        }
    }
}
