import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import Lali.Types

Rectangle {
    property AnimeQML anime
    color: "#333333"
    radius: 16
    
    RowLayout {
        
        anchors.fill: parent
        
        Image {
            property bool cachedImageFound: true
            Layout.alignment: Qt.AlignLeft
            Layout.preferredWidth: parent.parent.height * 0.66
            Layout.preferredHeight: parent.parent.height
            fillMode: Image.PreserveAspectCrop
            asynchronous: true
            source: anime?.cachedImage || ""
            
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
                width: 500
                height: 500
                radius: 16
                visible: false
            }
        }
        
        ColumnLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft
            Layout.margins: 16
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
            
            Label {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                text: anime?.description || "[No description given]"
                wrapMode: Text.Wrap
                color: "white"
            }
            
            Item { Layout.fillHeight: true } 
        }
        
    }
}
