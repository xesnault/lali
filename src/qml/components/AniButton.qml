import QtQuick 
import QtQuick.Controls 2.0

Button {
    property string textColor: "white"
    property string bgColor: "grey"
    text: "Delete"
    implicitHeight: 32
    
    contentItem: Text {
        text: parent.text
        font: parent.font
        color: textColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        color: bgColor
        radius: 2
    }
}
