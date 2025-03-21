import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    objectName: "profile"
    property string username: regHandler.getQUsername()
    
    width: 130
    height: 50

    radius: 10

    color: "#2f3842"

    Row {
        width: parent.width
        height: parent.height 

        spacing: 5
        leftPadding: 5

        anchors.centerIn: parent

        //! user icon
        Item {
            width: 40
            height: 40
            
            anchors.verticalCenter: parent.verticalCenter

            Rectangle {
                width: 40
                height: 40

                radius: 40
                color: "#ffffff"

                anchors.verticalCenter: parent.verticalCenter

                Image {
                    width: 40
                    height: 40

                    anchors.verticalCenter: parent.verticalCenter

                    source: "qrc:/ui/assets/images/profile.png"
                }
            }
        }

        Column {
            leftPadding: 10
            //! username
            Item {
                width: 80
                height: 25

                Text {
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter

                    text: username

                    color: "#ffffff"
                    
                    font.pixelSize: 12
                    font.bold: true
                }
            }

            //! logout button
            Item {
                width: 80
                height: 25

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        regHandler.logoutUser()
                        username: ""
                    }
                }


                Row {
                    height: parent.height 
                    width: parent.width

                    spacing: 5
                    rightPadding: 5

                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        height: 20
                        anchors.verticalCenter: parent.verticalCenter

                        text: "logout"
                        
                        color: "#ffffff"
                        
                        font.pixelSize: 12
                        font.bold: true
                    }

                    Rectangle {
                        width: 20
                        height: 20

                        radius: 5
                        color: "#ffffff"

                        Image {
                            width: 20
                            height: 20

                            anchors.verticalCenter: parent.verticalCenter

                            source: "qrc:/ui/assets/images/leave.png"
                        }
                    }
                }
            }
        }
    }
}