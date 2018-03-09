#pragma once

#include "Common/Constants.hpp"

#include "Controller/CController.hpp"

class Core;

/// CDVD handler logic.
/// HLE-ish approach - emulates bios function calls made? There is near no documentation otherwise.
/// Everything from PCSX2. See CDVD.cpp etc.
class CCdvd : public CController
{
public:
	CCdvd(Core * core);

	void handle_event(const ControllerEvent & event) override;

	/// Converts a time duration into the number of ticks that would have occurred.
	int time_to_ticks(const double time_us);

	/// Checks and processes the CDVD state for any actions to be performed.
	int time_step(const int ticks_available);

	/// Increments the RTC state by the microseconds specified.
	void handle_rtc_increment(const double time_us);

	/// N Command instructions and table.
	/// In theory there can be 256 (ubyte) total instructions, but only a handful of them are implemented.
	void NCMD_INSTRUCTION_UNKNOWN();
	void(CCdvd::* NCMD_INSTRUCTION_TABLE[Constants::CDVD::NUMBER_NCMD_INSTRUCTIONS])() =
	{
		/* 0x00 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x01 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x02 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x03 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x04 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x05 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x06 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x07 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x08 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x09 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x0A */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x0B */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x0C */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x0D */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x0E */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x0F */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x10 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x11 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x12 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x13 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x14 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x15 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x16 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x17 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x18 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x19 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x1A */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x1B */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x1C */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x1D */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x1E */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x1F */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x20 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x21 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x22 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x23 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x24 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x25 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x26 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x27 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x28 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x29 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x2A */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x2B */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x2C */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x2D */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x2E */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x2F */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x30 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x31 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x32 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x33 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x34 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x35 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x36 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x37 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x38 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x39 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x3A */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x3B */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x3C */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x3D */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x3E */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x3F */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x40 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x41 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x42 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x43 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x44 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x45 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x46 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x47 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x48 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x49 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x4A */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x4B */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x4C */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x4D */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x4E */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x4F */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x50 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x51 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x52 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x53 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x54 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x55 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x56 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x57 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x58 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x59 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x5A */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x5B */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x5C */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x5D */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x5E */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x5F */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x60 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x61 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x62 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x63 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x64 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x65 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x66 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x67 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x68 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x69 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x6A */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x6B */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x6C */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x6D */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x6E */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x6F */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x70 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x71 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x72 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x73 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x74 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x75 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x76 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x77 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x78 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x79 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x7A */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x7B */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x7C */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x7D */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x7E */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x7F */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x80 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x81 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x82 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x83 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x84 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x85 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x86 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x87 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x88 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x89 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x8A */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x8B */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x8C */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x8D */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x8E */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x8F */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x90 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x91 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x92 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x93 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x94 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x95 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x96 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x97 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x98 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x99 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x9A */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x9B */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x9C */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x9D */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x9E */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0x9F */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA0 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA1 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA2 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA3 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA4 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA5 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA6 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA7 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA8 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xA9 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xAA */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xAB */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xAC */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xAD */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xAE */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xAF */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB0 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB1 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB2 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB3 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB4 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB5 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB6 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB7 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB8 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xB9 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xBA */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xBB */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xBC */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xBD */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xBE */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xBF */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC0 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC1 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC2 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC3 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC4 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC5 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC6 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC7 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC8 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xC9 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xCA */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xCB */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xCC */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xCD */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xCE */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xCF */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD0 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD1 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD2 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD3 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD4 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD5 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD6 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD7 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD8 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xD9 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xDA */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xDB */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xDC */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xDD */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xDE */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xDF */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE0 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE1 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE2 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE3 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE4 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE5 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE6 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE7 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE8 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xE9 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xEA */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xEB */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xEC */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xED */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xEE */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xEF */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF0 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF1 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF2 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF3 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF4 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF5 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF6 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF7 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF8 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xF9 */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xFA */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xFB */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xFC */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xFD */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xFE */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN,
		/* 0xFF */ &CCdvd::NCMD_INSTRUCTION_UNKNOWN
	};

