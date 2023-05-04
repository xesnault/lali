import QtQuick 
import QtQuick.Controls
import QtQuick.Layouts
import Lali.Types

ScrollView {
    id: scroller
    
    property ListQML list
    property AnimeQML selectedAnime
    
    anchors.fill: parent
    clip : true
    ScrollBar.vertical.policy: ScrollBar.AlwaysOn
    contentHeight: grid.height
    
    
    Rectangle {
        anchors.fill: parent
        anchors.margins: 16
        color: "transparent"
        
        GridLayout {
            property int animeCardWidth: 256 // Yes, this is an arbitrary number, "because it looks good on my computer"
            id: grid
            columns: grid.width / animeCardWidth 
            rows: 300
            width: parent.width
            columnSpacing: 32
            rowSpacing: 32

            Repeater {
                model: list?.animes || []

                AnimeCard {
                    anime: modelData
                    
                    MouseArea {
                        anchors.fill: parent
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        cursorShape: Qt.PointingHandCursor
                        onClicked: (mouse) => {
                            selectedAnime = modelData
                            if (mouse.button === Qt.LeftButton) {
                                animeInfo.open()
                            } else if (mouse.button === Qt.RightButton) {
                                contextMenu.popup()
                            } 
                        }
                    }
                }
            }
            
            // Autofill blanks
            Repeater {
                model: {
                    if (!list) {
                        return []
                    }
                    let blanks = []
            
                    for (let i = list.animes.length; i < grid.columns; i++) {
                        blanks.push(null)
                    }
                 
                    return blanks
                }

                Rectangle {
                    width: grid.animeCardWidth
                }
            }
        }
    }
    
    Dialog {
        id: animeInfo
        parent: root.contentItem
        modal: true
        width: root.width * 0.75
        x: (root.width - width) / 2
        y: 128
        padding: 16
        
        background: Rectangle {
            color: "#222222"
            radius: 16
        }
        
        AnimeInfo {
            anime: selectedAnime
        }
    }
    
    Menu {
        id: contextMenu
    
        Menu {
            title: "Add to list"
            Repeater {
                model: app.listsNames
                MenuItem {
                    text: modelData
                    onClicked: {
                        app.addAnimeToList(selectedAnime, modelData)
                    }
                }
            }
        }
        
        Menu {
            title: "Move to list"
            Repeater {
                model: app.listsNames
                MenuItem {
                    text: modelData
                    onClicked: {
                        app.moveAnimeToList(selectedAnime, list.name, modelData)
                    }
                }
            }
        }
        
        MenuItem {
            text: "Remove from list"
            onClicked: {
                app.removeAnimeFromList(selectedAnime, list.name)
            }
        }
    }
}
