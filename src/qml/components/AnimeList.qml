import QtQuick 
import QtQuick.Controls
import QtQuick.Layouts
import Lali.Types

import "../components" as Components

ScrollView {
	id: scroller
	
	property AnimeList list
	property Anime selectedAnime
	property string filterByTitle
	
	anchors.fill: parent
	clip : true
	ScrollBar.vertical.policy: ScrollBar.AlwaysOn
	contentHeight: grid.height
	
	Rectangle {
		anchors.fill: parent
		anchors.margins: 16
		color: "transparent"
		
		GridLayout {
			property int animeCardWidth: 256 // Yes, this is an arbitrary number, "because it looks good on my computer"
			id: grid
			columns: grid.width / animeCardWidth 
			rows: 300
			width: parent.width
			columnSpacing: 32
			rowSpacing: 32
			
			Repeater {
				model: {
					if (!list) 
						return ;
					if (filterByTitle) {
						return list.animes.filter(anime => anime.title.toLowerCase().includes(filterByTitle.toLowerCase()))
					}
					return list.animes
				}
				
				AnimeCard {
					anime: modelData
					
					MouseArea {
						anchors.fill: parent
						acceptedButtons: Qt.LeftButton | Qt.RightButton
						cursorShape: Qt.PointingHandCursor
						onClicked: (mouse) => {
									   selectedAnime = modelData
									   if (mouse.button === Qt.LeftButton) {
										   animeInfo.open()
									   } else if (mouse.button === Qt.RightButton) {
										   contextMenu.popup()
									   } 
								   }
					}
				}
			}
			
			// Autofill blanks
			Repeater {
				model: {
					if (!list) {
						return []
					}
					let blanks = []
					
					for (let i = list.animes.length; i < grid.columns; i++) {
						blanks.push(null)
					}
					
					return blanks
				}
				
				Rectangle {
					width: grid.animeCardWidth
				}
			}
		}
	}
	
	Components.Modal {
		id: animeInfo
		width: root.width * 0.75
		x: (root.width - width) / 2
		y: 128
		
		AnimeInfo {
			anime: selectedAnime
		}
	}
	
	Menu {
		id: contextMenu
		
		Menu {
			title: "Add to list"
			Repeater {
				model: _app.animeLists.map(x => x.getName())
				MenuItem {
					text: modelData
					onClicked: {
						_app.addAnimeToList(selectedAnime, modelData)
					}
				}
			}
		}
		
		Menu {
			title: "Move to list"
			Repeater {
				model: _app.animeLists.map(x => x.getName())
				MenuItem {
					text: modelData
					onClicked: {
						_app.moveAnimeToList(selectedAnime, list.name, modelData)
					}
				}
			}
		}
		
		MenuItem {
			text: "Remove from list"
			onClicked: {
				_app.removeAnimeFromList(selectedAnime, list.name)
			}
		}
	}
}
