#pragma once

#include "nlohmann/json.hpp"
#include "client/client.h"
#include "game/game.h"

class GameClient {
public:
    GameClient(bool debug = true);

    // must be called once and first.
    bool initGame(const std::string& name, const std::string& password = "",
                  const std::string& game_name="", int num_turns = 0, int num_players = 1,
                  bool is_observer = false);

    [[nodiscard]] bool GameIsFinished() const;

    void CheckGameState();

//    void CheckGameAction();  Do we really need this?

    ~GameClient();

    bool SendTurn() const;

    void SendAction() const;
    void InitPlayersId();

    Client *getClient() const;

    bool isOurTurn();

private:

    // entities
    Game* game;
    Client* client;
    tuple<int, int, int> MakePosTuple(const nlohmann::ordered_json& coordinate) {
        return make_tuple(
                coordinate.value("x", -1),
                coordinate.value("y", -1),
                coordinate.value("z", -1)
        );
    }

};


