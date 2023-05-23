import QtQuick 
import QtQuick.Controls

Rectangle {
	id: button
	property string text
	property string image
	property bool selected
	signal clicked
	
	color: ma.hovered || selected ? "#444444" : "transparent"
	radius: 8
	
	Image {
		// anchors.fill: parent
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.top: parent.top
		anchors.topMargin: 8
		
		sourceSize.width: 48
		sourceSize.height: 48
		fillMode: Image.PreserveAspectFit
		source: image
	}
	
	MouseArea {
		id: ma
		property bool hovered: false
		anchors.fill: parent
		cursorShape: Qt.PointingHandCursor
		onClicked: {
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
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 8
		anchors.horizontalCenter: parent.horizontalCenter
		text: button.text
		color: "#AAAAAA"
		font.pixelSize: 14
	}
}
