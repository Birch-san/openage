// Copyright 2015-2016 the openage authors. See copying.md for legal info.

#include "gui_event_queue_impl.h"

#include <cassert>

#include <QThread>

#include "../public/gui_event_queue.h"

#ifdef __APPLE__
	#include <QtDebug>
	#include <QCoreApplication>
#endif

namespace qtsdl {

GuiEventQueueImpl::GuiEventQueueImpl()
	:
	thread{QThread::currentThread()} {
}

GuiEventQueueImpl::~GuiEventQueueImpl() {
}

GuiEventQueueImpl* GuiEventQueueImpl::impl(GuiEventQueue *event_queue) {
	return event_queue->impl.get();
}

void GuiEventQueueImpl::process_callbacks() {
	assert(QThread::currentThread() == this->thread);
	QEventLoop::ProcessEventsFlags flags = QEventLoop::AllEvents;
#ifdef __APPLE__
	if (QThread::currentThread() == QCoreApplication::instance()->thread()) return;
	flags ^= QEventLoop::ExcludeUserInputEvents;
	flags ^= QEventLoop::ExcludeSocketNotifiers;
	flags ^= QEventLoop::WaitForMoreEvents;
	qWarning() << "callbacks:";
	qWarning() << flags;
#endif
	this->callback_processor.processEvents(flags, 100);
}

QThread* GuiEventQueueImpl::get_thread() {
	return this->thread;
}

} // namespace qtsdl
