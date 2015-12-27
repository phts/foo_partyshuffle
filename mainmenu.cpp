#include "stdafx.h"

static const GUID cfg_partyshuffle_enabled_guid = { 0xbdac777, 0x735c, 0x440d,{ 0x8c, 0x71, 0x49, 0xb6, 0xac, 0xff, 0xce, 0xb8 } };
cfg_bool cfg_partyshuffle_enabled(cfg_partyshuffle_enabled_guid, false);

class PartyShuffleMainmenuCommands : public mainmenu_commands {
public:
	enum {
		cmd_partyshuffle = 0,
		cmd_total
	};
	t_uint32 get_command_count() {
		return cmd_total;
	}
	GUID get_command(t_uint32 p_index) {
		static const GUID guid_partyshuffle = { 0x7d4726df, 0x3b2d, 0x4c7c, { 0xad, 0xe8, 0x43, 0xd8, 0x46, 0xbe, 0xce, 0xa8 } };
		switch(p_index) {
			case cmd_partyshuffle: return guid_partyshuffle;
			default: uBugCheck();
		}
	}
	void get_name(t_uint32 p_index, pfc::string_base & p_out) {
		switch(p_index) {
			case cmd_partyshuffle:
				p_out = "Party Shuffle";
				break;
			default: uBugCheck();
		}
	}
	bool get_description(t_uint32 p_index, pfc::string_base & p_out) {
		switch(p_index) {
			case cmd_partyshuffle:
				p_out = "Enable/disable Party Shuffle mode.";
				return true;
			default: uBugCheck();
		}
	}
	GUID get_parent() {
		return mainmenu_groups::playback;
	}
	void execute(t_uint32 p_index, service_ptr_t<service_base> p_callback) {
		switch(p_index) {
			case cmd_partyshuffle:
				cfg_partyshuffle_enabled = cfg_partyshuffle_enabled.get_value() == TRUE ? FALSE : TRUE;
				break;
			default:
				uBugCheck();
		}
	}
	bool get_display(t_uint32 p_index, pfc::string_base & p_text, t_uint32 & p_flags) {
		p_flags = cfg_partyshuffle_enabled == TRUE ? flag_checked : 0;
		get_name(p_index, p_text);
		return true;
	}
};

static mainmenu_commands_factory_t<PartyShuffleMainmenuCommands> g_mainmenu_commands_partyshuffle_factory;
