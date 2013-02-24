import bb.cascades 1.0

Page {
    Container {
        background: Color.Black

        //Separator
        Container {
            layoutProperties: StackLayoutProperties {
                spaceQuota: 1
            }
        }

        Label {
			text: "Tic tac toe game by"
            textStyle.color: Color.White
            horizontalAlignment: HorizontalAlignment.Center
        }
        ImageView {
        	imageSource: "asset:///images/logo_fo2rist.png"
            horizontalAlignment: HorizontalAlignment.Center
        }

        Label {
            text: "special thanks to"
            textStyle.color: Color.White
            horizontalAlignment: HorizontalAlignment.Center
        }
        ImageView {
        	imageSource: "asset:///images/logo_rw.png"
            horizontalAlignment: HorizontalAlignment.Center
        }

        //Separator
        Container {
            layoutProperties: StackLayoutProperties {
                spaceQuota: 1
            }
        }
    }
}
