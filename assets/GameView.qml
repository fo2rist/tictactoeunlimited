import bb.cascades 1.0

Page {
    property int gameWidth;
    property int gameHeight;

    function initializeGame() {
        game.initializeGame(gameField, gameWidth, gameHeight)
        
    } 

    Container {
        layout: DockLayout {
        }

        // Background ImageView
        ImageView {
            imageSource: "asset:///images/bg.png"
        }
        
        Container {
            id: gameField

            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Center
        }
    }
}
