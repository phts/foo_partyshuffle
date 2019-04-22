#include "stdafx.h"

DECLARE_COMPONENT_VERSION(
	"Party Shuffle",
	"1.0.2",
	u8"Party Shuffle\n\nhttps://github.com/phts/foo_partyshuffle\n© 2019 Phil Tsaryk"
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

		t_size last_track_index = playlist_manager_service->activeplaylist_get_item_count();

		for (int i = 0; i < 10; i++) {
			int track_index = rand() % list_size;
			metadb_handle_ptr item = all_items[track_index];
			insert_track_to_current_playlist(last_track_index, item);
		}

		if (playback_control_service->get_stop_after_current() == FALSE) {
			start_playback(last_track_index);
		}
	}

	void insert_track_to_current_playlist(t_size position, metadb_handle_ptr item) {
		pfc::list_t<metadb_handle_ptr> item_to_add;
		item_to_add.add_item(item);

		bit_array_bittable selection;

		playlist_manager_service->activeplaylist_insert_items(position, item_to_add, selection);
	}

	void start_playback(t_size position) {
		playlist_manager_service->activeplaylist_set_focus_item(position);
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
			static_api_ptr_t<playback_control>()->start();
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
