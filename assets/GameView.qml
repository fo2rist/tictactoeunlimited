import bb.cascades 1.0

Page {
    onCreationCompleted: game.initializeGame(gameField)
    
    Container {
        layout: DockLayout {
        }

        // Background ImageView
        ImageView {
            imageSource: "asset:///images/bg4.png"
        }
        
	    Container {
	        id: gameField
	        
	        Label {
	            text: "    Tic tac toe"
                textStyle.fontSize: FontSize.Large
            }
	    }
    }
}
