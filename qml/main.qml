import QtQuick 2.6
import QtQuick.Controls 2.0

import QtMultimedia 5.15

import Hospital 1.0

ApplicationWindow {
    id: rootWindow
    width: 480
    height: 640
    visible: true

    property alias mainWindow: rootWindow
    property alias hospital: _hospital

    Audio {
        source: "qrc:/salaamtak.mp3"
        loops: 1

        Component.onCompleted:
            play()
    }

    Hospital {
        id: _hospital
    }

    ReceptionPage {

    }
}
