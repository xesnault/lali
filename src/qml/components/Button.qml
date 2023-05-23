import QtQuick 
import QtQuick.Controls as QtQuick

QtQuick.Button {
	property string textColor: "white"
	property string bgColor: "#666666"
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
		radius: 4
	}
	
	HoverHandler {
		cursorShape: Qt.PointingHandCursor
	}
}
