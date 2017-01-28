# HHKB
Happy Hacking Keyboard driver for Adafruit Feather 32u4 Bluefruit LE

This is a USB only driver as of now, Bluetooth functions should be added soon.

This is a minimalist driver for the Happy Hacking Keyboard Professional 2 using the Adafruit Feather 32u4 Bluefruit LE.

This driver depends on NicoHood's HID Library:
https://github.com/NicoHood/HID

This driver provides easy to read and follow code with abundant commenting, with the goal of creating a clear understanding of how the HHKB scans the key matrix, and to provide a base of understanding for others to build on when writing there own drivers, or using and modifing other availible drivers.

This driver has no timing, and does not use direct port manipulation.  It should not be considered optimised, or particularly fast.  The delay or lag varies between key presses, and is directly affected by code placed in the keyON() and keyOff() functions.  It will wait until that code completes before the next scan of the matrix starts.

Keymaps by default emulate the default HHKB behavior with Mac keys enabled, and Delete = Backspace.  This can all be changed in Keymaps.cpp to whatever you desire.
