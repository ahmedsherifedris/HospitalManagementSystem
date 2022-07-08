import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4 as Calendar
import QtQuick.Dialogs 1.2

import Qt.labs.qmlmodels 1.0

import QtQuick.Layouts 1.12
import QtPositioning 5.12
import QtLocation 5.12

Item {
    id: emergency
    anchors.fill: parent
    property int bookingId: 0

    Button {
        id: backButton
        anchors.top: parent.top
        anchors.left: parent.left
        text: "Back"

        onClicked: {
            emergency.visible = false
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
            text: "Choose Date" ;
        }
        Button {
            id: dateButton
            checkable: true
            text: Qt.formatDate( calendar.selectedDate , "dd-MM-yyyy"  )
        }

        Calendar.Calendar {
            id: calendar;
            visible: dateButton.checked
            Layout.columnSpan: 2 ;
            minimumDate: new Date();
            maximumDate: new Date(2023,0,1)
            onClicked: {
                dateButton.checked = false
                refreshModel()
            }
        }
        ListView {
            id: doctorList
            visible: !dateButton.checked
            Layout.preferredWidth: calendar.implicitWidth
            Layout.preferredHeight: calendar.implicitHeight
            Layout.columnSpan: 2 ;
            clip: true
            highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
            focus: true

            model :
                ListModel {
                id: doctorModel

            }
            delegate:
                RowLayout {
                id: row
                width: doctorList.width
                anchors.margins: 3
                Text {
                    text: doctor
                    Layout.fillWidth: true
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            doctorList.currentIndex = index
                        }
                    }
                }
                Text {
                    text: rating
                }
            }
        }

        Button {
            text: "Book Appointment"
            Layout.columnSpan: 2
            Layout.fillWidth: true

            onClicked: {
                bookingId = mainWindow.hospital.reception.bookEmergency(
                            mainWindow.hospital.reception.username, doctorModel.get(doctorList.currentIndex).doctor, Qt.formatDate( calendar.selectedDate , "dd-MM-yyyy"  ) )
                if(bookingId === 0){
                    errDialog.text = "Booking Failed!"
                    errDialog.informativeText = "Please try again"
                    errDialog.open()
                    return;
                }

                errDialog.text = "Booking Success!"
                errDialog.informativeText = "Your Booking ID is " + bookingId + ". Please Note it down for reference"
                errDialog.open()

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
            text: "<h2> Booking Invoice </h2>"
            Layout.columnSpan: 2
        }
        Label {
            text: "<b> Booking Id : </b>"
        }
        Label {
            text: bookingId
        }
        Label {
            text: "<b> Doctor's Fees : </b>"
        }
        Label {
            text: doctorModel.get(doctorList.currentIndex).fee
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
            text: ( doctorModel.get(doctorList.currentIndex).fee - mainWindow.hospital.reception.getDiscount() )
        }
        Button {
            Layout.columnSpan: 2
            text: "Make Payment"
            onClicked : {
                console.debug(bookingId, doctorModel.get(doctorList.currentIndex).fee )
                var result = mainWindow.hospital.reception.makePayment(bookingId, doctorModel.get(doctorList.currentIndex).fee)

                if(result)
                    enabled = false
            }
        }

    }

    function refreshModel(){
        doctorModel.clear()

        doctorModel.append( mainWindow.hospital.emergencyRoom.doctors )

        for(var i = 0; i < doctorModel.count; i++){

            if( !mainWindow.hospital.reception.checkAvailability( doctorModel.get(i).doctor , Qt.formatDate( calendar.selectedDate , "dd-MM-yyyy"  ) ) )
                doctorModel.remove(i)
        }

        listModelSort( doctorModel, function compareNumbers( a, b ) { return a.rating - b.rating } )
    }

    function listModelSort(listModel, compareFunction) {
            let indexes = [ ...Array(listModel.count).keys() ]
            indexes.sort( (a, b) => compareFunction( listModel.get(a), listModel.get(b) ) )
            let sorted = 0
            while ( sorted < indexes.length && sorted === indexes[sorted] ) sorted++
            if ( sorted === indexes.length ) return
            for ( let i = sorted; i < indexes.length; i++ ) {
                listModel.move( indexes[i], listModel.count - 1, 1 )
                listModel.insert( indexes[i], { } )
            }
            listModel.remove( sorted, indexes.length - sorted )
        }

    Component.onCompleted: refreshModel()
}
