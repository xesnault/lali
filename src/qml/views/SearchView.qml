import QtQuick 
import QtQuick.Controls
import QtQuick.Layouts

import "../components" as Components

ColumnLayout {
    anchors.fill: parent

    RowLayout {
        Layout.alignment: Qt.AlignTop
        Layout.margins: 16
       
        Components.TextField {
            id: searchString
            bgColor: "#595959"
            Layout.preferredWidth: 200
            Layout.preferredHeight: 32

            onEditingFinished: {
                app.searchAnimes(searchString.text);
            }
        }
        
        Components.Button {
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
        
        Components.AnimeList {
            list: app.searchResults
        }
    }
}
