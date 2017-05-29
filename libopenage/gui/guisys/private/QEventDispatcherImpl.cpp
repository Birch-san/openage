#include "QEventDispatcherImpl.h"

#include <QAbstractEventDispatcher>
#include <QObject>
#include <QList>
#include <QEventLoop>
#include <QCoreApplication>
#include <QtDebug> 
// #include <QWindowSystemInterface>

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
    qWarning() << "processFlags()";
    interruptor.store(0);
    //QCoreApplicationPrivate::sendPostedEvents(0, 0, d->threadData); //unix dispatcher use this
    QCoreApplication::sendPostedEvents(); //glib dispatcher call this after every call of "awake".

    const bool canWait = (/*d->threadData->canWaitLocked()
                          &&*/ !interruptor.load() //it may have been set during the call of QCoreApplication::sendPostedEvents()
&& (flags & QEventLoop::WaitForMoreEvents));

    if (interruptor.load())
    {
        return false; //unix event dispatcher returns false if nothing more than "postedEvents" were dispatched
    }

    // if (!(flags & QEventLoop::X11ExcludeTimers)) {
    //     d->timerStart();
    // }

    int total_events = 0; /* FIXME: +1 for stop? */

    if (canWait) {
        //run at least one handler - may block
        emit aboutToBlock();
        // d->io_service.reset();
        // total_events += d->io_service.run_one();
        emit awake();
    }

    int events;
    do
    {
        // if (!(flags & QEventLoop::X11ExcludeTimers)) {
        //     d->timerStart();
        // }

        // d->io_service.reset();
        //run all ready handlers
        // events = d->io_service.poll();

        if ((flags & QEventLoop::ExcludeSocketNotifiers)) {
            //FIXME: ignore stream descriptors
        }

        if ((flags & QEventLoop::X11ExcludeTimers)) {
            //FIXME: ignore timers?
        }

        total_events += events;
        QCoreApplication::sendPostedEvents();
        // total_events += QWindowSystemInterface::sendWindowSystemEvents(flags) ? 1 : 0;
    } while(events>0);

    // d->cleanupSocketNotifiers();

    // return true if we handled events, false otherwise
    return (total_events > 0);
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
}
bool qtsdl::QEventDispatcherImpl::unregisterTimer(int timerId) {
    qWarning() << "unregisterTimer()";
    return true;
}
bool qtsdl::QEventDispatcherImpl::unregisterTimers(QObject *object) {
    qWarning() << "unregisterTimers()";
    return true;
}
QList<QAbstractEventDispatcher::TimerInfo> qtsdl::QEventDispatcherImpl::registeredTimers(QObject *object) const {
    qWarning() << "registeredTimers()";
    return *new QList<QAbstractEventDispatcher::TimerInfo>();
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
