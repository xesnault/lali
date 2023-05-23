import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

Rectangle {
	property var anime
	property var title: anime.title
	property var imageUrl: anime.imageUrl
	property var cachedImagePath: anime.cachedImage
	property bool cachedImageFound: true
	
	property int imageWidth: (grid.width / grid.columns) - ((grid.columnSpacing * grid.columns) / grid.columns)
	
	Layout.preferredWidth: imageWidth
	Layout.preferredHeight: imageWidth * 1.5 + 64
	radius: 16
	color: "transparent"
	
	ColumnLayout {
		
		Image {
			Layout.alignment: Qt.AlignTop
			Layout.preferredWidth: parent.parent.width
			Layout.preferredHeight: parent.parent.height - 64
			fillMode: Image.PreserveAspectCrop
			asynchronous: true
			source: cachedImagePath
			
			signal failedToLoad
			
			onStatusChanged: {
				if (status === Image.Error && cachedImageFound === true) {
					source = imageUrl
					cachedImageFound = false
				}
			}
			
			layer.enabled: true
			layer.effect: OpacityMask {
				maskSource: mask
			}
		}
		
		Text {
			Layout.alignment: Qt.AlignTop
			Layout.preferredWidth: parent.parent.width
			text: title || "[Missing title]"
			wrapMode: Text.Wrap
			color: "white"
			font.pixelSize: 16
			font.bold: true
		}
		
		Rectangle {
			id: mask
			width: 500
			height: 500
			radius: 16
			visible: false
		}
		
	}
}
