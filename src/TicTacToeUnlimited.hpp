// Drilldown navigation project template
#ifndef TicTacToeUnlimited_HPP_
#define TicTacToeUnlimited_HPP_

#include <QObject>

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class TicTacToeUnlimited : public QObject
{
    Q_OBJECT
public:
    TicTacToeUnlimited(bb::cascades::Application *app);
    virtual ~TicTacToeUnlimited() {}
};

#endif /* TicTacToeUnlimited_HPP_ */