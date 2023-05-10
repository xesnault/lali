import QtQuick 
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import Lali.App

import "views"
import "components"

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Lali")
    color: "#444444"
    
    Component.onCompleted: {
        app.loadLists();
    }
    
    property string currentPage: "lists"
    
    App {
        id: app
    }
    
    RowLayout {
        anchors.fill: parent
        spacing: 0
        
        Rectangle {
            Layout.alignment: Qt.AlignLeft
            color: "#333333"
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: 96
        
            ColumnLayout {
                
                anchors.fill: parent
                anchors.topMargin: 32
                anchors.bottomMargin: 16
                spacing: 32
                
                SideBarButton {
                    Layout.preferredHeight: 84
                    Layout.preferredWidth: 64
                    Layout.alignment: Qt.AlignCenter | Qt.AlignTop
                    text: "Lists"
                    image: "/qml/images/lists.svg"
                    onClicked: {
                        currentPage = "lists"
                    }
                    selected: currentPage == "lists"
                }
                
                SideBarButton {
                    Layout.preferredHeight: 84
                    Layout.preferredWidth: 64
                    Layout.alignment: Qt.AlignCenter | Qt.AlignTop
                    text: "Search"
                    image: "/qml/images/search.svg"
                    onClicked: {
                        currentPage = "search"
                    }
                    selected: currentPage == "search"
                }

                Item { Layout.fillHeight: true } 
                
                SideBarButton {
                    Layout.preferredHeight: 84
                    Layout.preferredWidth: 64
                    Layout.alignment: Qt.AlignCenter | Qt.AlignTop
                    text: "Import"
                    image: "/qml/images/import.svg"
                    onClicked: {
                        pickList.open()
                    }
                }
                
                Dialog {
                    id: pickList
                    modal: true
                    width: 400
                    
                    ColumnLayout {
                        Label {
                            text: "This is a small experimental utility to import your lists from AniList."
                        }
                        
                        Label {
                            text: "AniList user name:"
                        }
            
                        AniTextField {
                            id: anilistUserName
                            Layout.preferredWidth: 200
                            Layout.preferredHeight: 32
                        }
                        
                        Label {
                            text: "AniList list name:"
                        }
                        
                        AniTextField {
                            id: anilistListName
                            Layout.preferredWidth: 200
                            Layout.preferredHeight: 32
                        }
                        
                        Label {
                            text: "New local list name:"
                        }
                        
                        AniTextField {
                            id: targetListName
                            Layout.preferredWidth: 200
                            Layout.preferredHeight: 32
                        }
                        
                        Button {
                            text: "Import"
                            onClicked: {
                                app.importFromAnilist(anilistUserName.text, anilistListName.text, targetListName.text);
                            }
                        }
                    }
                }

            }

        }
            
        ColumnLayout {
            Layout.alignment: Qt.AlignLeft
            
            Rectangle {
                visible: currentPage === "lists"
                enabled: currentPage === "lists"
                Layout.alignment: Qt.AlignTop
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "transparent"
                
                ListsView {
                    
                }
            }
            
            Rectangle {
                visible: currentPage === "search"
                enabled: currentPage === "search"
                Layout.alignment: Qt.AlignTop
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "transparent"
                
                SearchView {
                    
                }
            }
        }
    }
}



