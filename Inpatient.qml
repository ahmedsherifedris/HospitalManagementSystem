import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.2

import Qt.labs.qmlmodels 1.0

import QtQuick.Layouts 1.12
import QtPositioning 5.12
import QtLocation 5.12

Item {
    id: inpatient
    anchors.fill: parent

    Button {
        id: backButton
        anchors.top: parent.top
        anchors.left: parent.left
        text: "Back"

        onClicked: {
            inpatient.visible = false
            parent.parent.dashboardBackClicked()
        }
    }
    GridLayout {
        id: grid
        visible: true
        anchors.top: backButton.bottom
        anchors.centerIn: parent
        columns: 2
        Label {
            text: "Room Type: "
        }
        ComboBox {
            id: roomCombo
            model: ["Standard", "VIP"]

        }
        Label {
            text: "Room Cost: "
        }
        Label {
            text: roomCombo.currentIndex == 0 ? "100" : "200"
        }
        Label {
            text: "Number of Days (Tentative)" ;
        }
        SpinBox {
            id: noOfDays
            from: 1
        }

        Button {
            text: "Book Room"
            Layout.columnSpan: 2
            Layout.fillWidth: true

            onClicked: {

                grid.visible = false
                invoiceGrid.visible = true
            }
        }

        MessageDialog {
            id: errDialog
        }
    }

    GridLayout {
        id: invoiceGrid
        columns: 2
        visible: false
        anchors.top: backButton.bottom
        anchors.centerIn: parent
        Label {
            text: "<h2> Booking Room Invoice </h2>"
            Layout.columnSpan: 2
        }
        Label {
            text: "<b> Room Fees Per Day: </b>"
        }
        Label {
            text: roomCombo.currentIndex === 0 ? 100 : 200
        }
        Label {
            text: "<b> Room Fees For: " + noOfDays.value + " days </b>"
        }
        Label {
            text: roomCombo.currentIndex === 0 ? 100 * noOfDays.value : 200 * noOfDays.value
        }
        Label {
            text: "<b> Discount : </b>"
        }
        Label {
            text: mainWindow.hospital.reception.getDiscount() !== 0 ? mainWindow.hospital.reception.getDiscount() : "0"
        }
        Label {
            text: "<b> Total : </b>"
        }
        Label {
            text: ( (roomCombo.currentIndex === 0 ? 100 * noOfDays.value : 200 * noOfDays.value) - mainWindow.hospital.reception.getDiscount() )
        }
        Button {
            Layout.columnSpan: 2
            text: "Make Payment"
            onClicked : {
                console.debug(  roomCombo.currentIndex === 0 ? 100 * noOfDays.value : 200 * noOfDays.value )
                var result = mainWindow.hospital.reception.makePayment(roomCombo.currentIndex === 0 ? 100 * noOfDays.value : 200 * noOfDays.value)

                if(result)
                    enabled = false
            }
        }

    }
}
