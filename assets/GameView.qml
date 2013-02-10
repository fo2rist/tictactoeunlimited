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
            imageSource: "asset:///images/bg7.png"
        }
        
        Container {
            id: gameField

            horizontalAlignment: HorizontalAlignment.Center
            Label {
                text: "    Tic tac toe"
                textStyle.fontSize: FontSize.Large
            }
        }
    }

}
