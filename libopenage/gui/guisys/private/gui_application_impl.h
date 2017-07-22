// Copyright 2015-2016 the openage authors. See copying.md for legal info.

#pragma once

#include <thread>
#include <memory>

#include <QGuiApplication>

// #include "QEventDispatcherImpl.h"
#include "mycocoaeventfilter.h"
#include "KeyPressEater.h"

namespace qtsdl {

/**
 * Houses gui logic event queue.
 *
 * To launch it in a dedicated thread, use qtsdl::GuiDedicatedThread instead.
 */
class GuiApplicationImpl {
public:
	static std::shared_ptr<GuiApplicationImpl> get();

	~GuiApplicationImpl();

	void processEvents();

private:
	GuiApplicationImpl();

	GuiApplicationImpl(const GuiApplicationImpl&) = delete;
	GuiApplicationImpl& operator=(const GuiApplicationImpl&) = delete;

#ifndef NDEBUG
	const std::thread::id owner;
#endif

	KeyPressEater event_filter;
	CocoaNativeEventFilter native_event_filter;
	QGuiApplication app;

	static std::weak_ptr<GuiApplicationImpl> instance;
};

} // namespace qtsdl
