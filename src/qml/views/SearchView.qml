import QtQuick 
import QtQuick.Controls
import QtQuick.Layouts

import "../components"

ColumnLayout {
    anchors.fill: parent

    RowLayout {
        Layout.alignment: Qt.AlignTop
        Layout.margins: 16
       
        AniTextField {
            id: searchString
            Layout.preferredWidth: 200
            Layout.preferredHeight: 32

            onEditingFinished: {
                app.searchAnimes(searchString.text);
            }
        }
        
        AniButton {
            text: "Search"
            onClicked: {
                app.searchAnimes(searchString.text);
            }
        }
    }
    
    Rectangle {
        Layout.alignment: Qt.AlignTop
        Layout.fillHeight: true
        Layout.fillWidth: true
        color: "transparent"
        
        AnimeList {
            list: app.searchResults
        }
    }
}
