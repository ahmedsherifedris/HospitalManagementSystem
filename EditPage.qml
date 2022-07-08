import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

import QtQuick.Layouts 1.12
import QtPositioning 5.12
import QtLocation 5.12

Item {
    id: editPage
    anchors.fill: parent

    property var loc : QtPositioning.coordinate(latTxt.text, longTxt.text)

    Button {
        id: backButton
        anchors.top: parent.top
        anchors.left: parent.left
        text: "Back"

        onClicked: {
            editPage.visible = false
            parent.parent.dashboardBackClicked()
        }
    }
    GridLayout {
        anchors.top: backButton.bottom
        anchors.centerIn: parent
        columns: 2
        Label { text: "Username" }
        TextField { id: unameTxt; enabled: false }

        Label { text: "Old Password" }
        TextField {
            id: pwTxt
            echoMode: TextField.Password
        }

        Label { text: "New Password" }
        TextField {
            id: newPwTxt
            echoMode: TextField.Password
        }

        Label { text: "Confirm Password" }
        TextField {
            id: confirmTxt
            echoMode: TextField.Password

            onEditingFinished: {
                if(text !== newPwTxt.text){
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
        Label { id: ptsTxt ; text: "Points available : " }
        Button {
            text: "Redeem Now"
            onClicked: { if(mainWindow.hospital.reception.redeemPoints() ) enabled = false }
        }
        Label { text: "Wallet" }
        TextField {
            id: wltTxt
            enabled: false
            text: "0"
        }

        Button {
            text: "Save"
            Layout.columnSpan: 2
            Layout.fillWidth: true

            onClicked: {

                if(pwTxt.text === ""){
                    errDialog.text = "Old Password empty"
                    errDialog.informativeText = "Please try again"
                    errDialog.open()
                    return
                }
                else if(newPwTxt.text === ""){
                    errDialog.text = "New Password empty"
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
                else if(newPwTxt.text !== confirmTxt.text){
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

                patient.username = unameTxt.text
                patient.password = pwTxt.text;
                patient.newPassword = newPwTxt.text;
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

                var result = mainWindow.hospital.reception.saveEdits(patient)
                if(result === -1){
                    errDialog.text = "Incorrect Password!";
                    errDialog.open()
                    return
                }
                else if(result === 0){
                    errDialog.text = "Update Failed!";
                    errDialog.open()
                    return
                }
                else if(result === 1){
                    errDialog.text = "Update Success!";
                    editPage.visible = false
                    parent.parent.parent.dashboardBackClicked()
                }
                else {

                    editPage.visible = false
                    parent.parent.parent.dashboardBackClicked()
                }
            }
        }

        MessageDialog {
            id: errDialog
        }
    }
    onVisibleChanged: {
        if(!visible)
            return
        var patient = mainWindow.hospital.reception.viewDetails()
        unameTxt.text = mainWindow.hospital.reception.username
        ageSpn.value = patient.age
        genderCmb.currentIndex = patient.gender
        latTxt.text = patient.address.latitude
        longTxt.text = patient.address.longitude
        insuredChk.checked = patient.insured
        cardTxt.text = patient.creditCardNumber
        ptsTxt.text = "Points available : " + patient.points
        wltTxt.text = patient.wallet

        mainWindow.hospital.reception.deleteViewDetailsPtr(patient)
    }
}
