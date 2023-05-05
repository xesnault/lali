import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Lali.Types
import "../components"

ColumnLayout {
    
    property ListQML list
    property var closeForm
    
    signal save(ListQML list)
    signal deleteList
    
    onListChanged: {
        listName.text = list.name
    }
    
    Label {
        text: "Name"
    }
    
    AniTextField {
        id: listName
        Layout.preferredWidth: 200
        Layout.preferredHeight: 32
    }
    
    AniButton {
        id: saveButton
        text: "Save"
        bgColor: "green"
        onClicked: {
            let oldName = list.name
            list.name = listName.text
            app.updateList(oldName, list)
            parent.save(list)
        }
    }
    
    Rectangle {
        height: 16
        color: "transparent"
    }
    
    Label {
        text: "Danger zone"
        color: "red"
    }
    
    Rectangle {
        Layout.fillWidth: true
        height: 1
        color: "red"
    }
    
    AniButton {
        text: "DELETE LIST"
        textColor: "white"
        bgColor: "red"
        
        onClicked: {
            parent.deleteList()
        }
    }
}
