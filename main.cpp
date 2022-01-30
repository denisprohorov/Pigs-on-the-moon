#include <iostream>
//#include "modules/client/Client.h"
//#include "modules/game.h"
#include "modules/game_client.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

tuple<int, int, int> MakePosTuple(nlohmann::json&);

//void parse_map_info() {
//    char map_txt[] = R"(
//    {
//        "Map":
//              {
//                "content":
//                {
//                  "base":
//                  [
//                    {"x":-1,"y":0,"z":1},
//                    {"x":-1,"y":1,"z":0},
//                    {"x":0,"y":-1,"z":1},
//                    {"x":0,"y":0,"z":0},
//                    {"x":0,"y":1,"z":-1},
//                    {"x":1,"y":-1,"z":0},
//                    {"x":1,"y":0,"z":-1}
//                  ],
//                  "catapult":[],
//                  "hard_repair":[],
//                  "light_repair":[],
//                  "obstacle":[]
//                },
//                "name":"map01",
//                "size":11,
//                "spawn_points":
//                [
//                  {
//                    "medium_tank":
//                    [
//                      {"x":-7,"y":-3,"z":10},
//                      {"x":-6,"y":-4,"z":10},
//                      {"x":-5,"y":-5,"z":10},
//                      {"x":-4,"y":-6,"z":10},
//                      {"x":-3,"y":-7,"z":10}
//                    ]
//                  },
//                  {
//                    "medium_tank":
//                    [
//                      {"x":-7,"y":10,"z":-3},
//                      {"x": -6,"y":10,"z":-4},
//                      {"x":-5,"y":10,"z":-5},
//                      {"x":-4,"y":10,"z":-6},
//                      {"x":-3,"y":10,"z":-7}
//                    ]
//                  },
//                  {
//                    "medium_tank":
//                    [
//                      {"x":10,"y":-7,"z":-3},
//                      {"x":10,"y":-6,"z":-4},
//                      {"x":10,"y":-5,"z":-5},
//                      {"x":10,"y":-4,"z":-6},
//                      {"x":10,"y":-3,"z":-7}
//                    ]
//                  }
//                ]
//              }
//    }
//    )";
//    json map = json::parse(map_txt);
//    auto map_in = map.value("Map", json(""));
//    auto spawn_info = map_in.value("spawn_points", nlohmann::json(""));
//    auto base_info = map_in.value("content", json("")).value("base", json(""));
//    for (auto& x : map_in.items()) {
////        cout << x.value("x", -1) << endl;
//        std::cout << "key is : " << x.key()
//                  << ", value is : " << x.value() << '\n';
////        auto inx = x.value().value("medium_tank", nlohmann::json(""));
////        cout << "\tin\n";
////        for (auto& i : inx)
////            cout << "next\t" << i.value("x", -1) << endl;
//    }
////    cout << map_in.value("content", json("not_fount"));
//}

//void parse_am() {
//    char matrix_txt[] = R"(
//         {
//            "attack_matrix":
//            {
//              "406":[],
//              "303": [406, 123],
//              "123": [303]
//            }
//         }
//    )";
//    json am = json::parse(matrix_txt);
//    auto am_in = am.value("attack_matrix", json(""));
//    for(auto& pm : am_in.items()) {
//        cout << "|" << pm.key() << "|" << pm.value() << "|" << endl;
//        cout << "size: " << pm.value().size() << endl;
//        for(int i : pm.value())
//            cout << "nex v: " << i << ' ';
//        cout << endl;
//    }
//}

int main() {
    GameClient gc;
    gc.initGame("test14");
    while(gc.SendTurn() != true);
    while(gc.GameIsFinished() != true){
        gc.InitPlayersId();
        gc.SendAction();
//        std::cout << gc.getClient()->GameState();
        std::cerr << "\n---------------------------------------\n";
        gc.SendTurn();
    }


    cout << "Success";
}

