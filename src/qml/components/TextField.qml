import QtQuick
import QtQuick.Controls as QtQuick

QtQuick.TextField {
	property string textColor: "white"
	property string bgColor: "#494949"
	color : textColor
	background: Rectangle {
		color: bgColor
		radius: 4
	}
}
