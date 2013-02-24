import bb.cascades 1.0

Page {
    Container {
        background: Color.Black

        TextArea {
			text: "Tic tac toe game by"
            textStyle.color: Color.White
        }
        ImageView {
        	imageSource: "asset:///images/logo_fo2rist.png"
        }
        TextArea {
            text: "special thanks to team"
            textStyle.color: Color.White
        }
        ImageView {
        	imageSource: "asset:///images/logo_rw.png"
        }
    }
}
