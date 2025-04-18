import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15 
import todo 0.1

import "components"

ApplicationWindow {
    id: win
    title: "Profile"

    width: 1500
    height: 750
    minimumWidth: 500
    minimumHeight: 250

    visible: true
    color: "#0C121D"

    Component.onCompleted: {
        taskHandler.setUser()
    }

    GridLayout {
        anchors.fill: parent  
        anchors.margins: 10

        rows: 2
        columns: 2

        rowSpacing: 10
        columnSpacing: 10

        // tasks background
        Rectangle {
            id: tasksBackground

            Layout.row: 0
            Layout.column: 0

            Layout.fillWidth: true
            Layout.fillHeight: true

            radius: 12.5
            color: "#222B3B"

            //TODO fix tid 
            Item {
                id: ilv
                anchors.centerIn: parent

                width: parent.width
                height: parent.height - 20 

                clip: true
                ListView {
                    id: lv
                    objectName: "lv"
                    model: taskHandler.lvtask() 

                    anchors.fill: parent
                    anchors.bottomMargin: index == lv.model ? 0 : 10
                    spacing: 10

                    snapMode: ListView.SnapOneItem
                    property int tid: -1

                    delegate: Task {
                        taskName: name
                        taskText: text
                        taskStatus: status

                        width: ListView.view.width - 20
                        height: 100

                        anchors.horizontalCenter: parent.horizontalCenter

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                lv.tid = index
                                //? test
                                // taskHandler.setPickedID(index)
                            }
                        }
                    }
                }
            }
        } // tasks background   

        // profile button
        ProfileButton {
            Layout.row: 0
            Layout.column: 1

            Layout.alignment: Qt.AlignTop
        } // profile button

        // task managment buttons
        Rectangle {
            Layout.row: 1
            Layout.column: 0

            Layout.fillWidth: true
            Layout.preferredHeight: 50 

            color: "transparent"

            RowLayout {
                anchors.fill: parent
                spacing: 10

                AddTask {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height
                }

                RemTask {
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height

                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            taskHandler.delTask(lv.tid)
                            lv.tid = -1
                            //? test
                            // taskHandler.delTask(taskHandler.getPickedID())
                            // taskHandler.setPickedID(-1)
                        } 
                    }
                }
            }
        } // task managment buttons
    }
}
