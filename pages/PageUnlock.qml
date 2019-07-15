import QtQuick 2.7

PageUnlockForm {

    function entry () {
        if (auth.checkAccessRequest(loginName.text, passwd.text) === 0) {
            login.close();
        } else {
            loginErrorFlag = true;
        }
    }

    function checkExecPermission (time) {
        return unlock.checkTime(time);
    }

    unlock.onResultChanged: {
        console.log("Resultado");
        statusLabel.text = unlock.result;
        if (statusLabel.text === "ERRO") {
            statusBox.color = "red";
        } else {
            statusBox.color = "green";
        }

        statusBox.visible = true;
    }

    button1 {
        onClicked: {
            console.log("Button 1 clicked generate.");
            unlock.gen_code(serial.text, code.text);
        }
    }

    button2 {
        onClicked: {
            serial.clear();
            code.clear();
        }
    }

    serial {
        onTextChanged: {
            statusBox.visible = false;
            if (serial.length > 0) {
                button2.enabled = true;
            } else {
                button2.enabled = false;
            }
        }
        onAccepted: {
            unlock.gen_code(serial.text, code.text);
        }
    }

    code {
        onTextChanged: {
            statusBox.visible = false;
            if (code.length > 0) {
                button2.enabled = true;
            } else {
                button2.enabled = false;
            }
        }
        onAccepted: {
            unlock.gen_code(serial.text, code.text);
        }
    }
}
