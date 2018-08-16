#include "stdafx.h"

DECLARE_COMPONENT_VERSION(
	"Party Shuffle",
	"1.0.0",
	u8"Party Shuffle\n\nhttps://github.com/phts/foo_partyshuffle\n© 2018 Phil Tsaryk"
);
VALIDATE_COMPONENT_FILENAME("foo_partyshuffle.dll");

class PartyShuffle : public play_callback_impl_base {
public:

	PartyShuffle() {}

private:

	void on_playback_stop(play_control::t_stop_reason p_reason) {
		if (cfg_partyshuffle_enabled == FALSE) return;
		if (p_reason != play_control::t_stop_reason::stop_reason_eof) return;

		pfc::list_t<metadb_handle_ptr> all_items;
		library_manager_service->get_all_items(all_items);

		int list_size = static_cast<int>(all_items.get_count());

		for (int i = 0; i < 10; i++) {
			int random_index = rand() % list_size;
			add_track_to_current_playlist(all_items, random_index);
		}

		if (playback_control_service->get_stop_after_current() == FALSE) {
			start_playback();
		}
	}

	void add_track_to_current_playlist(pfc::list_t<metadb_handle_ptr> all_items, int track_index) {
		t_size active_playlist = playlist_manager_service->get_active_playlist();
		t_size item_count = playlist_manager_service->playlist_get_item_count(active_playlist);

		pfc::list_t<metadb_handle_ptr> item_to_add;
		item_to_add.add_item(all_items[track_index]);

		bit_array_bittable selection;

		playlist_manager_service->playlist_insert_items(active_playlist, item_count, item_to_add, selection);
	}

	void start_playback() {
		service_ptr_t<StartPlaybackCallback> callback_serv = new service_impl_t<StartPlaybackCallback>();
		main_thread_callback_manager_service->add_callback(callback_serv);
	}


	static_api_ptr_t<library_manager> library_manager_service;
	static_api_ptr_t<playback_control> playback_control_service;
	static_api_ptr_t<playlist_manager> playlist_manager_service;
	static_api_ptr_t<main_thread_callback_manager> main_thread_callback_manager_service;


	class StartPlaybackCallback : public main_thread_callback {
	public:
		void callback_run() {
			static_api_ptr_t<playback_control>()->next();
		}
	};
};

class PartyShuffleInit : public initquit {
public:

	void on_init() {
		srand(static_cast<unsigned int>(time(NULL)));
		new PartyShuffle();
	}

};

static initquit_factory_t<PartyShuffleInit> partyshuffle_init_factory;
