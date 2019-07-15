import QtQuick 2.7
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0
import Qt.labs.settings 1.0
import QtQuick.LocalStorage 2.0
import QtQml 2.0
import dClock 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 480
    height: 620
    title: qsTr("dClock Tools")

    property bool loginErrorFlag: false
    readonly property int textMargins: Math.round(32 * toPixels(0.02))
    readonly property int menuMargins: Math.round(13 * toPixels(0.02))

    function toPixels(percentage) {
        return percentage * Math.min(window.width, window.height);
    }


    function checkObsolecence() {
        var db = LocalStorage.openDatabaseSync("unlockDB", "1.0", "Data record to REP unlock!", 1000000);

        var rs;
        db.transaction(
                    function(tx) {
                        // Create the database if it doesn't already exist
                        tx.executeSql('CREATE TABLE IF NOT EXISTS SchedObsolecence(id INTEGER PRIMARY KEY, cur_date DATE)');
                        tx.executeSql('CREATE TRIGGER IF NOT EXISTS ins_sched_obso AFTER INSERT ON SchedObsolecence BEGIN UPDATE SchedObsolecence SET cur_date = DATETIME(\'NOW\') WHERE rowid = new.rowid; END;');
                        // Show all added SchedObsolecence
                        rs = tx.executeSql('SELECT * FROM SchedObsolecence');
                        if (rs.rows.length > 0) {
                            console.log("Date de ativação [ " + rs.rows.item(0).cur_date + " ]");
                        } else {
                            // Add (another) SchedObsolecence row
                            tx.executeSql('INSERT INTO SchedObsolecence (id) VALUES(1)');
                        }
                    }
                    )
        return rs.rows.item(0).cur_date;
    }

    function renewLicence() {
        var db = LocalStorage.openDatabaseSync("unlockDB", "1.0", "Data record to REP unlock!", 1000000);

        var rs;
        db.transaction(
                    function(tx) {
                        // Remove Obsolecence Schedule
                        tx.executeSql('DELETE FROM SchedObsolecence');
                    }
                    )
    }

    Component.onCompleted: {
        //        renewLicence();
        //        if (unlock.checkExecPermission(checkObsolecence()) === false) {
        //            button1.enabled = false;
        //            passwd.enabled = false;
        //            loginName.enabled = false;
        //            loginError.text = "Firmware expirou!";
        //            loginErrorFlag = true;
        //        }
                login.open();
    }

    Settings {
        id: settings
        property string style: "Material"
    }

        SwipeView {
            id: swipeView
            anchors.fill: parent
            currentIndex: tabBar.currentIndex

            PageUnlock {
                id: unlock
                Label {
                    text: qsTr("Unlock");
                }
            }
        }

        footer: TabBar {
            id: tabBar
            currentIndex: swipeView.currentIndex
            TabButton {
                text: qsTr("Unlock")
            }
        }

    Popup {
        id: login
        x: (window.width - width) / 2
        y: window.height / 6
        modal: true
        focus: true
        contentWidth: 280
        closePolicy: Popup.NoAutoClose

        contentItem: ColumnLayout {
            id: aboutColumn
            spacing: 8

            Label {
                text: "Login"
                font.bold: true
                font.pixelSize: toPixels(0.05)
            }

            Label {
                id: loginError
                width: parent.width
                wrapMode: Label.Wrap
                Layout.alignment: Qt.AlignJustify
                font.pixelSize: toPixels(0.04)
                text: "Login ou senha inválida!"
                color: "red"
                opacity: loginErrorFlag
            }

            TextField {
                id: loginName
                Layout.fillWidth: true
                onAccepted: {
                    unlock.entry();
                }
                onTextChanged: {
                    loginErrorFlag = false;
                }
            }

            TextField {
                id: passwd
                Layout.fillWidth: true
                echoMode: TextInput.Password
                width: parent.width
                onAccepted: {
                    unlock.entry();
                }
                onTextChanged: {
                    loginErrorFlag = false;
                }
            }

            Button {
                id: button1
                highlighted: true
                Material.accent: Material.Red
                Material.elevation: 0
                text: "ENTRAR"
                onClicked: {
                    unlock.entry();
                }
            }
        }
    }
}
