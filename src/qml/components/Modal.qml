import QtQuick
import QtQuick.Controls

Dialog {
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
}