	/// S Command instructions and table.
	/// In theory there can be 256 (ubyte) total instructions, but only a handful of them are implemented.
	/// Notation: "Mnemonic" (3:1) means 3 parameter bytes in (S_DATA_IN FIFO), 1 result byte out (S_DATA_OUT).
	void SCMD_INSTRUCTION_UNKNOWN();
	void SCMD_INSTRUCTION_08();      // "sceCdReadRTC" (0:8).
	void SCMD_INSTRUCTION_15();      // "sceCdForbidDVDP" (0:1).
	void SCMD_INSTRUCTION_40();      // "sceCdOpenConfig" (3:1).
	void SCMD_INSTRUCTION_41();      // "sceCdReadConfig" (0:16).
	void SCMD_INSTRUCTION_42();      // "sceCdWriteConfig" (16:1).
	void SCMD_INSTRUCTION_43();      // "sceCdCloseConfig" (0:1).
	void(CCdvd::* SCMD_INSTRUCTION_TABLE[Constants::CDVD::NUMBER_SCMD_INSTRUCTIONS])() =
	{ 
		/* 0x00 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x01 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x02 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x03 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x04 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x05 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x06 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x07 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x08 */ &CCdvd::SCMD_INSTRUCTION_08,
		/* 0x09 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x0A */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x0B */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x0C */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x0D */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x0E */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x0F */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x10 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x11 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x12 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x13 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x14 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x15 */ &CCdvd::SCMD_INSTRUCTION_15,
		/* 0x16 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x17 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x18 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x19 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x1A */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x1B */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x1C */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x1D */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x1E */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x1F */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x20 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x21 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x22 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x23 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x24 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x25 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x26 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x27 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x28 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x29 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x2A */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x2B */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x2C */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x2D */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x2E */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x2F */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x30 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x31 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x32 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x33 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x34 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x35 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x36 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x37 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x38 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x39 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x3A */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x3B */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x3C */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x3D */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x3E */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x3F */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x40 */ &CCdvd::SCMD_INSTRUCTION_40,
		/* 0x41 */ &CCdvd::SCMD_INSTRUCTION_41,
		/* 0x42 */ &CCdvd::SCMD_INSTRUCTION_42,
		/* 0x43 */ &CCdvd::SCMD_INSTRUCTION_43,
		/* 0x44 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x45 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x46 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x47 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x48 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x49 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x4A */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x4B */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x4C */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x4D */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x4E */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x4F */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x50 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x51 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x52 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x53 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x54 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x55 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x56 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x57 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x58 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x59 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x5A */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x5B */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x5C */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x5D */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x5E */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x5F */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x60 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x61 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x62 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x63 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x64 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x65 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x66 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x67 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x68 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x69 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x6A */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x6B */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x6C */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x6D */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x6E */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x6F */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x70 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x71 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x72 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x73 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x74 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x75 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x76 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x77 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x78 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x79 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x7A */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x7B */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x7C */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x7D */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x7E */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x7F */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x80 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x81 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x82 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x83 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x84 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x85 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x86 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x87 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x88 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x89 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x8A */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x8B */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x8C */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x8D */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x8E */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x8F */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x90 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x91 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x92 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x93 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x94 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x95 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x96 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x97 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x98 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x99 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x9A */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x9B */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x9C */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x9D */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x9E */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0x9F */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA0 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA1 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA2 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA3 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA4 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA5 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA6 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA7 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA8 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xA9 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xAA */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xAB */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xAC */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xAD */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xAE */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xAF */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB0 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB1 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB2 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB3 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB4 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB5 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB6 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB7 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB8 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xB9 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xBA */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xBB */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xBC */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xBD */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xBE */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xBF */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC0 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC1 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC2 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC3 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC4 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC5 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC6 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC7 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC8 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xC9 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xCA */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xCB */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xCC */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xCD */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xCE */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xCF */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD0 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD1 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD2 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD3 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD4 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD5 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD6 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD7 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD8 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xD9 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xDA */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xDB */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xDC */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xDD */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xDE */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xDF */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE0 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE1 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE2 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE3 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE4 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE5 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE6 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE7 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE8 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xE9 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xEA */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xEB */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xEC */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xED */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xEE */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xEF */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF0 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF1 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF2 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF3 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF4 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF5 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF6 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF7 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF8 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xF9 */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xFA */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xFB */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xFC */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xFD */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xFE */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN,
		/* 0xFF */ &CCdvd::SCMD_INSTRUCTION_UNKNOWN
	};
};

