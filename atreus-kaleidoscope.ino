/* -*- mode: c++ -*-
 * Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
 * Copyright (C) 2018-2022  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-CharShift.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-FirmwareVersion.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-SpaceCadet.h"
#include "Kaleidoscope-DynamicMacros.h"
#include "Kaleidoscope-LayerNames.h"

#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

#define OS_SFT OSM(LeftShift)
#define OS_CMD OSM(LeftGui)
#define OS_ALT OSM(LeftAlt)
#define OS_CTL OSM(LeftControl)

enum {
  MACRO_QWERTY,
  MACRO_VERSION_INFO
};

#define Key_Exclamation LSHIFT(Key_1)
#define Key_At          LSHIFT(Key_2)
#define Key_Hash        LSHIFT(Key_3)
#define Key_Dollar      LSHIFT(Key_4)
#define Key_Percent     LSHIFT(Key_5)
#define Key_Caret       LSHIFT(Key_6)
#define Key_And         LSHIFT(Key_7)
#define Key_Star        LSHIFT(Key_8)
#define Key_Plus        LSHIFT(Key_Equals)

#define Key_Question    LSHIFT(Key_Slash)
#define Key_Lt          LSHIFT(Key_Comma)
#define Key_Gt          LSHIFT(Key_Period)
#define Key_Eq          Key_Equals
#define Key_Underscore  LSHIFT(Key_Minus)
#define Key_Tilde       LSHIFT(Key_Backtick)

#define Key_PlayPause   Consumer_PlaySlashPause
#define Key_Stop        Consumer_Stop
#define Key_PrevTrack   Consumer_ScanPreviousTrack
#define Key_NextTrack   Consumer_ScanNextTrack

#define Key_BrightUp    Consumer_DisplayBrightnessIncrement
#define Key_BrightDn    Consumer_DisplayBrightnessDecrement
#define Key_Sleep       Consumer_Sleep
#define Key_VolUp       Consumer_VolumeIncrement
#define Key_VolDn       Consumer_VolumeDecrement

#define M_Home LCTRL(Key_A)
#define M_End  LCTRL(Key_E)
#define M_Undo LGUI(Key_Z)
#define M_Redo LGUI(LSHIFT(Key_Z))
#define M_Cut  LGUI(Key_X)
#define M_Copy LGUI(Key_C)
#define M_Paste LGUI(Key_V)

enum { BASE, NAV, SYM, NUM };

// clang-format off
KEYMAPS(
  [BASE] = KEYMAP_STACKED
  (
       Key_Q ,Key_W ,Key_E ,Key_R          ,Key_T
      ,Key_A ,Key_S ,Key_D ,Key_F          ,Key_G
      ,Key_Z ,Key_X ,Key_C ,Key_V          ,Key_B         ,___
      ,___   ,___   ,___   ,LT(NUM,Escape) ,LT(NAV,Space) ,SFT_T(Tab)

                     ,Key_Y             ,Key_U      ,Key_I  ,Key_O  ,Key_P
                     ,Key_H             ,Key_J      ,Key_K  ,Key_L  ,Key_Semicolon
       ,___          ,Key_N             ,Key_M      ,CS(0)  ,CS(1)  ,CS(2)
       ,SFT_T(Enter) ,LT(SYM,Backspace) ,Key_Delete ,___    ,___    ,___
  ),

  [NAV] = KEYMAP_STACKED
  (
       ___       ,Key_Mute      ,Key_VolDn     ,Key_VolUp     ,Key_BrightUp
      ,OS_SFT    ,OS_CTL        ,OS_ALT        ,OS_CMD        ,Key_BrightDn
      ,Key_Stop  ,Key_PrevTrack ,Key_PlayPause ,Key_NextTrack ,Key_Sleep    ,___
      ,___       ,___           ,___           ,___           ,___          ,___

                 ,Key_PageUp    ,M_Undo        ,Key_UpArrow   ,M_Redo         ,___
                 ,M_Home        ,Key_LeftArrow ,Key_DownArrow ,Key_RightArrow ,M_End
      ,___       ,Key_PageDown  ,M_Paste       ,M_Copy        ,M_Cut          ,___
      ,Key_Enter ,Key_Backspace ,Key_Delete    ,___           ,___            ,___
   ),

  [SYM] = KEYMAP_STACKED
  (
       ___     ,Key_Hash    ,Key_Slash     ,Key_LeftCurlyBracket ,Key_RightCurlyBracket
      ,Key_At  ,Key_Dollar  ,Key_Pipe      ,Key_LeftParen        ,Key_RightParen
      ,Key_And ,Key_Percent ,Key_Backslash ,Key_LeftBracket      ,Key_RightBracket      ,___
      ,___     ,___         ,___           ,Key_Esc              ,Key_Space             ,Key_Tab

                ,Key_Tilde    ,Key_Lt   ,Key_Eq   ,Key_Gt    ,___
                ,Key_Backtick ,OS_CMD   ,OS_ALT   ,OS_CTL    ,OS_SFT
      ,___      ,Key_Caret    ,Key_Star ,Key_Plus ,Key_Minus ,Key_Underscore
      ,___      ,___          ,___      ,___      ,___       ,___
   ),

   [NUM] = KEYMAP_STACKED
   (
       ___    ,___    ,___    ,___    ,___
      ,OS_SFT ,OS_CTL ,OS_ALT ,OS_CMD ,___
      ,___    ,___    ,___    ,___    ,___ ,___
      ,___    ,___    ,___    ,___    ,___ ,___

                  ,Key_Delete    ,Key_7      ,Key_8   ,Key_9  ,___
                  ,Key_Backspace ,Key_4      ,Key_5   ,Key_6  ,___
       ,___       ,Key_Tab       ,Key_1      ,Key_2   ,Key_3  ,___
       ,Key_Enter ,Key_0         ,Key_Period ,___     ,___    ,___
   )

)
// clang-format on

KALEIDOSCOPE_INIT_PLUGINS(
  // https://kaleidoscope.readthedocs.io/en/latest/plugins/Kaleidoscope-CharShift.html
  CharShift,

  // ----------------------------------------------------------------------
  // Chrysalis plugins

  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The FirmwareVersion plugin lets Chrysalis query the version of the firmware
  // programmatically.
  FirmwareVersion,

  // The LayerNames plugin allows Chrysalis to display - and edit - custom layer
  // names, to be shown instead of the default indexes.
  LayerNames,

  // ----------------------------------------------------------------------
  // Keystroke-handling plugins

  // The Qukeys plugin enables the "Secondary action" functionality in
  // Chrysalis. Keys with secondary actions will have their primary action
  // performed when tapped, but the secondary action when held.
  Qukeys,

  // SpaceCadet can turn your shifts into parens on tap, while keeping them as
  // Shifts when held. SpaceCadetConfig lets Chrysalis configure some aspects of
  // the plugin.
  // SpaceCadet,
  SpaceCadetConfig,

  // Enables the "Sticky" behavior for modifiers, and the "Layer shift when
  // held" functionality for layer keys.
  OneShot,
  OneShotConfig,
  EscapeOneShot,
  EscapeOneShotConfig,

  // The macros plugin adds support for macros
  Macros,

  // Enables dynamic, Chrysalis-editable macros.
  DynamicMacros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,
  MouseKeysConfig  //,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  // MagicCombo,

  // Enables the GeminiPR Stenography protocol. Unused by default, but with the
  // plugin enabled, it becomes configurable - and then usable - via Chrysalis.
  // GeminiPR,
);

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    switch (macro_id) {
    case MACRO_VERSION_INFO:
      Macros.type(PSTR("Keyboardio Atreus - Kaleidoscope "));
      Macros.type(PSTR(BUILD_INFORMATION));
      break;
    default:
      break;
    }
  }
  return MACRO_NONE;
}

void setup() {
  // https://kaleidoscope.readthedocs.io/en/latest/examples/Keystrokes/CharShift/CharShift.ino.html
  CS_KEYS(
    kaleidoscope::plugin::CharShift::KeyPair(Key_Comma, Key_Quote),
    kaleidoscope::plugin::CharShift::KeyPair(Key_Period, LSHIFT(Key_Quote)),
    kaleidoscope::plugin::CharShift::KeyPair(Key_Question, Key_Exclamation),
  );

  Kaleidoscope.setup();
  EEPROMKeymap.setup(9);

  Qukeys.setOverlapThreshold(25);

  DynamicMacros.reserve_storage(48);

  LayerNames.reserve_storage(63);

  Layer.move(EEPROMSettings.default_layer());

  // To avoid any surprises, SpaceCadet is turned off by default. However, it
  // can be permanently enabled via Chrysalis, so we should only disable it if
  // no configuration exists.
  SpaceCadetConfig.disableSpaceCadetIfUnconfigured();
}

void loop() {
  Kaleidoscope.loop();
}
