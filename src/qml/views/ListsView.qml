import QtQuick 
import QtQuick.Controls
import QtQuick.Layouts
import Lali.Types

import "../components"

RowLayout {
    anchors.fill: parent
    Rectangle {
        id: listSelector
        color: "#3a3a3a"
        implicitWidth: 256
        implicitHeight: parent.height
        property string selectedList: app.listsNames[0]
        
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 8
            
            RowLayout {
                Layout.topMargin: 16
                Layout.bottomMargin: 16
                Label {
                    text: "Lists"
                }
                
                Item { Layout.fillWidth: true }
                
                Image {
                    sourceSize.width: 24
                    sourceSize.height: 24
                    fillMode: Image.PreserveAspectFit
                    source: "/qml/images/add.svg"
                    
                    
                    MouseArea {
                        property bool hovered: false
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            newListNameDialog.open();
                        }
                    }
                }
            }
            
            Repeater {
                model: app.listsNames
                
                Rectangle {
                    id: button
                    property string text: modelData
                    property bool selected: modelData === listSelector.selectedList
                    signal clicked
                    
                    Layout.alignment: Qt.AlignTop
                    color: ma.hovered || selected ? "#444444" : "transparent"
                    radius: 8
                    implicitHeight: 32
                    implicitWidth: parent.width
                    
                    MouseArea {
                        id: ma
                        property bool hovered: false
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            listSelector.selectedList = modelData
                            app.selectListByName(modelData);
                            button.clicked();
                        }
                        
                        hoverEnabled: true
                        
                        onEntered: {
                            hovered = true
                        }
                
                        onExited: {
                            hovered = false
                        }
                    }
                    
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 8
                        text: button.text
                        color: "#CCCCCC"
                        font.pixelSize: 14
                    }
                }
            }
            
            Item { Layout.fillHeight: true }
        }
    }

    ColumnLayout {
        
        RowLayout {
            Layout.alignment: Qt.AlignTop
            Layout.margins: 16
            Layout.bottomMargin: 0
            
            Label {
                Layout.alignment: Qt.AlignTop
                text: `${app.selectedList.name}`
                color: "white"
                font.pixelSize: 24
            }
            
            Item { Layout.fillWidth: true }

            Image {
                sourceSize.width: 24
                sourceSize.height: 24
                fillMode: Image.PreserveAspectFit
                source: "/qml/images/settings.svg"
                
                
                MouseArea {
                    property bool hovered: false
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        listEditForm.setListToEdit(app.selectedList)
                        listEditForm.open();
                    }
                }
            }
        }
        
        Label {
            Layout.alignment: Qt.AlignTop
            Layout.margins: 16
            Layout.topMargin: 0
            Layout.bottomMargin: 0
            text: `${app.selectedList.animes.length} anime(s)`
            color: "white"
            font.pixelSize: 16
        }
        
        Rectangle {
            Layout.alignment: Qt.AlignTop
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"
            
            AnimeList {
                list: app.selectedList
            }
        }
    }
    
    Dialog {
        id: newListNameDialog
        modal: true
        width: 400
        x: (parent.width - width) / 2
        y: (parent.height - height) / 3
        
        ColumnLayout {
            Label {
                text: "New list name:"
            }

            AniTextField {
                id: newListName
                Layout.preferredWidth: 200
                Layout.preferredHeight: 32
            }
            
            Button {
                text: "Create"
                onClicked: {
                    app.createList(newListName.text);
                    newListNameDialog.close();
                }
            }
        }
    }
    
    Dialog {
        id: listEditForm
        modal: true
        width: 400
        x: (parent.parent.width - width) / 2
        y: (parent.parent.height - height) / 3
        
        function setListToEdit (list) {
            listForm.list = list
        }
        
        ListForm {
            id: listForm
            onSave: function (list) {
                listEditForm.close()
                listSelector.selectedList = list.name
            }
            onDeleteList: {
                listEditForm.close()
                deleteConfirmation.open()
            }
        }
    }
    
    Dialog {
        id: deleteConfirmation
        modal: true
        width: 400
        x: (parent.parent.width - width) / 2
        y: (parent.parent.height - height) / 3
        
        ColumnLayout {
            Label {
                text: "Do you really want to delete this list ?"
            }
            
            Button {
                text: "Yes"
                onClicked: {
                    app.deleteList(listSelector.selectedList);
                    deleteConfirmation.close();
                }
                
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: "#ff0000"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    
                }
            }
            
            Button {
                text: "No"
                onClicked: {
                    deleteConfirmation.close();
                }
                
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: "#00ff00"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    
                }
            }
        }
    }
}
