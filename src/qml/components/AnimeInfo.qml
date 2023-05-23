import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import Lali.Types

ColumnLayout {
	property Anime anime
	
	anchors.fill: parent
	Layout.alignment: Qt.AlignTop
	
	onAnimeChanged: {
		image.source = anime.cachedImage
	}
	
	RowLayout {
		
		Layout.alignment: Qt.AlignTop
		
		Image {
			id: image
			property bool cachedImageFound: true
			Layout.alignment: Qt.AlignTop | Qt.AlignLeft
			Layout.preferredHeight: 128 * 1.5
			Layout.preferredWidth: 128 
			fillMode: Image.PreserveAspectCrop
			asynchronous: true
			source: anime.cachedImage
			
			signal failedToLoad
			
			onStatusChanged: {
				if (status === Image.Error && cachedImageFound === true) {
					source = anime?.imageUrl
					cachedImageFound = false
				}
			}
			
			layer.enabled: true
			layer.effect: OpacityMask {
				maskSource: mask
			}
			
			Rectangle {
				id: mask
				width: 128
				height: 128
				radius: 8
				visible: false
			}
		}
		
		ColumnLayout {
			Layout.fillWidth: true
			Layout.alignment: Qt.AlignLeft | Qt.AlignTop
			Layout.leftMargin: 16
			spacing: 32
			
			// Missing status and genres
			
			Label {
				Layout.fillWidth: true
				Layout.alignment: Qt.AlignTop
				text: anime?.title || "[Missing title]"
				wrapMode: Text.Wrap
				color: "white"
				font.pixelSize: 24
				font.bold: true
			}
			
			Label {
				Layout.fillWidth: true
				Layout.alignment: Qt.AlignTop
				text: `${anime?.startDay}/${anime?.startMonth}/${anime?.startYear} - ${anime?.endDay}/${anime?.endMonth}/${anime?.endYear}\n${anime?.episodeCount} episode${anime?.episodeCount > 1 ? "s" : ""}`
				wrapMode: Text.Wrap
				color: "white"
			}
		}
	}
	
	Item { implicitHeight: 16 }
	
	Label {
		Layout.fillWidth: true
		Layout.alignment: Qt.AlignTop
		text: anime?.description || "[No description given]"
		wrapMode: Text.Wrap
		color: "white"
	}
}

