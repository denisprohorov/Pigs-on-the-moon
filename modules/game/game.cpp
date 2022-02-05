#include "game.h"

using namespace std;
using namespace VehiclesTypes;

Vehicle *Game::Find(int adaptedPlayerId, const Point &spawn) const {
    for (auto *p : vehicles[adaptedPlayerId]) {
        if (p->GetSpawn() == spawn)
            return p;
    }
    return nullptr;
}

Game::~Game() {
    // TODO!
    delete player;
    delete map;
    for (auto &vehicle : vehicles) {
        for (auto v : vehicle) {
            delete v;
        }
    }
}

void Game::InitVariables(int playersNum) {
    numPlayers = playersNum;
    numTurns = numRounds * numPlayers;
    currentTurn = 0;

    vehicles.resize(playersNum);
    attackMatrix.resize(playersNum);
    captures.resize(playersNum);
    kills.resize(playersNum);
    tanksIdAdapter.resize(5);
    // TODO! magic constant
}

void Game::InitPlayersId(const vector<int> &realId) {
    for (int i = 0; i < realId.size(); i++) {
        playersIdAdapter[realId[i]] = i;
    }
}

void Game::InitVehiclesIds(int playerId, const vector<int> &realId) {
    if (playerId != player->GetId())
        return;
    // TODO _
    for (int i = 0; i < realId.size(); i++) {
        tanksIdAdapter[i] = realId[i];
    }
}

void Game::InitVehiclesIds(int playerId, const unordered_map<std::string, vector<int>> &realId) {
    if (playerId != player->GetId())
        return;
    int next = 0;
    for (int i = 0; i < VehiclesTypes::TypesNum; i++) {
        auto &tanks = realId.at(VehiclesTypes::s_types[i]);
        // q: is there more than one access?
        for (const auto &id : tanks) {
            tanksIdAdapter[next++] = id;
        }
    }
}

// Add

void Game::AddVehicle(int playerId, Type type, tuple<int, int, int> spawn) {
    // there choose type of tanks
    Vehicle* t;
    switch (type) {
        case MEDIUM_TANK:
            t = new MediumTank(playerId);
            break;
        case LIGHT_TANK:
            t = new LightTank(playerId);
            break;
        case HEAVY_TANK:
            t = new HeavyTank(playerId);
            break;
        case AT_SPG:
            t = new AtSpg(playerId);
            break;
        case SPG:
            t = new Spg(playerId);
    }
    t->InitSpawn(map->Get(spawn));
    vehicles[playerId].push_back(t);// there player id passed from 0 to 2 (GameClient)
}

// get state
void Game::UpdateState(int currTurn, int currPlayer, bool finished) {
    currentTurn = currTurn;
    currentPlayerId = currPlayer;
    isFinished = finished;
}

void Game::UpdateVehicleState(int parentId, Point spawn, Point pos, int health,
                              int capturePoints) {
    Vehicle *v = Find(playersIdAdapter.at(parentId), spawn);
    v->Update(health, map->Get(pos), capturePoints);
}

void Game::UpdateWinPoints(int playerId, int capture, int kill) {
    int adaptedPlayerId = playersIdAdapter.at(playerId);
    captures[adaptedPlayerId] = capture;
    kills[adaptedPlayerId] = kill;
}

bool TargetIsAvailable(const Point *target) {
    auto [x, y, z] = *target;
    return !(x == -1 && y == -1 && z == -1);
}

vector<tuple<Action, int, Hex *>> Game::Play() const {
    vector<tuple<Action, int, Hex *>> res;
    return res;
}