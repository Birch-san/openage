#include "KeyPressEater.h"
#include <QtDebug>
#include <QObject>
#include <QEvent>
#include <QKeyEvent>

bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
    qDebug() << "EVENT";
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug("Ate key press %d", keyEvent->key());
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}