#include "Bot.h"

#include "gui/controller/Controller.h"

void Bot::StartAI() {
    gc->StartAI();
//    gc->ConnectPlayer();
////    tree.Init(this->gc);
//    while (!gc->GameIsFinished() && !controller.GetIsWindowClose()) {
//        std::cout << "Bot\n";
//        gc->UpdateGameState();
//        if (gc->IsPlayTime())// play only our turn
////            tree.ProcessAllTanks();
//            gc->GetAIPlayer()->Play();
//#ifdef _DEBUG
//        std::cerr << "\n---------------------------------------\n";
//#endif
//        gc->SendTurn();
//    }
}
