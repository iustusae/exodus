/**
 * @file main.cpp
 * @author iustus (lindgreiae@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <cstdlib>
#include <dpp/dpp.h>
#include <iostream>
#include <string>

#include "../res/envs.hpp"
#include "dpp/dispatcher.h"
#include "dpp/intents.h"
#include "dpp/message.h"
#include "dpp/once.h"

#include "core/SpellReader.hpp"

int main() {
  dpp::cluster bot(DISCORD_TOKEN,
                   dpp::i_default_intents | dpp::i_message_content);

  bot.on_log(dpp::utility::cout_logger());

   bot.on_slashcommand([](const dpp::slashcommand_t &event) {
    if (event.command.get_command_name() == "ping") {
      event.reply("Pong!");
    } 
  });

  bot.on_message_create([&bot](const dpp::message_create_t &event) {
    if (event.msg.content == "!spells") {
        SpellReader sp = SpellReader();
      /* create the embed */
     dpp::embed embed = sp.all_spells_to_embed();
    
      /* reply with the created embed */
      bot.message_create(dpp::message(event.msg.channel_id, embed)
                             .set_reference(event.msg.id));
    }
  });

  bot.on_ready([&bot](const dpp::ready_t &event) {
    if (dpp::run_once<struct register_bot_commands>()) {
      bot.global_command_create(
          dpp::slashcommand("ping", "ping pong", bot.me.id));
    }
  });

  bot.start(dpp::st_wait);



  
  return 0;
}
