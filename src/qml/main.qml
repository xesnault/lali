import QtQuick 
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import Lali.App
import Lali.Types

import "views"
import "components" as Components

Window {
	id: root
	width: 640
	height: 480
	visible: true
	title: qsTr("Lali")
	color: "#444444"
	
	Component.onCompleted: {
		_app.loadLists()
	}
	
	property string currentPage: "lists"
	
	RowLayout {
		anchors.fill: parent
		spacing: 0
		
		Rectangle {
			Layout.alignment: Qt.AlignLeft
			color: "#333333"
			Layout.preferredHeight: parent.height
			Layout.preferredWidth: 96
			
			ColumnLayout {
				
				anchors.fill: parent
				anchors.topMargin: 32
				anchors.bottomMargin: 16
				spacing: 32
				
				Components.SideBarButton {
					Layout.preferredHeight: 84
					Layout.preferredWidth: 64
					Layout.alignment: Qt.AlignCenter | Qt.AlignTop
					text: "Lists"
					image: "/qml/images/lists.svg"
					onClicked: {
						currentPage = "lists"
					}
					selected: currentPage == "lists"
				}
				
				Components.SideBarButton {
					Layout.preferredHeight: 84
					Layout.preferredWidth: 64
					Layout.alignment: Qt.AlignCenter | Qt.AlignTop
					text: "Search"
					image: "/qml/images/search.svg"
					onClicked: {
						currentPage = "search"
					}
					selected: currentPage == "search"
				}
				
				Item { Layout.fillHeight: true } 
				
				Components.SideBarButton {
					Layout.preferredHeight: 84
					Layout.preferredWidth: 64
					Layout.alignment: Qt.AlignCenter | Qt.AlignTop
					text: "Import"
					image: "/qml/images/import.svg"
					onClicked: {
						pickList.open()
					}
				}
				
				Components.Modal {
					id: pickList
					
					Connections {
						target: _app
						function onImportStatusChanged() {
							if (_app.importStatus === Status.Completed) {
								pickList.close();
								_app.importStatus = NONE;
							}
						}
					}
					
					ColumnLayout {
						Label {
							text: "This is a small experimental utility to import your lists from AniList."
						}
						
						Label {
							text: "AniList user name:"
						}
						
						Components.TextField {
							id: anilistUserName
							Layout.preferredWidth: 200
							Layout.preferredHeight: 32
						}
						
						Label {
							text: "AniList list name:"
						}
						
						Components.TextField {
							id: anilistListName
							Layout.preferredWidth: 200
							Layout.preferredHeight: 32
						}
						
						Label {
							text: "New local list name:"
						}
						
						Components.TextField {
							id: targetListName
							Layout.preferredWidth: 200
							Layout.preferredHeight: 32
						}
						
						Components.HorizontalSpacer { height: 16 }
						
						Components.Button {
							enabled: _app.importStatus !== Status.InProgress
							text: _app.importStatus !== Status.InProgress ? "Import" : "Importing..."
							onClicked: {
								_app.importFromAnilist(anilistUserName.text, anilistListName.text, targetListName.text);
							}
						}
					}
				}
				
			}
			
		}
		
		ColumnLayout {
			Layout.alignment: Qt.AlignLeft
			
			Rectangle {
				visible: currentPage === "lists"
				enabled: currentPage === "lists"
				Layout.alignment: Qt.AlignTop
				Layout.fillHeight: true
				Layout.fillWidth: true
				color: "transparent"
				
				ListsView {
					
				}
			}
			
			Rectangle {
				visible: currentPage === "search"
				enabled: currentPage === "search"
				Layout.alignment: Qt.AlignTop
				Layout.fillHeight: true
				Layout.fillWidth: true
				color: "transparent"
				
				SearchView {
					
				}
			}
		}
	}
}



