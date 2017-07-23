#include "KeyPressEater.h"
#include <QtDebug>
#include <QObject>
#include <QEvent>
#include <QKeyEvent>

bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
    qInfo() << "EVENT: " << event->type();
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qInfo("Ate key press %d", keyEvent->key());
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}