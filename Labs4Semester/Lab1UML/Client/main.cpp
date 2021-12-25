/**
\file
\brief main file

entry point, unit tests
*/

#include "GameModel.h"
#include "ClientController.h"
#include "GameRender.h"
#include "ClientController.h"
#include "MenuController.h"
#include "SignController.h"
#include "LeadersController.h"
#include "LeadersRender.h"
#include "NetworkManager.h"
#include "Assets.h"

#include <fstream>

/**
   macros to launch unit tests in existing entry point
 */
#define DOCTEST_CONFIG_IMPLEMENT

 /**
    unit tests (if macros is defined)
 */
#ifdef DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <random>

 /**
    random device mersenne
 */
std::random_device rd;
std::mt19937 mersenne(rd());

/**
   testing game model
*/
TEST_CASE("testing game model") {
    using namespace Docking::Client;
    GameModel& model = GameModel::Get();

    model.Restore();

    CHECK(model.GetWinner() == 0);
    CHECK(model.GetElement({ 0,5 }) == 1);

    model.SetElement(2, { 0,5 });
    CHECK(model.GetElement({ 0,5 }) == 2);

    model.SetWinner(1);
    CHECK(model.GetWinner() == 1);

    CHECK(model.GetPlayers().size() == 0);
    model.AddPlayer(Player("player",10));
    CHECK(model.GetPlayers().size() == 1);
    CHECK(model.GetPlayers()[0].GetName() == "player");
    CHECK(model.GetPlayers()[0].GetWins() == 10);

    model.GetPlayers().clear();

    model.Restore();
}

/**
   testing leaders render
*/
TEST_CASE("testing leaders render") {
    using namespace Docking::Client;
    LeadersRender& render = LeadersRender::Get();
    render.Restore();
    CHECK(render.GetName() == "");
    render.SetPlayer(Player("name", 5));
    CHECK(render.GetName() == "name");

    render.EraseLetter();
    CHECK(render.GetName() == "nam");

    render.AddLetter('e');
    CHECK(render.GetName() == "name");

    render.AddLetter('1');
    CHECK(render.GetName() == "name1");
    render.AddLetter('2');
    CHECK(render.GetName() == "name12");
    render.AddLetter('3');
    CHECK(render.GetName() == "name123");
    render.AddLetter('4');
    CHECK(render.GetName() == "name1234");
    render.AddLetter('5');
    CHECK(render.GetName() == "name12345");
    render.AddLetter('6');
    CHECK(render.GetName() == "name123456");
    //!!
    render.AddLetter('7');
    CHECK(render.GetName() == "name123456");

    render.EraseLetter();
    CHECK(render.GetName() == "name12345");

    render.Restore();
}

/**
   testing player
*/
TEST_CASE("testing player") {
    Docking::Client::Player player("abc", 20);
    CHECK(player.GetName() == "abc");
    player.SetName("abb");
    CHECK(player.GetName() == "abb");
    CHECK(player.GetWins() == 20);
    player.SetWins(21);
    CHECK(player.GetWins() == 21);
}

/**
   testing sign render
*/
TEST_CASE("testing sign render") {
    Docking::Client::SignRender& render = Docking::Client::SignRender::Get();
    render.SetFocus(false);
    CHECK(render.GetName() == "");
    CHECK(render.GetPassword() == "");
    render.AddLetter('a');
    CHECK(render.GetName() == "a");
    CHECK(render.GetPassword() == "");
    render.AddLetter('b');
    CHECK(render.GetName() == "ab");
    CHECK(render.GetPassword() == "");
    render.SetFocus(true);
    CHECK(render.GetName() == "ab");
    CHECK(render.GetPassword() == "");
    render.AddLetter('a');
    CHECK(render.GetName() == "ab");
    CHECK(render.GetPassword() == "a");
    render.AddLetter('b');
    CHECK(render.GetName() == "ab");
    CHECK(render.GetPassword() == "ab");
    render.SetFocus(false);
    for (int i = 0; i < 8; i++) {
        render.AddLetter('.');
    }
    std::string expected = "ab........";
    CHECK(expected == render.GetName());
    render.AddLetter('.');
    //!!
    CHECK(expected == render.GetName());
    render.SetFocus(true);
    for (int i = 0; i < 8; i++) {
        render.AddLetter('.');
    }
    CHECK(expected == render.GetPassword());
    render.AddLetter('.');
    //!!
    CHECK(expected == render.GetPassword());
    expected.resize(9);
    render.EraseLetter();
    CHECK(expected == render.GetPassword());
    for (int i = 0; i < 9; i++) {
        render.EraseLetter();
    }
    render.SetFocus(false);
    render.EraseLetter();
    CHECK(expected == render.GetName());
    for (int i = 0; i < 9; i++) {
        render.EraseLetter();
    }
}
#endif

/**
   \brief entry point

   runs unit tests and launch client application
*/
int main(){
    using namespace Docking::Client;
    sf::RenderWindow window(sf::VideoMode(640, 690), "Docking", sf::Style::Titlebar | sf::Style::Close);

    std::ifstream fin("config.txt");
    int port;
    fin >> port;
    fin.close();
    NetworkManager::Create("localhost", port);
    Assets::Create();
    ClientController::Create(window);
    GameModel::Create();
    GameRender::Create(window);
    GameController::Create();
    MenuRender::Create(window);
    MenuController::Create();
    SignRender::Create(window);
    SignController::Create();
    LeadersRender::Create(window);
    LeadersController::Create();

#ifdef DOCTEST_CONFIG_IMPLEMENT
    doctest::Context context;
    int res = context.run();
#endif

    Docking::Client::ClientController::Get().Run();

	return 0;
}