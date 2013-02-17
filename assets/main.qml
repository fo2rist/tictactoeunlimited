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
	            horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                topMargin: 480

	            ImageView {
	                imageSource: "asset:///images/tictactoe.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    opacity: 0.5
                }
	
                ImageButton {
                    id: playButton_6_6
                    defaultImageSource: "asset:///images/6x6.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    onClicked: {
	                    var page = gamePageDefinition.createObject();
                        page.gameWidth = 6;
                        page.gameHeight = 6;
                        page.initializeGame();
                        navigationPane.push(page);
                    } 
	            }
                ImageButton {
	                id: playButton_6_10
                    defaultImageSource: "asset:///images/6x10.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    onClicked: {
	                    var page = gamePageDefinition.createObject();
                        page.gameWidth = 6;
                        page.gameHeight = 10;
                        page.initializeGame();
                        navigationPane.push(page);
	                } 
	            }
                ImageButton {
	                id: playButton_8_14
                    defaultImageSource: "asset:///images/8x14.png"
                    horizontalAlignment: HorizontalAlignment.Center
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

                ImageView {
                    imageSource: "asset:///images/unlimited.png"
                    opacity: 0.5
                }

//                Button {
//		            id: settingsButton
//	                text: "Settings"
//	                onClicked: {
//	                    var page = settingsPageDefinition.createObject();
//	                    navigationPane.push(page);
//	                }
//                }
            }
		}
	}

}
