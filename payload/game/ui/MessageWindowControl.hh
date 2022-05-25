#pragma once

#include "game/ui/UIControl.hh"

namespace UI {

class MessageWindowControl : public LayoutUIControl {
public:
    MessageWindowControl();
    ~MessageWindowControl() = default;

    void load(const char *dir, const char *file, const char *variant);
};

}  // namespace UI
