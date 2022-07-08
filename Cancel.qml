import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.2

import Qt.labs.qmlmodels 1.0

import QtQuick.Layouts 1.12
import QtPositioning 5.12
import QtLocation 5.12

Item {
    id: cancel
    anchors.fill: parent
    property int bookingId: 0

    Button {
        id: backButton
        anchors.top: parent.top
        anchors.left: parent.left
        text: "Back"

        onClicked: {
            cancel.visible = false
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
            text: "Booking ID"
        }
        SpinBox {
            id: bookingNo
            editable: true
            from: 1
        }

        Button {
            text: "Cancel Appointment"
            Layout.columnSpan: 2
            Layout.fillWidth: true

            onClicked: {
                var result = mainWindow.hospital.reception.cancelBooking(bookingNo)

                if(result){
                    enabled = false
                    errDialog.text = "Cancellation Succeeded!"
                    errDialog.open()
                    return
                }
                else {
                    errDialog.text = "Cancellation Failed!"
                    errDialog.informativeText = "Please try again"
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
