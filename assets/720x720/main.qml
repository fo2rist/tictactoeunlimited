// Drilldown navigation project template
import bb.cascades 1.0

NavigationPane {
    id: navigationPane

    onPopTransitionEnded: {
        page.destroy();
    }
        
    attachedObjects: [
        ComponentDefinition {
            id: gamePageDefinition;
            source: "GameView.qml"
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
	                id: playButton_8_8
                    defaultImageSource: "asset:///images/8x8.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    onClicked: {
	                    var page = gamePageDefinition.createObject();
                        page.gameWidth = 8;
                        page.gameHeight = 8;
                        page.initializeGame();
                        navigationPane.push(page);
	                } 
	            }
                ImageButton {
	                id: playButton_9_9
                    defaultImageSource: "asset:///images/9x9.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    onClicked: {
	                    var page = gamePageDefinition.createObject();
                        page.gameWidth = 9;
                        page.gameHeight = 9;
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
            }
		}
	}

}
