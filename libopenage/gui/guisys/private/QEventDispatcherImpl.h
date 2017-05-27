// Copyright 2015-2016 the openage authors. See copying.md for legal info.

#pragma once

#include <QAbstractEventDispatcher>
#include <QEventLoop>
namespace qtsdl {

class QEventDispatcherImpl : public QAbstractEventDispatcher {
	Q_OBJECT
	
    public:
        QEventDispatcherImpl(QObject *parent = Q_NULLPTR);
        ~QEventDispatcherImpl();

        virtual bool processEvents(QEventLoop::ProcessEventsFlags flags);
	    virtual bool hasPendingEvents(); // ### Qt6: remove, mark final or make protected

	    virtual void registerSocketNotifier(QSocketNotifier *notifier);
	    virtual void unregisterSocketNotifier(QSocketNotifier *notifier);

	    virtual void registerTimer(int timerId, int interval, Qt::TimerType timerType, QObject *object);
	    virtual bool unregisterTimer(int timerId);
	    virtual bool unregisterTimers(QObject *object);
	    virtual QList<TimerInfo> registeredTimers(QObject *object) const;

	    virtual int remainingTime(int timerId);

	#ifdef Q_OS_WIN
	    virtual bool registerEventNotifier(QWinEventNotifier *notifier);
	    virtual void unregisterEventNotifier(QWinEventNotifier *notifier);
	#endif

	    virtual void wakeUp();
	    virtual void interrupt();
	    virtual void flush();

	    virtual void startingUp();
	    virtual void closingDown();
};

} // namespace qtsdl
