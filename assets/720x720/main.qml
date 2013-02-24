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
        },
        ComponentDefinition {
            id: aboutPageDefinition;
            source: "AboutView.qml"
        }
    ]

    peekEnabled: false

    Page {
        Container {
	        layout: DockLayout {
            }

            // Background ImageView
            ImageView {
	            imageSource: "asset:///images/bg.png"
	        }

            Container {
		        id: menuContainer
	            horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill

	            ImageView {
				    imageSource: "asset:///images/tictactoe.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    opacity: 0.4
                    maxHeight: 120
                    scalingMethod: ScalingMethod.AspectFit
                }
	
                ImageButton {
	                id: playButton_6_6
                    defaultImageSource: "asset:///images/6x6.png"
                    pressedImageSource: "asset:///images/6x6_pressed.png"
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
                    pressedImageSource: "asset:///images/8x8_pressed.png"
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
                    pressedImageSource: "asset:///images/9x9_pressed.png"
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

            }

            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }

                verticalAlignment: VerticalAlignment.Bottom
                horizontalAlignment: HorizontalAlignment.Right
                rightPadding: 10
                bottomPadding: 10

                ImageView {
	                imageSource: "asset:///images/unlimited.png"
	                opacity: 0.3
	                maxHeight: 60
	                scalingMethod: ScalingMethod.AspectFit
                }
	            ImageButton {
	                defaultImageSource: "asset:///images/info.png"
	                verticalAlignment: VerticalAlignment.Bottom
                    onClicked: {
                        var page = aboutPageDefinition.createObject();
                        navigationPane.push(page);
                    }
                }
            }
        }
    }
}
