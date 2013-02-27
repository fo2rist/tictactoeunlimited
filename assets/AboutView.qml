import bb.cascades 1.0

Page {
    Container {
        attachedObjects: [
            Invocation {
            	id: invokeFo2ristPage
            	query {
                    mimeType: "text/html"
                    uri: "http://habrahabr.ru/users/fo2rist/"
                }
            },  
            Invocation {
            	id: invokeRwPage
            	query {
                    mimeType: "text/html"
                    uri: "http://ruswizards.com"
                }
            },  
            Invocation {
            	id: invokeDiomaPage
            	query {
                    mimeType: "text/html"
                    uri: "http://dioma.deviantart.com/"
                }
            }  
        ]

        background: Color.Black

        bottomPadding: 20.0

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
            onTouch: {
                invokeFo2ristPage.trigger("bb.action.OPEN")
            }
        }

        Label {
            text: "special thanks to"
            textStyle.color: Color.White
            horizontalAlignment: HorizontalAlignment.Center
        }
        ImageView {
        	imageSource: "asset:///images/logo_rw.png"
            horizontalAlignment: HorizontalAlignment.Center
            onTouch: {
                invokeRwPage.trigger("bb.action.OPEN")
            }
        }

        //Separator
        Container {
            layoutProperties: StackLayoutProperties {
                spaceQuota: 1
            }
        }
        Label {
            text: "Background by Dioma"
            textStyle.color: Color.White
            horizontalAlignment: HorizontalAlignment.Center
			onTouch: {
                invokeDiomaPage.trigger("bb.action.OPEN")
            }
        }
    }
}
