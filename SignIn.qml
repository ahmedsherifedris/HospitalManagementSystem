import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

Item {
    id: signInPage
    anchors.fill: parent

    Button {
        id: backButton
        anchors.top: parent.top
        anchors.left: parent.left
        text: "Back"

        onClicked: {
            signInPage.visible = false
            parent.parent.backClicked()
        }
    }
    GridLayout {
        id: grid
        anchors.top: backButton.bottom
        anchors.centerIn: parent
        columns: 2
        Label {text: "Username: "}
        TextField {
            id: unameTxt
        }

        Label {text: "Password: "}
        TextField {
            id: pwTxt
            echoMode: TextField.Password
        }
        Button {
            id: loginBtn
            text: "Login"
            Layout.columnSpan: 2
            Layout.fillWidth: true

            onClicked: {
                var result =  mainWindow.hospital.reception.signIn(unameTxt.text, pwTxt.text)
                if( result === 1) {
                    signInPage.visible = false
                    parent.parent.parent.dashboardBackClicked()
                }
                else if (result === 0){
                    errDialog.text = "Incorrect Password!"
                    errDialog.open()
                    return
                }
                else if (result === -1){
                    errDialog.text = "User not found!"
                    errDialog.open()
                    return
                }

            }
        }
        MessageDialog {
            id: errDialog
        }
    }
}
