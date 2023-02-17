/* Copyright (c) 2019 The Asil Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/views/location_bar/brave_star_view.h"
#include "brave/browser/ui/views/speedreader/speedreader_icon_view.h"
#include "chrome/browser/ui/page_action/page_action_icon_type.h"
#include "chrome/browser/ui/views/reader_mode/reader_mode_icon_view.h"

namespace {
constexpr PageActionIconType kUndefinedPageActionIconType =
    static_cast<PageActionIconType>(-1);
}  // namespace

// Circumvent creation of CookieControlsIconView in
// PageActionIconController::Init's switch statement by injecting a case
// with a non-existent value created above.
#define kCookieControls \
  kCookieControls:      \
  break;                \
  case kUndefinedPageActionIconType

#define ReaderModeIconView SpeedreaderIconView
#define StarView BraveStarView
#include "src/chrome/browser/ui/views/page_action/page_action_icon_controller.cc"
#undef StarView
#undef ReaderModeIconView
#undef kCookieControls
