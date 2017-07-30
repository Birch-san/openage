#include "QEventDispatcherImpl.h"

#include <QAbstractEventDispatcher>
#include <QObject>
#include <QList>
#include <QEventLoop>
#include <QCoreApplication>
#include <QtDebug>
// #include <QWindowSystemInterface>

#include <sys/select.h>
#include <QSocketNotifier>
#include <cassert>
#include <QThread>

//#include <QtGlobal>

namespace qtsdl {

qtsdl::QEventDispatcherImpl::QEventDispatcherImpl(QObject *parent)
  : QAbstractEventDispatcher(parent) {
}

qtsdl::QEventDispatcherImpl::~QEventDispatcherImpl() {
}

/**
* Mostly I am copying from (MIT License, peper0@GitHub):
* https://github.com/peper0/qtasio/blob/master/qasioeventdispatcher.cpp
* https://github.com/peper0/qtasio/blob/master/qasioeventdispatcher.h
*/
bool qtsdl::QEventDispatcherImpl::processEvents(QEventLoop::ProcessEventsFlags flags) {
    bool had_events = false;
//    qInfo() << flags;

    while (!this->interrupted) {
        if (!(flags & QEventLoop::ExcludeSocketNotifiers))
        {
            fd_set read_fd_set;
            fd_set write_fd_set;
            fd_set except_fd_set;
            struct timeval timeout = {};
            fd_set* fd_sets[3] = {&read_fd_set, &write_fd_set, &except_fd_set};
            static_assert(QSocketNotifier::Read == 0, "QSocketNotifier::Type enum incompatible");
            static_assert(QSocketNotifier::Write == 1, "QSocketNotifier::Type enum incompatible");
            static_assert(QSocketNotifier::Exception == 2, "QSocketNotifier::Type enum incompatible");

            FD_ZERO(&read_fd_set);
            FD_ZERO(&write_fd_set);
            FD_ZERO(&except_fd_set);

            for (auto notifier : this->socket_notifiers)
                switch (notifier->type()) {
                    case QSocketNotifier::Read:
                    case QSocketNotifier::Write:
                    case QSocketNotifier::Exception:
                        FD_SET(notifier->socket(), fd_sets[notifier->type()]);
                        break;
                    default:
                        assert(false);
                        break;
                }

            emit this->aboutToBlock();
            if (select(FD_SETSIZE, &read_fd_set, &write_fd_set, &except_fd_set, &timeout) < 0)
            {
                emit this->awake();
                qCritical() << "socket notifier failed";
            }
            else
            {
                emit this->awake();
                QEvent event(QEvent::SockAct);
                for (auto notifier : this->socket_notifiers)
                    switch (notifier->type()) {
                        case QSocketNotifier::Read:
                        case QSocketNotifier::Write:
                        case QSocketNotifier::Exception:
                            if (FD_ISSET(notifier->socket(), fd_sets[notifier->type()])) {
                                qInfo() << "evt";
                                QCoreApplication::sendEvent(notifier, &event);
                                had_events = true;
                            }
                            break;
                        default:
                            assert(false);
                            break;
                    }
            }
        }

        QCoreApplication::sendPostedEvents();

        if (!(flags & QEventLoop::WaitForMoreEvents))
            break;
    }

    return had_events;
}
bool qtsdl::QEventDispatcherImpl::hasPendingEvents() { // ### Qt6: remove, mark final or make protected
    qWarning() << "hasPendingEvents()";
    return true;
}

void qtsdl::QEventDispatcherImpl::registerSocketNotifier(QSocketNotifier *notifier) {
    qWarning() << "registerSocketNotifier()";
}
void qtsdl::QEventDispatcherImpl::unregisterSocketNotifier(QSocketNotifier *notifier) {
    qWarning() << "unregisterSocketNotifier()";
}

void qtsdl::QEventDispatcherImpl::registerTimer(int timerId, int interval, Qt::TimerType timerType, QObject *object) {
    qWarning() << "registerTimer()";
#ifndef QT_NO_DEBUG
    if (timerId < 1 || interval < 0 || !object) {
        qWarning("QEventDispatcherUNIX::registerTimer: invalid arguments");
        return;
    } else if (object->thread() != thread() || thread() != QThread::currentThread()) {
        qWarning("QEventDispatcherUNIX::registerTimer: timers cannot be started from another thread");
        return;
    }
#endif

    this->timerList.registerTimer(timerId, interval, timerType, object);
}
bool qtsdl::QEventDispatcherImpl::unregisterTimer(int timerId) {
    qWarning() << "unregisterTimer()";
#ifndef QT_NO_DEBUG
    if (timerId < 1) {
        qWarning("QEventDispatcherUNIX::unregisterTimer: invalid argument");
        return false;
    } else if (thread() != QThread::currentThread()) {
        qWarning("QEventDispatcherUNIX::unregisterTimer: timers cannot be stopped from another thread");
        return false;
    }
#endif

    return this->timerList.unregisterTimer(timerId);
}
bool qtsdl::QEventDispatcherImpl::unregisterTimers(QObject *object) {
    qWarning() << "unregisterTimers()";
#ifndef QT_NO_DEBUG
    if (!object) {
        qWarning("QEventDispatcherUNIX::unregisterTimers: invalid argument");
        return false;
    } else if (object->thread() != thread() || thread() != QThread::currentThread()) {
        qWarning("QEventDispatcherUNIX::unregisterTimers: timers cannot be stopped from another thread");
        return false;
    }
#endif

    return this->timerList.unregisterTimers(object);
}
QList<QAbstractEventDispatcher::TimerInfo> qtsdl::QEventDispatcherImpl::registeredTimers(QObject *object) const {
    qWarning() << "registeredTimers()";
//    return QList<TimerInfo>();
//    return *new QList<QAbstractEventDispatcher::TimerInfo>();
    if (!object) {
        qWarning("QEventDispatcherUNIX:registeredTimers: invalid argument");
        return QList<TimerInfo>();
    }

    return this->timerList.registeredTimers(object);
}

int qtsdl::QEventDispatcherImpl::remainingTime(int timerId) {
    qWarning() << "remainingTime()";
    return 0;
}

#ifdef Q_OS_WIN
bool qtsdl::QEventDispatcherImpl::registerEventNotifier(QWinEventNotifier *notifier) {
    qWarning() << "registerEventNotifier()";
    return true;
}
void qtsdl::QEventDispatcherImpl::unregisterEventNotifier(QWinEventNotifier *notifier) {
    qWarning() << "unregisterEventNotifier()";
}
#endif

void qtsdl::QEventDispatcherImpl::wakeUp() {
    qWarning() << "wakeUp()";
}
void qtsdl::QEventDispatcherImpl::interrupt() {
    qWarning() << "interrupt()";
}
void qtsdl::QEventDispatcherImpl::flush() {
    qWarning() << "flush()";
}

void qtsdl::QEventDispatcherImpl::startingUp() {
    qWarning() << "startingUp()";
}
void qtsdl::QEventDispatcherImpl::closingDown() {
    qWarning() << "closingDown()";
}

} // namespace qtsdl
