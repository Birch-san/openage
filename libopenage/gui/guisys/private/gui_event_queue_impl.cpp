// Copyright 2015-2016 the openage authors. See copying.md for legal info.

#include "gui_event_queue_impl.h"

#include <cassert>

#include <QThread>
#include <QtDebug>

#ifdef __APPLE__
	#include <QCoreApplication>
#endif

#include "../public/gui_event_queue.h"

namespace qtsdl {

GuiEventQueueImpl::GuiEventQueueImpl()
	:
	thread{QThread::currentThread()} {
}

GuiEventQueueImpl::~GuiEventQueueImpl() {
	// our QEventLoop is a "local event loop", so maybe it has no filters on it yet
	qInfo() << "Installing event filters into GuiEventQueue's QEventLoop...";
	this->callback_processor.installEventFilter(&this->event_filter);
}

GuiEventQueueImpl* GuiEventQueueImpl::impl(GuiEventQueue *event_queue) {
	return event_queue->impl.get();
}

void GuiEventQueueImpl::process_callbacks() {
	assert(QThread::currentThread() == this->thread);
#ifdef __APPLE__
	// btw this condition is always true, as far as I've noticed:
	if (QThread::currentThread() == QCoreApplication::instance()->thread()) return;
	qWarning() << "Processing of event queue will continue for thread: " << QThread::currentThread();
	// if you are using the default macOS event dispatcher, and 
	// you allow this class to invoke processEvents(): 
	// _only_ native events `NATIVE EVENT:  "mac_generic_NSEvent"` will appear in our logger.
	// i.e. no QTimer events will be handled.
	// additionally: the following call to processEvents() will never finish.
#endif
	this->callback_processor.processEvents();
	qWarning() << "Finished processing of local event loop for thread: " << QThread::currentThread();
}

QThread* GuiEventQueueImpl::get_thread() {
	return this->thread;
}

} // namespace qtsdl
