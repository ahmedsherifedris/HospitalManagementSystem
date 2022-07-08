import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

Item {
    id: receptionPage
    anchors.fill: parent
    visible: true

    function backClicked() {
        cLayout.visible = true
    }
    function dashboardBackClicked() {
        dashboardCLayout.visible = true
    }

    SignUp {
        id: signUpPage
        visible : false
    }
    SignIn {
        id: signInPage
        visible : false
    }

    EditPage {
        id: editPage
        visible : false
    }

    Outpatient {
        id: outpatient
        visible: false
    }

    Inpatient {
        id: inpatient
        visible: false
    }

    Emergency {
        id: emergency
        visible: false
    }

    Cancel {
        id: cancel
        visible: false
    }

    Item {
        id: treatment
        anchors.fill: parent
        visible: false

        Button {
            id: backButton
            anchors.top: parent.top
            anchors.left: parent.left
            text: "Back"

            onClicked: {
                treatment.visible = false
                parent.parent.dashboardBackClicked()
            }
        }

        GridLayout {
            id: grid
            visible: true
            anchors.top: backButton.bottom
            anchors.centerIn: parent
            columns: 2

            Button {
                text: "Start Treatment"
                Layout.columnSpan: 2
                Layout.fillWidth: true

                onClicked: {
                    treatment.getTreatment()
                }
            }
            Label {
                text: "Medicines:"
            }
            Label {
                id: medicines
                text: ""
            }
            Label {
                text: "Equipment:"
            }
            Label {
                id: equipment
                text: ""
            }
            Label {
                text: "Discount:"
            }
            Label {
                text: mainWindow.hospital.reception.getDiscount()
            }
            Label {
                text: "Total Cost:"
            }
            Label {
                id: totalCost
                property real cost: 0
                text: (cost - mainWindow.hospital.reception.getDiscount() )
            }
            Button {
                text: "Make Payment"
                Layout.columnSpan: 2
                Layout.fillWidth: true

                onClicked: {
                    var result = mainWindow.hospital.reception.makePayment( cost )

                    if(result)
                        enabled = false
                }
            }

            MessageDialog {
                id: errDialog
            }
        }
        function getTreatment() {

            var i

            var items = mainWindow.hospital.pharmacy.itemsList

            for(i = 0; i < items.length; i++){
                var qty = (Math.floor(Math.random() * 10))
                if(items[i].isDrug){
                    medicines.text += items[i].itemName += " ( "+ qty +" ), "
                }
                else{
                    equipment.text += items[i].itemName += " ( "+ qty +" ), "
                }
                totalCost.cost += items[i].cost * qty
            }
        }
    }

    Item {
        id: rating
        anchors.fill: parent
        visible: false

        Button {
            id: backButton2
            anchors.top: parent.top
            anchors.left: parent.left
            text: "Back"

            onClicked: {
                rating.visible = false
                parent.parent.dashboardBackClicked()
            }
        }

        GridLayout {
            id: grid2
            visible: true
            anchors.top: backButton2.bottom
            anchors.centerIn: parent
            columns: 2

            Label {
                text: "Booking ID: "
            }
            SpinBox {
                id: feedbackId
                from: 1
            }
            Label {
                text: "Doctor (out of 5)"
            }
            SpinBox {
                id: doctorRating
                from: 0
                to: 5
            }
            Label {
                text: "Pharmacy (out of 5)"
            }
            SpinBox {
                id: pharmacyRating
                from: 0
                to: 5
            }
            Label {
                text: "Room (out of 5)"
            }
            SpinBox {
                id: roomRating
                from: 0
                to: 5
            }
            Label {
                text: "Reception (out of 5)"
            }
            SpinBox {
                id: receptionRating
                from: 0
                to: 5
            }
            Label {
                text: "Hospital (out of 5)"
            }
            SpinBox {
                id: hospitalRating
                from: 0
                to: 5
            }
            Button {
                id: submitRating
                text: "Submit"
                Layout.columnSpan: 2
                onClicked: {
                    mainWindow.hospital.reception.feedback(
                                feedbackId.value,
                                doctorRating.value,
                                pharmacyRating.value,
                                roomRating.value,
                                receptionRating.value,
                                hospitalRating.value
                                )
                    submitRating.enabled = false
                }
            }
        }
    }

    ColumnLayout {
        id: cLayout
        anchors.centerIn: parent
        Button {
            text: "Signup"

            onClicked: {
                cLayout.visible = false
                signUpPage.visible = true
            }
        }
        Button {
            text: "Signin"
            onClicked: {
                cLayout.visible = false
                signInPage.visible = true
            }
        }
    }

    ColumnLayout {
        id: dashboardCLayout
        visible: false
        anchors.centerIn: parent
        Button {
            text: "View/Edit Profile"
            onClicked: {
                dashboardCLayout.visible = false
                editPage.visible = true
            }
        }
        Button {
            text: "Book Outpatient"
            onClicked: {
                dashboardCLayout.visible = false
                outpatient.visible = true
            }
        }

        Button {
            text: "Book Inpatient"
            onClicked: {
                dashboardCLayout.visible = false
                inpatient.visible = true
            }
        }

        Button {
            text: "Book Emergency"
            onClicked: {
                dashboardCLayout.visible = false
                emergency.visible = true
            }
        }

        Button {
            text: "Cancel Booking"
            onClicked: {
                dashboardCLayout.visible = false
                cancel.visible = true
            }
        }

        Button {
            text: "Get Treatment"
            onClicked: {
                dashboardCLayout.visible = false
                treatment.visible = true
            }
        }

        Button {
            text: "Give Feedback"
            onClicked: {
                dashboardCLayout.visible = false
                rating.visible = true
            }
        }
    }
}
