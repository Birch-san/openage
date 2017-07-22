#include <QObject>
#include <QEvent>

class KeyPressEater : public QObject
{
    Q_OBJECT

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};