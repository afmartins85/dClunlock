import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0
import Qt.labs.settings 1.0
import dClock 1.0

Item {
    property alias button1: button1
    property alias button2: button2
    property alias serial: serial
    property alias code: code
    property alias unlock: unlock
    property alias auth: auth
    property alias statusBox: statusBox
    property alias statusLabel: statusLabel

    Unlock {
        id: unlock
    }

    Authentication {
        id: auth
    }

    ColumnLayout {
        anchors.centerIn: parent

        TextField {
            id: serial
//            Layout.fillWidth: true
            Layout.preferredWidth: 200
            maximumLength: 7
            width: 150
            placeholderText: "NÚMERO SERIAL"
        }

        TextField {
            id: code
//            Layout.fillWidth: true
            Layout.preferredWidth: 200
            maximumLength: 8
            width: 150
            placeholderText: "CÓDIGO"
        }

        RowLayout {
            spacing: 20

            Button {
                id: button1
                highlighted: true
                Layout.fillWidth: true
                Material.background: Material.Red
                Material.elevation: 0
                text: "GERAR"
            }

            Button {
                id: button2
                highlighted: true
                Layout.fillWidth: true
                enabled: false
                text: "LIMPAR"
            }
        }

        Rectangle {
            id: statusBox
            height: 40
            color: "#1eb369"
            visible: false
            Layout.fillWidth: true

            Label {
                id: statusLabel
                color: "#ffffff"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignTop
            }
        }
    }
}
