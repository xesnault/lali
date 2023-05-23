import QtQuick 
import QtQuick.Controls
import QtQuick.Layouts
import Lali.Types

import "../components" as Components

RowLayout {
	id: animeListsView
	property var lists: _app.animeLists
	property AnimeList selectedList: _app.animelists[0]
	property int selectedListIndex: 0
	property string filterByTitle
	anchors.fill: parent
	
	Connections {
		target: _app
		function onAnimeListsChanged() {
			if (animeListsView.selectedListIndex >= _app.animeLists.length) {
				animeListsView.selectedListIndex = 0
				animeListsView.selectedList = _app.animeLists[0]
				return
			}
			animeListsView.selectedList = _app.animeLists[selectedListIndex]
		}
	}
	
	Rectangle {
		color: "#3a3a3a"
		implicitWidth: 256
		implicitHeight: parent.height
		
		
		ColumnLayout {
			anchors.fill: parent
			anchors.margins: 8
			
			RowLayout {
				
				Layout.topMargin: 16
				Layout.bottomMargin: 16
				
				Label {
					text: "Lists"
					font.pixelSize: 24
				}
				
				Item { Layout.fillWidth: true }
				
				Image {
					sourceSize.width: 24
					sourceSize.height: 24
					fillMode: Image.PreserveAspectFit
					source: "/qml/images/add.svg"
					
					
					MouseArea {
						property bool hovered: false
						anchors.fill: parent
						cursorShape: Qt.PointingHandCursor
						onClicked: {
							newListNameDialog.open();
						}
					}
				}
			}
			
			Repeater {
				model: lists.map(x => x.getName())
				
				Rectangle {
					id: button
					property string text: modelData
					property bool selected: modelData === animeListsView.selectedList.getName()
					signal clicked
					
					Layout.alignment: Qt.AlignTop
					color: ma.hovered || selected ? "#444444" : "transparent"
					radius: 8
					implicitHeight: 32
					implicitWidth: parent.width
					
					MouseArea {
						id: ma
						property bool hovered: false
						anchors.fill: parent
						cursorShape: Qt.PointingHandCursor
						onClicked: {
							animeListsView.selectedList = lists[index]
							animeListsView.selectedListIndex = index
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
						anchors.verticalCenter: parent.verticalCenter
						anchors.left: parent.left
						anchors.leftMargin: 8
						text: button.text
						color: "#CCCCCC"
						font.pixelSize: 14
					}
				}
			}
			
			Item { Layout.fillHeight: true }
		}
	}
	
	ColumnLayout {
		
		RowLayout {
			Layout.alignment: Qt.AlignTop
			Layout.margins: 16
			Layout.bottomMargin: 0
			
			Label {
				Layout.alignment: Qt.AlignTop
				text: `${animeListsView.selectedList.name}`
				color: "white"
				font.pixelSize: 24
			}
			
			Item { Layout.fillWidth: true }
			
			Image {
				sourceSize.width: 24
				sourceSize.height: 24
				fillMode: Image.PreserveAspectFit
				source: "/qml/images/settings.svg"
				
				
				MouseArea {
					property bool hovered: false
					anchors.fill: parent
					cursorShape: Qt.PointingHandCursor
					onClicked: {
						listEditForm.setListToEdit(animeListsView.selectedList)
						listEditForm.open();
					}
				}
			}
		}
		
		Label {
			Layout.alignment: Qt.AlignTop
			Layout.margins: 16
			Layout.topMargin: 0
			Layout.bottomMargin: 0
			text: `${animeListsView.selectedList.getAnimes().length} anime(s)`
			color: "white"
			font.pixelSize: 16
		}
		
		Components.TextField {
			id: searchString
			placeholderText: "Filter by title..."
			placeholderTextColor: "#6f6f6f"
			bgColor: "#595959"
			Layout.preferredWidth: 256
			Layout.preferredHeight: 32
			Layout.margins: 16
			Layout.bottomMargin: 8
			
			onEditingFinished: {
				animeListsView.filterByTitle = searchString.text
			}
			
			onTextChanged: {
				timer.restart()
			}
			
			Timer {
				id: timer
				interval: 1000; running: false; repeat: false
				onTriggered: animeListsView.filterByTitle = searchString.text
			}
		}
		
		Rectangle {
			color: "#525252"
			height: 1
			Layout.fillWidth: true
			Layout.leftMargin: 16
			Layout.rightMargin: 16
		}
		
		Rectangle {
			Layout.alignment: Qt.AlignTop
			Layout.fillHeight: true
			Layout.fillWidth: true
			color: "transparent"
			
			
			Components.AnimeList {
				list: animeListsView.selectedList
				filterByTitle: animeListsView.filterByTitle
			}
		}
	}
	
	Components.Modal {
		id: newListNameDialog
		
		ColumnLayout {
			Label {
				text: "New list name:"
			}
			
			Components.TextField {
				id: newListName
				Layout.preferredWidth: 200
				Layout.preferredHeight: 32
			}
			
			Components.Button {
				text: "Create"
				onClicked: {
					_app.createList(newListName.text);
					newListNameDialog.close();
				}
			}
		}
	}
	
	Components.Modal {
		id: listEditForm
		function setListToEdit (list) {
			listForm.reload(list)
		}
		
		ListForm {
			id: listForm
			onSave: function (list) {
				listEditForm.close()
			}
			onDeleteList: {
				listEditForm.close()
				deleteConfirmation.open()
			}
		}
	}
	
	Components.Modal {
		id: deleteConfirmation
		ColumnLayout {
			Label {
				text: "Do you really want to delete this list ?"
			}
			
			Components.Button {
				text: "Yes"
				onClicked: {
					_app.deleteList(animeListsView.selectedList.getName());
					deleteConfirmation.close();
				}
				
				contentItem: Text {
					text: parent.text
					font: parent.font
					color: "#ff0000"
					horizontalAlignment: Text.AlignHCenter
					verticalAlignment: Text.AlignVCenter
					
				}
			}
			
			Components.Button {
				text: "No"
				onClicked: {
					deleteConfirmation.close();
				}
				
				contentItem: Text {
					text: parent.text
					font: parent.font
					color: "#00ff00"
					horizontalAlignment: Text.AlignHCenter
					verticalAlignment: Text.AlignVCenter
					
				}
			}
		}
	}
}
