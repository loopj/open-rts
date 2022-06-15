var group__openrts =
[
    [ "rts_frame", "structrts__frame.html", [
      [ "rts_frame_init", "group__openrts.html#gab5571a1d421a1148d309f2858a83613f", null ],
      [ "rts_frame_from_bytes", "group__openrts.html#ga4223460f69635b1c97a7c9f2dd42dfb5", null ],
      [ "rts_frame_to_bytes", "group__openrts.html#gabee4ad16c735ef07839cbc12f9282b96", null ],
      [ "rts_frame_obfuscate_bytes", "group__openrts.html#gafa119ab98f70aaa2f90961c7830e882a", null ],
      [ "rts_frame_deobfuscate_bytes", "group__openrts.html#ga055aa8c663040dd6861a11035696bca5", null ],
      [ "rts_frame_generate_checksum", "group__openrts.html#ga8c6b65412d7a48442ff251fbff5360f5", null ],
      [ "encryption_key", "structrts__frame.html#a995b3e499dede20ddbbc72b46d9b19eb", null ],
      [ "command", "structrts__frame.html#a964158d6b5abbdf6b270ee68f5f47d1d", null ],
      [ "rolling_code", "structrts__frame.html#ab2748d2359b54160bac4602dedf227ff", null ],
      [ "remote_address", "structrts__frame.html#a1e13f78218638b484d92d51e3df6cfd9", null ]
    ] ],
    [ "rts_frame_builder", "structrts__frame__builder.html", [
      [ "rts_frame_builder_init", "group__openrts.html#ga548d086f646014651fe55561383da6da", null ],
      [ "rts_frame_builder_handle_pulse", "group__openrts.html#ga0a7bdbe14a80d21cbd6294bf30ff6933", null ],
      [ "rts_frame_builder_set_callback", "group__openrts.html#ga610780004e4d229af371f0a3512fa102", null ]
    ] ],
    [ "rts_pulse_output", "structrts__pulse__output.html", [
      [ "rts_pulse_output_init_espidf_gpio", "structrts__pulse__output.html#af6c20b47f3c8f0bd80492edbb122e905", null ],
      [ "rts_pulse_output_init_gpiod", "structrts__pulse__output.html#a534578efdd276bbda622e2bc1a4e2440", null ],
      [ "rts_pulse_output_enable", "group__openrts.html#ga25ffde10f6d05c6ee10a72cba20661b7", null ],
      [ "rts_pulse_output_disable", "group__openrts.html#gab13f5dc4c1590c8b62ee99a39f555a97", null ],
      [ "rts_pulse_output_send_pulse", "group__openrts.html#ga077cadffb99c505fc5c338975770cf05", null ],
      [ "rts_pulse_output_close", "group__openrts.html#ga828fc88c73c452a2ea0c2c32f77508da", null ]
    ] ],
    [ "rts_pulse_source", "structrts__pulse__source.html", [
      [ "rts_pulse_source_init_espidf_gpio", "structrts__pulse__source.html#a0739f646f14a3628a130e80120dec3fe", null ],
      [ "rts_pulse_source_init_gpiod", "structrts__pulse__source.html#aa898334853d0f0180a97fa4c093bff9b", null ],
      [ "rts_pulse_source_enable", "group__openrts.html#ga8a9e0325230d97d61ccbea915c89ec74", null ],
      [ "rts_pulse_source_disable", "group__openrts.html#ga45cfff3972b1a810712084835660f78c", null ],
      [ "rts_pulse_source_update", "group__openrts.html#ga331d02f4adc1a5adeffeadfe03c0c9a0", null ],
      [ "rts_pulse_source_attach", "group__openrts.html#gaf29fc3e4b2e446040c435f9400177934", null ],
      [ "rts_pulse_source_close", "group__openrts.html#gaaf1a44ffce736c880c87dac96b0e661d", null ]
    ] ],
    [ "rts_radio", "structrts__radio.html", [
      [ "rts_radio_init_rfm69", "group__openrts.html#ga2face82e870c83ded1dafde15f7e76d1", null ],
      [ "rts_radio_init_sx1278", "group__openrts.html#ga0311a0c0f3512263cef2ea6c2e1a055f", null ],
      [ "rts_radio_set_mode", "group__openrts.html#ga5c4eb3993da685313f6984b370c566d3", null ]
    ] ],
    [ "rts_receiver", "structrts__receiver.html", [
      [ "rts_receiver_init", "group__openrts.html#gafd40f0657d24a152a50b94760dce812e", null ],
      [ "rts_receiver_set_frame_callback", "group__openrts.html#ga6ad4ce1fbb9688ada6fcb41eb5245859", null ],
      [ "rts_receiver_set_mode_callback", "group__openrts.html#gacad30b70597a760b6800352ed3326f61", null ],
      [ "rts_receiver_set_mode", "group__openrts.html#gad8220ee59b348c4ed810237e95c468b1", null ],
      [ "rts_receiver_forget_all_remotes", "group__openrts.html#gabb156e720eb4e0891e1e2e5bfaff73f1", null ],
      [ "rts_receiver_update", "group__openrts.html#ga1561b9797fe677fadeb0117ea83b3177", null ]
    ] ],
    [ "rts_remote", "structrts__remote.html", [
      [ "rts_remote_init", "group__openrts.html#ga713e81bf47614d5cf50b8b6ab5d0a868", null ],
      [ "rts_remote_send_command", "group__openrts.html#ga2a109f38fb4fde769dbcf0b0d94a5a72", null ],
      [ "rts_remote_send_frame", "group__openrts.html#ga1d7ef1ec7e0ff4347b6b2bd285c205c3", null ],
      [ "rts_remote_send_pulse", "group__openrts.html#ga0b5d9329b4269cbf459cd1874c5918d0", null ]
    ] ],
    [ "rts_remote_store", "structrts__remote__store.html", [
      [ "rts_remote_store_init_nvs", "structrts__remote__store.html#afefe1fed614ea5110fed6eb69d2d9cdd", null ],
      [ "rts_remote_store_init_mmap", "structrts__remote__store.html#a947e08504299d8fe5812ec0c18a699c3", null ],
      [ "rts_remote_store_set_code", "group__openrts.html#gafd495bd856ec66c5f7b4dba72bc54ca6", null ],
      [ "rts_remote_store_get_code", "group__openrts.html#gab26b0afe0ab17f81af2a505ef4d05658", null ],
      [ "rts_remote_store_next_code", "group__openrts.html#ga558753287dc627e36b5216f5217e7177", null ],
      [ "rts_remote_store_known_remote", "group__openrts.html#ga6ecf66e04d8462b100b142cecc6a338d", null ],
      [ "rts_remote_store_forget", "group__openrts.html#ga93d26435ee32bda67ad0958cd08bfbfb", null ],
      [ "rts_remote_store_clear", "group__openrts.html#gaba1b041180b813756605331bba63a006", null ],
      [ "rts_remote_store_close", "group__openrts.html#ga55de60ac69a0b8576e52214fc51d22fe", null ],
      [ "rts_remote_store_init_memory", "group__openrts.html#ga52529ac5fcf5001a80dd19e3d490bf47", null ]
    ] ],
    [ "rts_timings", "structrts__timings.html", [
      [ "wakeup_high", "structrts__timings.html#afe93d68fa881dcf4d721157fe147cf09", null ],
      [ "wakeup_low", "structrts__timings.html#a67d2310a314cee6db5a145b3d22f8929", null ],
      [ "preamble_high", "structrts__timings.html#a266a072f05e01e3bc92f641c32f1262c", null ],
      [ "preamble_low", "structrts__timings.html#ab95bec97e093ebc1937ecece873c28d7", null ],
      [ "sync_high", "structrts__timings.html#ad8cba16a55ad5e406bd6c155d6d3f3a1", null ],
      [ "sync_low", "structrts__timings.html#a353992ae5dfd0d451bff0c88aa9e6f1b", null ],
      [ "symbol", "structrts__timings.html#acc161d1d2515ba7d267d800598a20bbe", null ],
      [ "frame_sleep", "structrts__timings.html#abc22451c60cd76d5317e43f16ac34922", null ]
    ] ],
    [ "rts_command", "group__openrts.html#ga2dc6d8f19dc54273cf451709d2e9d164", [
      [ "RTS_COMMAND_MY", "group__openrts.html#gga2dc6d8f19dc54273cf451709d2e9d164a09fa728837a8d64fb7f4bafcbde12805", null ],
      [ "RTS_COMMAND_UP", "group__openrts.html#gga2dc6d8f19dc54273cf451709d2e9d164a3a90f83ed959783ef12b278d767c3859", null ],
      [ "RTS_COMMAND_MY_UP", "group__openrts.html#gga2dc6d8f19dc54273cf451709d2e9d164a715b4ac33fd2c69f0d475350dccdb802", null ],
      [ "RTS_COMMAND_DOWN", "group__openrts.html#gga2dc6d8f19dc54273cf451709d2e9d164a917c5c8d3a9648f16b672966ca1f7a99", null ],
      [ "RTS_COMMAND_MY_DOWN", "group__openrts.html#gga2dc6d8f19dc54273cf451709d2e9d164a1a825c8e7b1fa2cf97cbb7fb861c7bd0", null ],
      [ "RTS_COMMAND_UP_DOWN", "group__openrts.html#gga2dc6d8f19dc54273cf451709d2e9d164af9ef17d36e1c8053e13516f18fe67455", null ],
      [ "RTS_COMMAND_MY_UP_DOWN", "group__openrts.html#gga2dc6d8f19dc54273cf451709d2e9d164aed2cb4fe313d305bf1cad965aa7a2db5", null ],
      [ "RTS_COMMAND_PROG", "group__openrts.html#gga2dc6d8f19dc54273cf451709d2e9d164ae2e44d311e49eeb6349eb60b41ac2f99", null ],
      [ "RTS_COMMAND_SUN_FLAG", "group__openrts.html#gga2dc6d8f19dc54273cf451709d2e9d164a2ad51e428b1f9ca2d4f7f48bb7c2d282", null ],
      [ "RTS_COMMAND_FLAG", "group__openrts.html#gga2dc6d8f19dc54273cf451709d2e9d164a9519c21df799d8153ebd6e2a43f52996", null ]
    ] ],
    [ "rts_radio_mode", "group__openrts.html#ga307d23bc496f860a9ff57bde0ca15336", [
      [ "RTS_RADIO_MODE_STANDBY", "group__openrts.html#gga307d23bc496f860a9ff57bde0ca15336a709e6461ce74ad1d3a97fe10631e76bd", null ],
      [ "RTS_RADIO_MODE_RECEIVE", "group__openrts.html#gga307d23bc496f860a9ff57bde0ca15336a92b2151744028824c9ff3867acf604ae", null ],
      [ "RTS_RADIO_MODE_TRANSMIT", "group__openrts.html#gga307d23bc496f860a9ff57bde0ca15336a5a2fd52a32e6e5ded54d751aa65d9585", null ]
    ] ],
    [ "rts_receiver_event", "group__openrts.html#gaa591089885a2aef8ea967bcb1b462615", [
      [ "RTS_RECEIVER_EVENT_NONE", "group__openrts.html#ggaa591089885a2aef8ea967bcb1b462615a20ffa88b0309d238199eb5b0a624de0a", null ],
      [ "RTS_RECEIVER_EVENT_PRESS", "group__openrts.html#ggaa591089885a2aef8ea967bcb1b462615a4701110312e3952d07bc480545f5f246", null ],
      [ "RTS_RECEIVER_EVENT_HOLD", "group__openrts.html#ggaa591089885a2aef8ea967bcb1b462615aa0d7ec27fdfde4ad520bcb6ff8d1dd8e", null ],
      [ "RTS_RECEIVER_EVENT_HOLD_2", "group__openrts.html#ggaa591089885a2aef8ea967bcb1b462615abb0eb0a9cc4038f710cd4dec72e59ee6", null ],
      [ "RTS_RECEIVER_EVENT_HOLD_3", "group__openrts.html#ggaa591089885a2aef8ea967bcb1b462615a2e7d7181e13b07c03d8b1c8f584a6afa", null ]
    ] ],
    [ "rts_receiver_mode", "group__openrts.html#ga95b9ffaba40b365472722c9736fdb05d", [
      [ "RTS_RECEIVER_MODE_OFF", "group__openrts.html#gga95b9ffaba40b365472722c9736fdb05dae296a12c397ad0f4cdb6fae91807402d", null ],
      [ "RTS_RECEIVER_MODE_PROGRAMMING", "group__openrts.html#gga95b9ffaba40b365472722c9736fdb05daaa909fc78742ee14a0c611aa2a7bca01", null ],
      [ "RTS_RECEIVER_MODE_COMMAND", "group__openrts.html#gga95b9ffaba40b365472722c9736fdb05da51a77a887a7ab7ff270872946e7839ea", null ]
    ] ],
    [ "rts_frame::rts_frame_init", "group__openrts.html#gab5571a1d421a1148d309f2858a83613f", null ],
    [ "rts_frame::rts_frame_from_bytes", "group__openrts.html#ga4223460f69635b1c97a7c9f2dd42dfb5", null ],
    [ "rts_frame::rts_frame_to_bytes", "group__openrts.html#gabee4ad16c735ef07839cbc12f9282b96", null ],
    [ "rts_frame::rts_frame_obfuscate_bytes", "group__openrts.html#gafa119ab98f70aaa2f90961c7830e882a", null ],
    [ "rts_frame::rts_frame_deobfuscate_bytes", "group__openrts.html#ga055aa8c663040dd6861a11035696bca5", null ],
    [ "rts_frame::rts_frame_generate_checksum", "group__openrts.html#ga8c6b65412d7a48442ff251fbff5360f5", null ],
    [ "rts_frame_builder::rts_frame_builder_init", "group__openrts.html#ga548d086f646014651fe55561383da6da", null ],
    [ "rts_frame_builder::rts_frame_builder_handle_pulse", "group__openrts.html#ga0a7bdbe14a80d21cbd6294bf30ff6933", null ],
    [ "rts_frame_builder::rts_frame_builder_set_callback", "group__openrts.html#ga610780004e4d229af371f0a3512fa102", null ],
    [ "rts_pulse_output::rts_pulse_output_enable", "group__openrts.html#ga25ffde10f6d05c6ee10a72cba20661b7", null ],
    [ "rts_pulse_output::rts_pulse_output_disable", "group__openrts.html#gab13f5dc4c1590c8b62ee99a39f555a97", null ],
    [ "rts_pulse_output::rts_pulse_output_send_pulse", "group__openrts.html#ga077cadffb99c505fc5c338975770cf05", null ],
    [ "rts_pulse_output::rts_pulse_output_close", "group__openrts.html#ga828fc88c73c452a2ea0c2c32f77508da", null ],
    [ "rts_pulse_source::rts_pulse_source_enable", "group__openrts.html#ga8a9e0325230d97d61ccbea915c89ec74", null ],
    [ "rts_pulse_source::rts_pulse_source_disable", "group__openrts.html#ga45cfff3972b1a810712084835660f78c", null ],
    [ "rts_pulse_source::rts_pulse_source_update", "group__openrts.html#ga331d02f4adc1a5adeffeadfe03c0c9a0", null ],
    [ "rts_pulse_source::rts_pulse_source_attach", "group__openrts.html#gaf29fc3e4b2e446040c435f9400177934", null ],
    [ "rts_pulse_source::rts_pulse_source_close", "group__openrts.html#gaaf1a44ffce736c880c87dac96b0e661d", null ],
    [ "rts_radio::rts_radio_init_rfm69", "group__openrts.html#ga2face82e870c83ded1dafde15f7e76d1", null ],
    [ "rts_radio::rts_radio_init_sx1278", "group__openrts.html#ga0311a0c0f3512263cef2ea6c2e1a055f", null ],
    [ "rts_radio::rts_radio_set_mode", "group__openrts.html#ga5c4eb3993da685313f6984b370c566d3", null ],
    [ "rts_receiver::rts_receiver_init", "group__openrts.html#gafd40f0657d24a152a50b94760dce812e", null ],
    [ "rts_receiver::rts_receiver_set_frame_callback", "group__openrts.html#ga6ad4ce1fbb9688ada6fcb41eb5245859", null ],
    [ "rts_receiver::rts_receiver_set_mode_callback", "group__openrts.html#gacad30b70597a760b6800352ed3326f61", null ],
    [ "rts_receiver::rts_receiver_set_mode", "group__openrts.html#gad8220ee59b348c4ed810237e95c468b1", null ],
    [ "rts_receiver::rts_receiver_forget_all_remotes", "group__openrts.html#gabb156e720eb4e0891e1e2e5bfaff73f1", null ],
    [ "rts_receiver::rts_receiver_update", "group__openrts.html#ga1561b9797fe677fadeb0117ea83b3177", null ],
    [ "rts_remote::rts_remote_init", "group__openrts.html#ga713e81bf47614d5cf50b8b6ab5d0a868", null ],
    [ "rts_remote::rts_remote_send_command", "group__openrts.html#ga2a109f38fb4fde769dbcf0b0d94a5a72", null ],
    [ "rts_remote::rts_remote_send_frame", "group__openrts.html#ga1d7ef1ec7e0ff4347b6b2bd285c205c3", null ],
    [ "rts_remote::rts_remote_send_pulse", "group__openrts.html#ga0b5d9329b4269cbf459cd1874c5918d0", null ],
    [ "rts_remote_store::rts_remote_store_set_code", "group__openrts.html#gafd495bd856ec66c5f7b4dba72bc54ca6", null ],
    [ "rts_remote_store::rts_remote_store_get_code", "group__openrts.html#gab26b0afe0ab17f81af2a505ef4d05658", null ],
    [ "rts_remote_store::rts_remote_store_next_code", "group__openrts.html#ga558753287dc627e36b5216f5217e7177", null ],
    [ "rts_remote_store::rts_remote_store_known_remote", "group__openrts.html#ga6ecf66e04d8462b100b142cecc6a338d", null ],
    [ "rts_remote_store::rts_remote_store_forget", "group__openrts.html#ga93d26435ee32bda67ad0958cd08bfbfb", null ],
    [ "rts_remote_store::rts_remote_store_clear", "group__openrts.html#gaba1b041180b813756605331bba63a006", null ],
    [ "rts_remote_store::rts_remote_store_close", "group__openrts.html#ga55de60ac69a0b8576e52214fc51d22fe", null ],
    [ "rts_remote_store::rts_remote_store_init_memory", "group__openrts.html#ga52529ac5fcf5001a80dd19e3d490bf47", null ],
    [ "RTS_TIMINGS_SITUO5", "group__openrts.html#ga21e1f134c3b56ede954c4377ac6804bd", null ],
    [ "RTS_TIMINGS_DEFAULT", "group__openrts.html#ga5d5a8dd247442ea155318ad1d4d6fc7b", null ]
];