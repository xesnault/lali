import QtQuick 
import QtQuick.Controls
import QtQuick.Layouts

import "../components"

ColumnLayout {
    anchors.fill: parent

    RowLayout {
        Layout.alignment: Qt.AlignTop
        Layout.margins: 16
        
        ComboBox {
            id: listSelector
            Layout.preferredWidth: 200
            implicitHeight: 32
            model: app.listsNames
            onCurrentTextChanged: {
                app.selectListByName(currentText);
            }

            background: Rectangle {
                radius: 4
                anchors.fill: parent
                color : "grey"
                smooth: true
            }
            contentItem: Text {
                anchors.fill: parent
                anchors.margins: 8
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                text: parent.displayText
                font.bold: true
                color: "white"
            }
        }
        
        Item { Layout.fillWidth: true }
        
        AniButton {
            text: "Delete"
            textColor: "red"
            
            onClicked: {
                deleteConfirmation.open();
            }
        }
        
        Dialog {
            id: newListNameDialog
            modal: true
            width: 400
            x: (parent.parent.width - width) / 2
            y: (parent.parent.height - height) / 3
            
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
                        app.deleteList(listSelector.currentText);
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
        
        AniButton {
            text: "New"
            textColor: "#00ff00"
            
            onClicked: {
                newListNameDialog.open();
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
