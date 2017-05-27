#include "QEventDispatcherImpl.h"

#include <QAbstractEventDispatcher>
#include <QObject>
#include <QList>

namespace qtsdl {

qtsdl::QEventDispatcherImpl::QEventDispatcherImpl(QObject *parent)
  : QAbstractEventDispatcher(parent) {
}

bool qtsdl::QEventDispatcherImpl::processEvents(QEventLoop::ProcessEventsFlags flags) {
    return true;
}
bool qtsdl::QEventDispatcherImpl::hasPendingEvents() { // ### Qt6: remove, mark final or make protected
    return true;
}

void qtsdl::QEventDispatcherImpl::registerSocketNotifier(QSocketNotifier *notifier) {

}
void qtsdl::QEventDispatcherImpl::unregisterSocketNotifier(QSocketNotifier *notifier) {

}

void qtsdl::QEventDispatcherImpl::registerTimer(int timerId, int interval, Qt::TimerType timerType, QObject *object) {

}
bool qtsdl::QEventDispatcherImpl::unregisterTimer(int timerId) {
    return true;
}
bool qtsdl::QEventDispatcherImpl::unregisterTimers(QObject *object) {
    return true;
}
QList<QAbstractEventDispatcher::TimerInfo> qtsdl::QEventDispatcherImpl::registeredTimers(QObject *object) const {
    return *new QList<QAbstractEventDispatcher::TimerInfo>();
}

int qtsdl::QEventDispatcherImpl::remainingTime(int timerId) {
    return 0;
}

#ifdef Q_OS_WIN
bool qtsdl::QEventDispatcherImpl::registerEventNotifier(QWinEventNotifier *notifier) {
    return true;
}
void qtsdl::QEventDispatcherImpl::unregisterEventNotifier(QWinEventNotifier *notifier) {
}
#endif

void qtsdl::QEventDispatcherImpl::wakeUp() {
}
void qtsdl::QEventDispatcherImpl::interrupt() {
}
void qtsdl::QEventDispatcherImpl::flush() {
}

void qtsdl::QEventDispatcherImpl::startingUp() {
}
void qtsdl::QEventDispatcherImpl::closingDown() {
}

} // namespace qtsdl
