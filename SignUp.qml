import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

import QtQuick.Layouts 1.12
import QtPositioning 5.12

Item {
    id: signUpPage
    anchors.fill: parent

    property var loc : QtPositioning.coordinate(latTxt.text, longTxt.text)

    Button {
        id: backButton
        anchors.top: parent.top
        anchors.left: parent.left
        text: "Back"

        onClicked: {
            signUpPage.visible = false
            parent.parent.backClicked()
        }
    }
    GridLayout {
        anchors.top: backButton.bottom
        anchors.centerIn: parent
        columns: 2
        Label { text: "Username" }
        TextField { id: unameTxt }

        Label { text: "Password" }
        TextField {
            id: pwTxt
            echoMode: TextField.Password
        }

        Label { text: "Confirm Password" }
        TextField {
            id: confirmTxt
            echoMode: TextField.Password

            onEditingFinished: {
                if(text !== pwTxt.text){
                    errDialog.text = "Passwords don't match."
                    errDialog.informativeText = "Please try again"
                    text = ""
                    errDialog.open()
                }
            }
        }

        Label { text: "Age" }
        SpinBox {
            id: ageSpn
            editable: true
            from: 0
            to: 150
        }

        Label { text: "Gender" }
        ComboBox {
            id: genderCmb
            model: ["Male", "Female", "Other"]
        }

        Label { text: "Address Latitude" }
        TextField {
            id: latTxt
            validator: DoubleValidator{}
        }

        Label { text: "Address Longitude" }
        TextField {
            id: longTxt
            validator: DoubleValidator{}
        }

        Label { text: "Insured" }
        CheckBox {
            id: insuredChk
        }

        Label { text: "Credit Card Number" }
        TextField {
            id: cardTxt
            echoMode: TextField.Password
        }

        Button {
            text: "Sign Up"
            Layout.columnSpan: 2
            Layout.fillWidth: true

            onClicked: {

                if(unameTxt.text === ""){
                    errDialog.text = "Username empty"
                    errDialog.informativeText = "Please try again"
                    errDialog.open()
                    return
                }
                else if(pwTxt.text === ""){
                    errDialog.text = "Password empty"
                    errDialog.informativeText = "Please try again"
                    errDialog.open()
                    return
                }
                else if(confirmTxt.text === ""){
                    errDialog.text = "Confirm Password empty"
                    errDialog.informativeText = "Please try again"
                    errDialog.open()
                    return
                }
                else if(pwTxt.text !== confirmTxt.text){
                    errDialog.text = "Passwords don't match"
                    errDialog.informativeText = "Please try again"
                    errDialog.open()
                    return
                }
                else if(latTxt.text === ""){
                    errDialog.text = "Latitude empty"
                    errDialog.informativeText = "Please try again"
                    errDialog.open()
                    return
                }
                else if(longTxt.text === ""){
                    errDialog.text = "Longitude empty"
                    errDialog.informativeText = "Please try again"
                    errDialog.open()
                    return
                }
                else if(cardTxt.text === ""){
                    errDialog.text = "Credit Card Number empty"
                    errDialog.informativeText = "Please try again"
                    errDialog.open()
                    return
                }

                var patient = mainWindow.hospital.reception.signupPatient

                patient.username = unameTxt.text;
                patient.password = pwTxt.text;
                patient.age = ageSpn.value;
                patient.gender = genderCmb.currentIndex;

                loc.latitude = parseFloat(latTxt.text );
                loc.longitude = parseFloat(longTxt.text );

                if(!loc.isValid) {
                    errDialog.text = "Invalid coordinates!"
                    errDialog.informativeText = "Please try again"
                    errDialog.open()
                    return
                }

                patient.address = loc;

                patient.insured = insuredChk.checked;
                patient.creditCardNumber= cardTxt.text;

                mainWindow.hospital.reception.signUp(patient)

                signUpPage.visible = false
                parent.parent.parent.backClicked()

            }
        }

        MessageDialog {
            id: errDialog
        }
    }
}
