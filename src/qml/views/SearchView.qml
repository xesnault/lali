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
			placeholderText: "Enter an anime title..."
			placeholderTextColor: "#6f6f6f"
			bgColor: "#595959"
			Layout.preferredWidth: 256
			Layout.preferredHeight: 32
			
			onEditingFinished: {
				_app.searchAnimes(searchString.text);
			}
		}
		
		Components.Button {
			text: "Search"
			onClicked: {
				_app.searchAnimes(searchString.text);
			}
		}
	}
	
	Rectangle {
		Layout.alignment: Qt.AlignTop
		Layout.fillHeight: true
		Layout.fillWidth: true
		color: "transparent"
		
		Components.AnimeList {
			list: _app.searchResults
		}
	}
}
