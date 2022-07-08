QT += quick sql positioning

CONFIG += qmltypes

QML_IMPORT_NAME = Hospital
QML_IMPORT_MAJOR_VERSION = 1

QML_IMPORT_NAME = Patient
QML_IMPORT_MAJOR_VERSION = 1

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        patient/patient.cpp \
        doctor/doctor.cpp \
        hospital/department/department.cpp \
        hospital/department/opClinic.cpp \
        hospital/department/room.cpp \
        hospital/emergency/emergencyRoom.cpp \
        hospital/pharmacy/pharmacy.cpp \
        hospital/pharmacy/pharmacyItem.cpp \
        hospital/reception/booking.cpp \
        hospital/reception/roomBooking.cpp \
        hospital/reception/emergencyBooking.cpp \
        hospital/reception/opBooking.cpp \
        hospital/reception/reception.cpp \
        hospital/hospital.cpp

HEADERS += \
        patient/patient.h \
        doctor/doctor.h \
        hospital/department/department.h \
        hospital/department/opClinic.h \
        hospital/department/room.h \
        hospital/emergency/emergencyRoom.h \
        hospital/pharmacy/pharmacy.h \
        hospital/pharmacy/pharmacyItem.h \
        hospital/reception/booking.h \
        hospital/reception/roomBooking.h \
        hospital/reception/emergencyBooking.h \
        hospital/reception/opBooking.h \
        hospital/reception/reception.h \
        hospital/hospital.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =


#copydata.commands = $(COPY_DIR) $$PWD/hospital.db $$PWD/depts.json $$PWD/pharmacy.json $$PWD/emergency.json  $$OUT_PWD
#first.depends = $(first) copydata
#export(first.depends)
#export(copydata.commands)

#QMAKE_EXTRA_TARGETS += first copydata

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
