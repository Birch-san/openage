// Copyright 2015-2016 the openage authors. See copying.md for legal info.

#pragma once

namespace qtsdl {

class KeyPressEater : public QObject {
protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

} // namespace qtsdl
