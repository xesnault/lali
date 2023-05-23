import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Lali.Types

import "../components" as Components

ColumnLayout {
	
	property AnimeList list
	property var closeForm
	
	signal save(AnimeList list)
	signal deleteList
	
	function reload(listToLoad) {
		list = listToLoad
		listName.text = list.name
	}
	
	Label {
		text: "Name"
	}
	
	Components.TextField {
		id: listName
		Layout.preferredWidth: 200
		Layout.preferredHeight: 32
	}
	
	Rectangle {
		Layout.fillWidth: true
		height: 16
		color: "transparent"
	}
	
	Components.Button {
		id: saveButton
		text: "Save"
		bgColor: "green"
		onClicked: {
			let oldName = list.name
			list.setName(listName.text)
			_app.updateList(oldName, list)
			parent.save(list)
		}
	}
	
	Components.HorizontalSpacer { height: 16 }
	
	Label {
		text: "Danger zone"
		color: "red"
	}
	
	Rectangle {
		Layout.fillWidth: true
		height: 1
		color: "red"
	}
	
	Components.Button {
		text: "DELETE LIST"
		textColor: "white"
		bgColor: "red"
		
		onClicked: {
			parent.deleteList()
		}
	}
}
