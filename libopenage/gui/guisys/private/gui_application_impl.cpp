// Copyright 2015-2017 the openage authors. See copying.md for legal info.

#include "gui_application_impl.h"

#include <locale>
#include <cassert>

#include <QtGlobal>
#include <QtDebug>

#ifdef __APPLE__
	#include <QThread>
	#include <QCoreApplication>
#endif

namespace qtsdl {

std::weak_ptr<GuiApplicationImpl> GuiApplicationImpl::instance;

std::shared_ptr<GuiApplicationImpl> GuiApplicationImpl::get() {
	std::shared_ptr<GuiApplicationImpl> candidate = GuiApplicationImpl::instance.lock();

	assert(!candidate || std::this_thread::get_id() == candidate->owner);

	return candidate ? candidate : std::shared_ptr<GuiApplicationImpl>{new GuiApplicationImpl};
}

GuiApplicationImpl::~GuiApplicationImpl() {
	assert(std::this_thread::get_id() == this->owner);
}

void GuiApplicationImpl::processEvents() {
	assert(std::this_thread::get_id() == this->owner);
#ifdef __APPLE__
	// btw this condition is always true, as far as I've noticed:
	if (QThread::currentThread() == QCoreApplication::instance()->thread()) return;
	qWarning() << "Processing of GUI application events will continue for thread: " << QThread::currentThread();
	// if you are using the default macOS event dispatcher, and 
	// you allow this class to invoke processEvents(): 
	// _only_ native events `NATIVE EVENT:  "mac_generic_NSEvent"` will appear in our logger.
	// i.e. no QTimer events will be handled.
	// additionally: the following call to processEvents() will never finish.
#endif
	this->app.processEvents();
	qWarning() << "Finished processing of GUI application events for thread: " << QThread::currentThread();
}

namespace {
	int argc = 1;
	char arg[] = "qtsdl";
	char *argv = &arg[0];
}

GuiApplicationImpl::GuiApplicationImpl()
	:
#ifndef NDEBUG
	owner{std::this_thread::get_id()},
#endif
	event_filter{},
	native_event_filter{},
	app{(QCoreApplication::setEventDispatcher(&this->event_dispatcher), argc), &argv}
	// app{argc, &argv}
{
	// Set locale back to POSIX for the decimal point parsing (see qcoreapplication.html#locale-settings).
	std::locale::global(std::locale().combine<std::numpunct<char>>(std::locale::classic()));

	qInfo() << "Compiled with Qt" << QT_VERSION_STR << "and run with Qt" << qVersion();
	qInfo() << "Installing event filters into GuiApplicationImpl...";
	this->app.installNativeEventFilter(&this->native_event_filter);
	this->app.installEventFilter(&this->event_filter);
}

} // namespace qtsdl
