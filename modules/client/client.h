#pragma once

#include "enums/action.h"
#include "enums/result.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <valarray>
#include <winerror.h>
#include <winsock2.h>

#include "nlohmann/json.hpp"


struct Response {
    Result result;
    nlohmann::ordered_json answer;

    friend std::ostream &operator<<(std::ostream &out, const Response &response);
};

class Client {
private:
    const char ADDRESS[14] = {"92.223.34.102"};
    const int PORT = 443;
    SOCKET server;                      // server descriptor
    const int PROTOCOL = AF_INET;       //socket config
    const int SOCKET_TYPE = SOCK_STREAM;// socket config
    WSAData WSAData;                    //info about connect

    void SendRequest(Action action, const std::string &msg) const;

    int GetIntFromServer() const;

    Response GetAnswer() const;

    bool debug;

public:
    Client();

    ~Client() { shutdown(server, 1); }

    Response Login(const std::string &name, const std::string &password = "",
                   const std::string &game = "", int numTurns = 0, int numPlayers = 1,
                   bool isObserver = false) const;

    Response Logout() const {
        this->SendRequest(Action::LOGOUT, "");
        return this->GetAnswer();
    }

    Response Map() const {
        this->SendRequest(Action::MAP, "");
        return this->GetAnswer();
    }

    Response GameState() const {
        this->SendRequest(Action::GAME_STATE, "");
        return this->GetAnswer();
    }

    Response GameActions() const {
        this->SendRequest(Action::GAME_ACTIONS, "");
        return this->GetAnswer();
    }

    Response Turn() const {
        this->SendRequest(Action::TURN, "");
        return this->GetAnswer();
    }

    Response Chat(const std::string &msg) const;

    Response SendTankAction(Action action, int vehicleId, int x, int y, int z) const;

    static void PrintLogInfo(const std::string &info) { std::cout << info << '\n'; }
};
