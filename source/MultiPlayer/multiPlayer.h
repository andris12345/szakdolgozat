#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include <SDL3_net/SDL_net.h>
#include <SDL3/SDL.h>
#include <SDL3_net/SDL_net.h>
#include <cstring>

#include "../variables/Variables.h"
#include "../unit/drawing/Drawing.h"

#include "../unit/fighter/Fighter.h"
#include "../unit/ranged/Ranged.h"
#include "../unit/tank/Tank.h"

// ============================================================================
// HÁLÓZATI ÁLLAPOT
// ============================================================================

struct NetworkState {
    bool isInitialized = false;
    bool isServer = false;
    bool isConnected = false;

    NET_Server* server = nullptr;
    NET_StreamSocket* clientSocket = nullptr;
    SDL_Thread* serverThread = nullptr;
};

extern NetworkState g_network;
extern int num;  // Debug számláló

// ============================================================================
// JÁTÉKÁLLAPOT STRUKTÚRÁK
// ============================================================================

struct GameState {
    static constexpr int MAX_UNITS = 50;

    struct PlayerData {
        float baseHp;
        float xp;
        int level;
        float money;

        int manSize;
        int poolSize;

        struct Unit {
            int tipus;
            double hp;
            double maxHp;
            SDL_FRect rect;
            SDL_Color color;
        } manUnits[MAX_UNITS], poolUnits[MAX_UNITS];

        struct Tower {
            bool exists;
            int pos;
            SDL_FRect rect;
            SDL_Color color;
            SDL_Color hoverColor;
            bool isVisible;
        } towers[2];
    };

    PlayerData player1;
    PlayerData player2;

    bool gameStarted;
    bool gameEnded;
    int winnerId;
};

enum class MessageType : uint8_t {
    // Kliens → Szerver
    CMD_SPAWN_UNIT = 1,
    CMD_READY = 2,
    CMD_BUY_TOWER = 3,
    CMD_DELETE_TOWER = 4,

    // Szerver → Kliens
    STATE_UPDATE = 100,
    EVENT_GAME_START = 101,
    EVENT_GAME_END = 102
};

struct ClientCommand {
    MessageType type;
    int unitType;

    int towerType;
    int towerposition;
};

struct NetworkMessage {
    MessageType type;
    union {
        ClientCommand command;
        GameState state;
    };
};

// ============================================================================
// SZERIALIZÁCIÓ
// ============================================================================

/**
 * User objektum szerializálása hálózati küldéshez
 * @param user A szerializálandó User objektum
 * @return Szerializált PlayerData struktúra
 */
GameState::PlayerData SerializePlayer(User& user);

/**
 * Hálózatról kapott adatok deserializálása User objektumba
 * @param user A cél User objektum
 * @param data A deserializálandó PlayerData
 */
void DeserializePlayer(User& user, const GameState::PlayerData& data);

// ============================================================================
// KLIENS FÜGGVÉNYEK
// ============================================================================

/**
 * Egység spawn parancs küldése a szervernek
 * @param unitType Egység típusa (0=Fighter, 1=Ranged, 2=Tank)
 */
void ClientSpawnUnit(int unitType);

/**
 * Torony vasarlas parancs küldése a szervernek
 * @param towerType torony típusa (0, 1)
 * @param rect torony típusa (0, 1)
 * @param towerType torony típusa (0, 1)
 */
void ClientBuyTower(int towerType, int towerPosition);

void ClientDeleteTower(int towerPosition);
/**
 * Kliens hálózati frissítés - hívd meg minden frame-ben!
 * Fogadja a szerver állapotot és frissíti a helyi játékállást
 */
void UpdateNetworking();

// ============================================================================
// SZERVER FÜGGVÉNYEK
// ============================================================================

/**
 * Kliens parancs feldolgozása (szerver oldalon)
 * @param cmd A feldolgozandó parancs
 */
void ProcessClientCommand(const ClientCommand& cmd);

void SendGameEndToClient();

/**
 * Játékállapot küldése a kliensnek
 */
void SendGameStateToClient();

/**
 * Szerver játék logika frissítése
 * Hívd meg minden tick-ben a szerver szálon
 */
void ServerUpdateGameLogic();

/**
 * Szerver szál fő függvénye
 * @param data Thread paraméterek (nem használt)
 * @return Thread kilépési kód
 */
int ServerThreadFunction(void* data);

// ============================================================================
// INICIALIZÁCIÓ ÉS CLEANUP
// ============================================================================

/**
 * SDL_net inicializálása
 * Hívd meg a program elején egyszer!
 * @return true ha sikeres, false egyébként
 */
bool InitializeNetworking();

/**
 * Hálózati erőforrások felszabadítása
 * Hívd meg a program végén!
 */
void CleanupNetworking();

/**
 * Szerver indítása külön szálon (nem blokkoló)
 * @return true ha sikeres, false egyébként
 */
bool StartServerAsync();

/**
 * Csatlakozás szerverhez (kliens oldal)
 * @param hostname Szerver címe (pl. "127.0.0.1" vagy "example.com")
 * @return true ha sikeres csatlakozás, false egyébként
 */
bool ConnectToServer(const char* hostname);
#endif //MULTIPLAYER_H
