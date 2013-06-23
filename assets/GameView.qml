import bb.cascades 1.0

Page {
    property int gameWidth;
    property int gameHeight;

    function initializeGame(multiplayer) {
        
        game.initializeGame(gameField,
            gameWidth,
            gameHeight,
            multiplayer ? 1 : 0);
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
    actions: [
        ActionItem {
            id: actionWins
            title:game.numberOfWins
            imageSource: (game.currentPlayer == 1) ? "asset:///images/ic_x_active.png" : "asset:///images/ic_x_inactive.png"
            enabled: false
            ActionBar.placement: ActionBarPlacement.OnBar
        },
        ActionItem {
            id: actionDefeats
            title: game.numberOfDefeats
            imageSource: (game.currentPlayer == 2) ? "asset:///images/ic_o_active.png" : "asset:///images/ic_o_inactive.png"
            enabled: false
            ActionBar.placement: ActionBarPlacement.OnBar
        }
    ]
}
