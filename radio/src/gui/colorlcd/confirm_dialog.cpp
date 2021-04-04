/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "confirm_dialog.h"
#include "static.h"
#include "gridlayout.h"

ConfirmDialog::ConfirmDialog(Window * parent, const char * title, const char * message, std::function<void(void)> confirmHandler) :
  Dialog(parent, title, {50, 73, LCD_W - 100, LCD_H - 146}),
  confirmHandler(std::move(confirmHandler))
{
  auto form = &content->form;
  FormGridLayout grid(content->form.width());
  form->clear();
  
  new StaticText(form, grid.getCenteredSlot(), message);
  grid.nextLine();

  auto noButton = new TextButton(form, grid.getSlot(2, 0), "NO",
                                 [=]() -> int8_t {
                                   this->deleteLater();
                                   return 0;
                                 });

  new TextButton(form, grid.getSlot(2, 1), "YES",
                 [=]() -> int8_t {
                   this->deleteLater();
                   this->confirmHandler();
                   return 0;
                 });

  noButton->setFocus(SET_FOCUS_DEFAULT);
}

// #if defined(HARDWARE_KEYS)
// void ConfirmDialog::onEvent(event_t event)
// {
//   TRACE_WINDOWS("%s received event 0x%X", getWindowDebugString().c_str(), event);

//   if (event == EVT_KEY_BREAK(KEY_ENTER)) {
//     deleteLater(); // this restore the focus (it can be changed then in confirmHandler)
//     confirmHandler();
//   }
//   else if (event == EVT_KEY_BREAK(KEY_EXIT)) {
//     deleteLater();
//   }
// }
// #endif
