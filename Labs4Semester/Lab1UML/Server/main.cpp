#include <iostream>
#include "Server.h"
#include "Player.h"

#define DOCTEST_CONFIG_IMPLEMENT

#ifdef DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <random>
std::random_device rd;
std::mt19937 mersenne(rd());

TEST_CASE("testing players storage") {
    using namespace Docking::Server;
    PlayersStorage storage;
    bool success = storage.SignUp("aaa", "aaa");
    if (!success) {
        CHECK(storage.SignIn("aaa", "aaa"));
        int wins = storage.GetWins("aaa");
        storage.Win("aaa");
        CHECK(wins + 1 == storage.GetWins("aaa"));
    }
    else {
        storage.SignOut("aaa");
        CHECK(storage.SignIn("aaa", "aaa"));
        CHECK(storage.GetWins("aaa") == 0);
        storage.Win("aaa");
        CHECK(1 == storage.GetWins("aaa"));
    }
}

TEST_CASE("testing player") {
    using namespace Docking::Server;
    sf::TcpSocket socket0;
    Player player0(0, socket0);
    CHECK(player0.GetId() == 0);
    player0.SetName("a");
    CHECK(player0.GetName() == "a");
    player0.SetWins(5);
    CHECK(player0.GetWins() == 5);
    player0.SetGame(0);
    CHECK(player0.GetGame() == 0);
}

TEST_CASE("testing game") {
    using namespace Docking::Server;
    sf::TcpSocket socket0;
    Player player0(0, socket0);
    sf::TcpSocket socket1;
    Player player1(1, socket1);
    Game game;
    game.ConnectPlayer(player0);
    game.Clear();
    game.ConnectPlayer(player0);
    game.ConnectPlayer(player1);
    SUBCASE("Testing game basics") {    
        CHECK(game.AnotherPlayerId(0) == 1);
        CHECK(game.AnotherPlayerId(1) == 0);
        CHECK(game.CurrentPlayer() == 0);
        game.SetPosition(2,2);
        CHECK(game.GetPosition().x == 2);
        CHECK(game.GetPosition().y == 2);
        CHECK(game.IsCompleted());
    }
    SUBCASE("Game process") {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                game.SetElement(0, { i,j });
            }
        }
        SUBCASE("testing blocking") {
            SUBCASE("corner") {
                game.SetElement(1, { 0,0 });
                CHECK(!game.CheckClosed({ 0,0 }));
                game.SetElement(2, { 0,1 });
                game.SetElement(2, { 1,0 });
                CHECK(game.CheckClosed({ 0,0 }));
            }
            SUBCASE("") {
                game.SetElement(1, { 2,0 });
                CHECK(!game.CheckClosed({ 2,0 }));
                game.SetElement(2, { 1,0 });
                game.SetElement(2, { 3,0 });
                game.SetElement(2, { 2,1 });
                CHECK(game.CheckClosed({ 2,0 }));
            }
            SUBCASE("center") {
                game.SetElement(2, { 5,5 });
                CHECK(!game.CheckClosed({ 5,5 }));
                game.SetElement(1, { 5,4 });
                game.SetElement(1, { 5,6 });
                game.SetElement(1, { 4,5 });
                game.SetElement(1, { 6,5 });
                CHECK(game.CheckClosed({ 5,5 }));
            }
        }
        SUBCASE("testing connecting") {
            SUBCASE("vertically") {
                for (int i = 0; i < 8; i++) {
                    SUBCASE("") {
                        CHECK(!game.IsEnd());
                        for (int j = 0; j < 8; j++) {
                            game.SetElement(1, { i,j });
                        }
                        CHECK(game.IsEnd());
                    }
                }
            }
            SUBCASE("horizontally") {
                for (int i = 0; i < 8; i++) {
                    SUBCASE("") {
                        CHECK(!game.IsEnd());
                        for (int j = 0; j < 8; j++) {
                            game.SetElement(1, { j,i });
                        }
                        CHECK(game.IsEnd());
                    }
                }
            }
            SUBCASE("another figure") {
                game.SetElement(1, { 1,3 });
                game.SetElement(1, { 2,3 });
                game.SetElement(1, { 2,2 });
                game.SetElement(1, { 2,4 });
                game.SetElement(1, { 3,4 });
                game.SetElement(1, { 4,4 });
                game.SetElement(1, { 4,5 });
                game.SetElement(1, { 5,3 });
                CHECK(!game.IsEnd());
                game.SetElement(0, { 5,3 });
                game.SetElement(1, { 4,3 });
                CHECK(game.IsEnd());
            }
        }
    }
}
#endif

int main()
{
    Docking::Server::Server::Create();
#ifdef DOCTEST_CONFIG_IMPLEMENT
    doctest::Context context;
    int res = context.run();
#endif
    Docking::Server::Server::Get().Run();
}