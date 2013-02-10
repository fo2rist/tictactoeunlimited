// Drilldown navigation project template
import bb.cascades 1.0

NavigationPane {
    id: navigationPane
    
    onCreationCompleted: {
        //DEBUG
        playButton.clicked()
    }

    onPopTransitionEnded: {
        page.destroy();
    }
        
    attachedObjects: [
        ComponentDefinition {
            id: gamePageDefinition;
            source: "GameView.qml"
        },
        ComponentDefinition {
            id: settingsPageDefinition;
            source: "SettingsView.qml"
        }
    ]

    peekEnabled: false

    Page {
        Container {
	        layout: DockLayout {
            }

            // Background ImageView
            ImageView {
	            imageSource: "asset:///images/bg5.png"
	        }
		    
		    Container {
		        id: menuContainer
	            horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Fill
                topMargin: 480

                Button {
	                id: playButton_6_6
	                text: "Play 6x6"
	                onClicked: {
	                    var page = gamePageDefinition.createObject();
                        page.gameWidth = 6;
                        page.gameHeight = 6;
                        page.initializeGame();
                        navigationPane.push(page);
                    } 
	            }
                Button {
	                id: playButton_6_10
	                text: "Play 6x10"
	                onClicked: {
	                    var page = gamePageDefinition.createObject();
                        page.gameWidth = 6;
                        page.gameHeight = 10;
                        page.initializeGame();
                        navigationPane.push(page);
	                } 
	            }
                Button {
	                id: playButton_8_14
	                text: "Play 8x14"
	                onClicked: {
	                    var page = gamePageDefinition.createObject();
                        page.gameWidth = 8;
                        page.gameHeight = 14;
                        page.initializeGame();
                        navigationPane.push(page);
                    } 
	            }
                
                //Separator
                Container {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1
                    }
                }

                Button {
		            id: settingsButton
	                text: "Settings"
	                onClicked: {
	                    var page = settingsPageDefinition.createObject();
	                    navigationPane.push(page);
	                }
                }
            }
		}
	}

}
