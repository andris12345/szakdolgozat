#include "multiPlayer.h"

// Globális hálózati állapot
NetworkState g_network;
int num = 0;

// ============================================================================
// SZERIALIZÁCIÓ: User → GameState.PlayerData
// ============================================================================

GameState::PlayerData SerializePlayer(User& user) {
    GameState::PlayerData data = {};

    data.baseHp = user.getBaseHp();
    data.xp = user.getXp();
    data.level = user.getLevel();
    data.money = user.getMoney();
    data.manSize = user.getManSize();
    data.poolSize = user.getPoolSize();

    // Towers szerializálása (0-1 index)
    for (int i = 0; i < 2; i++) {
        Tower* tower = user.getTowerAt(i);
        data.towers[i].exists = tower->isExists();
        data.towers[i].pos = tower->getPos();
        data.towers[i].rect = tower->getRect();
        data.towers[i].color = tower->getColor();
        data.towers[i].hoverColor = tower->getHoverColor();
        data.towers[i].isVisible = tower->getIsVisible();
    }

    // Man units szerializálása
    for (int i = 0; i < user.getManSize(); i++) {
        GameUnit* unit = user.getManAt(i);
        if (unit) {
            data.manUnits[i].tipus = unit->getTipus();
            data.manUnits[i].hp = unit->getHp();
            data.manUnits[i].maxHp = unit->getMaxHp();
            data.manUnits[i].rect = unit->getRect();
            data.manUnits[i].color = unit->getColor();
        }
    }

    // Pool units szerializálása
    for (int i = 0; i < user.getPoolSize(); i++) {
        GameUnit* unit = user.getPoolAt(i);
        if (unit) {
            data.poolUnits[i].tipus = unit->getTipus();
            data.poolUnits[i].hp = unit->getHp();
            data.poolUnits[i].maxHp = unit->getMaxHp();
            data.poolUnits[i].rect = unit->getRect();
            data.poolUnits[i].color = unit->getColor();
        }
    }

    return data;
}

// ============================================================================
// DESERIALIZÁCIÓ: GameState.PlayerData → User
// ============================================================================

void DeserializePlayer(User& user, const GameState::PlayerData& data) {
    user.setBaseHp(data.baseHp);
    user.setXp(data.xp);
    user.setLevel(data.level);
    user.setMoney(data.money);

    // Towers visszaállítása
    for (int i = 0; i < 2; i++) {
        // Tower létrehozása a szerializált adatokból
        auto tower = std::make_unique<Tower>();
        tower->setExists(data.towers[i].exists);
        tower->setPos(data.towers[i].pos);
        tower->setRect(data.towers[i].rect);
        tower->setColor(data.towers[i].color);
        tower->setHoverColor(data.towers[i].hoverColor);
        tower->setIsVisible(data.towers[i].isVisible);

        user.setTowerAt(i, std::move(tower));
    }

    // Man units
    if (data.manSize != user.getManSize()) {
        user.reallocMan(data.manSize);
    }

    // Feltöltjük az adatokat
    for (int i = 0; i < data.manSize; i++) {
        GameUnit* unit = user.getManAt(i);

        if (unit) {
            unit->setHp(data.manUnits[i].hp);
            unit->setMaxHp(data.manUnits[i].maxHp);
            unit->setRect(data.manUnits[i].rect);
            unit->setColor(data.manUnits[i].color);
        }
    }
    user.setManSize(data.manSize);

    // Pool units
    if (data.poolSize != user.getPoolSize()) {
        user.reallocPool(data.poolSize);
    }
    for (int i = 0; i < data.poolSize; i++) {
        GameUnit* unit = user.getPoolAt(i);
        if (unit) {
            unit->setHp(data.poolUnits[i].hp);
            unit->setMaxHp(data.poolUnits[i].maxHp);
            unit->setRect(data.poolUnits[i].rect);
            unit->setColor(data.poolUnits[i].color);
        }
    }
    user.setPoolSize(data.poolSize);
}

// ============================================================================
// KLIENS FÜGGVÉNYEK
// ============================================================================

// Egység küldése (amikor a játékos megnyom egy gombot)
void ClientSpawnUnit(int unitType) {
    if (!g_network.clientSocket || !g_network.isConnected) {
        SDL_Log("[CLIENT] Not connected!");
        return;
    }

    NetworkMessage msg;
    msg.type = MessageType::CMD_SPAWN_UNIT;
    msg.command.type = MessageType::CMD_SPAWN_UNIT;
    msg.command.unitType = unitType;

    int sent = NET_WriteToStreamSocket(g_network.clientSocket, &msg, sizeof(NetworkMessage));
    if (sent > 0) {
        SDL_Log("[CLIENT] Spawned unit type %d", unitType);
    } else {
        SDL_Log("[CLIENT] Failed to spawn unit");
    }
}

void ClientBuyTower(int towerType, int towerPosition) {
    if (!g_network.clientSocket || !g_network.isConnected) {
        SDL_Log("[CLIENT] Not connected!");
        return;
    }

    NetworkMessage msg;
    msg.type = MessageType::CMD_BUY_TOWER;
    msg.command.type = MessageType::CMD_BUY_TOWER;
    msg.command.towerType = towerType;
    msg.command.towerposition = towerPosition;

    int sent = NET_WriteToStreamSocket(g_network.clientSocket, &msg, sizeof(NetworkMessage));
    if (sent > 0) {
        SDL_Log("[CLIENT] Bought tower type %d, position %d", towerType, towerPosition);
    } else {
        SDL_Log("[CLIENT] Failed to spawn unit");
    }
}

void ClientDeleteTower(int towerPosition) {
    if (!g_network.clientSocket || !g_network.isConnected) {
        SDL_Log("[CLIENT] Not connected!");
        return;
    }

    NetworkMessage msg;
    msg.type = MessageType::CMD_DELETE_TOWER;
    msg.command.type = MessageType::CMD_DELETE_TOWER;
    msg.command.towerposition = towerPosition;

    int sent = NET_WriteToStreamSocket(g_network.clientSocket, &msg, sizeof(NetworkMessage));
    if (sent > 0) {
        SDL_Log("[CLIENT] Bought tower position %d", towerPosition);
    } else {
        SDL_Log("[CLIENT] Failed to spawn unit");
    }
}


// Frissítés minden frame-ben (ha kliens vagy és kommunikálni akarsz)
void UpdateNetworking() {
    if (!g_network.isConnected || !g_network.clientSocket) {
        return;
    }

    NetworkMessage msg = {};
    int bytes = NET_ReadFromStreamSocket(g_network.clientSocket, &msg, sizeof(NetworkMessage));


    if (bytes == sizeof(NetworkMessage)) {
        switch (msg.type) {
            case MessageType::STATE_UPDATE:
                // Játékállapot frissítés
                DeserializePlayer(player1, msg.state.player1);
                DeserializePlayer(player2, msg.state.player2);

                if (player1.getMoney() == 50) {
                    SDL_Log("[CLIENT] Player 1 has man man");
                }
                SDL_Log("%d: [CLIENT] State - P1[HP:%.0f XP:%.0f Lv:%d Man:%d Money:%.0f] P2[HP:%.0f Man:%dMoney:%.0f]",
                     num, msg.state.player1.baseHp, msg.state.player1.xp, msg.state.player1.level,
                     msg.state.player1.manSize, msg.state.player1.money, msg.state.player2.baseHp, msg.state.player2.manSize, msg.state.player1.money);
                num++;
                break;

            case MessageType::EVENT_GAME_START:
                SDL_Log("[CLIENT] Game started!");
                start = true;
                break;

            case MessageType::EVENT_GAME_END:
                SDL_Log("[CLIENT] Game ended! Winner: %d", msg.state.winnerId);
                break;

            default:
                break;
        }
    } else if (bytes < 0) {
        SDL_Log("[CLIENT] Connection lost");
        NET_DestroyStreamSocket(g_network.clientSocket);
        g_network.clientSocket = nullptr;
        g_network.isConnected = false;
    }
}

// ============================================================================
// SZERVER FÜGGVÉNYEK
// ============================================================================

// Parancs feldolgozása (egység létrehozása)
void ProcessClientCommand(const ClientCommand& cmd) {
    switch (cmd.type) {
        case MessageType::CMD_SPAWN_UNIT:
            SDL_Log("[SERVER] Client wants to spawn unit type %d", cmd.unitType);
            switch (cmd.unitType) {
                case 0: {
                    Fighter fighter = Fighter(0, (12 + (12 * player2.getLevel() * 0.25)),(2 + (2 * player2.getLevel() * 0.25)), true);
                    fighter.setPrice(10 + 10 * player2.getLevel() * 0.25);
                    fighter.setXp(10 + 10 * player2.getLevel() * 0.25); 
                    player2.setMoney(player2.getMoney() - fighter.getPrice());
                    CreateManToPool(fighter, true);
                    break;
                }
                case 1: {
                    Ranged ranged = Ranged(1, (8 + (8 * player2.getLevel() * 0.25)), (2 + (2 * player2.getLevel() * 0.25)), true);
                    ranged.setPrice(15 + 15 * player2.getLevel() * 0.25);
                    ranged.setXp(10 + 10 * player2.getLevel() * 0.25);
                    player2.setMoney(player2.getMoney() - ranged.getPrice());
                    CreateManToPool(ranged, true);
                    break;
                }
                case 2: {
                    Tank tank = Tank(2, (16 + (16 * player2.getLevel() * 0.25)), (2 + (2 * player2.getLevel() * 0.25)), true);
                    tank.setPrice(20 + 20 * player2.getLevel() * 0.25);
                    tank.setXp(20 + 20 * player2.getLevel() * 0.25);
                    player2.setMoney(player2.getMoney() - tank.getPrice());
                    CreateManToPool(tank, true);
                    break;
                }
                default:
                    break;
            }
            break;

        case MessageType::CMD_BUY_TOWER:
            CreateNewTower(cmd.towerType, cmd.towerposition, true);
            player2.setMoney(player2.getMoney() - (player2.getTowerAt(cmd.towerposition)->getCost()));
            break;

        case MessageType::CMD_DELETE_TOWER:
            player2.setMoney(player2.getMoney() + (player2.getTowerAt(cmd.towerposition)->getCost()/2));
            player2.getTowerAt(cmd.towerposition)->resetTower();
            break;

        case MessageType::CMD_READY:
            SDL_Log("[SERVER] Client ready");
            start = true;
            break;

        default:
            break;
    }
}

// Játékállapot küldése a kliensnek
void SendGameStateToClient() {
    float p = (mezoszelesseg * mezoszam) / 2.0f + 100.0f;
    if (!g_network.clientSocket || !g_network.isConnected) {
        return;
    }

    NetworkMessage msg;
    msg.type = MessageType::STATE_UPDATE;
    msg.state.player1 = SerializePlayer(player2);
    if (msg.state.player1.manSize != 0) {
        for (int i = 0; i < msg.state.player1.manSize; i++) {
            msg.state.player1.manUnits[i].rect.x = ( 2.0f * p - msg.state.player1.manUnits[i].rect.x) - emberszelesseg;
        }
    }
    if (msg.state.player1.poolSize != 0) {
        for (int i = 0; i < msg.state.player1.poolSize; i++) {
            msg.state.player1.poolUnits[i].rect.x = ( 2.0f * p - msg.state.player1.poolUnits[i].rect.x) - emberszelesseg;
        }
    }
    for (int i = 0; i < 2; i++) {
        if (msg.state.player1.towers[i].exists) {
            msg.state.player1.towers[i].rect.x = (2.0f * p - msg.state.player1.towers[i].rect.x) - msg.state.player1.towers[i].rect.w;
        }
    }


    msg.state.player2 = SerializePlayer(player1);
    if (msg.state.player2.manSize != 0) {
        for (int i = 0; i < msg.state.player2.manSize; i++) {
            msg.state.player2.manUnits[i].rect.x = ( 2.0f * p - msg.state.player2.manUnits[i].rect.x) - emberszelesseg;
        }
    }
    if (msg.state.player2.poolSize != 0) {
        for (int i = 0; i < msg.state.player2.poolSize; i++) {
            msg.state.player2.poolUnits[i].rect.x = ( 2.0f * p - msg.state.player2.poolUnits[i].rect.x) - emberszelesseg;
        }
    }
    for (int i = 0; i < 2; i++) {
        if (msg.state.player2.towers[i].exists) {
            msg.state.player2.towers[i].rect.x = (2.0f * p - msg.state.player2.towers[i].rect.x) - msg.state.player2.towers[i].rect.w;
        }
    }

    msg.state.gameStarted = start;
    msg.state.gameEnded = false;
    msg.state.winnerId = 0;

    bool sent = NET_WriteToStreamSocket(g_network.clientSocket, &msg, sizeof(NetworkMessage));
    if (sent) {
         //SDL_Log("[SERVER] Sent state true");
    }
    if (msg.state.player1.baseHp != 50) {
        SDL_Log("[CLIENT] Client health");
    }
    SDL_Log("%d: [CLIENT] State - P1[HP:%.0f XP:%.0f Lv:%d Man:%d Money:%.0f] P2[HP:%.0f Man:%dMoney:%.0f]",
                     num, msg.state.player1.baseHp, msg.state.player1.xp, msg.state.player1.level,
                     msg.state.player1.manSize, msg.state.player1.money, msg.state.player2.baseHp, msg.state.player2.manSize, msg.state.player1.money);
    num++;
}

// Játék logika frissítése (szerver oldalon minden tick-ben!)
void ServerUpdateGameLogic() {
    // ITT TÖRTÉNIK MINDEN JÁTÉK LOGIKA!

    // 1. Egységek mozgatása
    // MoveAllUnits(player1);
    // MoveAllUnits(player2);

    // 2. Támadások
    // ProcessCombat(player1, player2);

    // 3. Collision detection
    // CheckCollisions(player1, player2);

    // 4. XP és pénz számítás
    // UpdateRewards(player1, player2);

    // 5. Szint növelés ellenőrzése
    // CheckLevelUp(player1);
    // CheckLevelUp(player2);

    // 6. Győzelem ellenőrzése
    // if (player1.getBaseHp() <= 0 || player2.getBaseHp() <= 0) {
    //     // Game over
    // }

    //SDL_Log("[SERVER] Game tick completed");
}

// Szerver szál
int ServerThreadFunction(void* data) {
    SDL_Log("[SERVER] Thread started on port 12345");

    NET_Server* net_server = NET_CreateServer(nullptr, 12345);
    if (!net_server) {
        SDL_Log("[SERVER] Failed to create server: %s", SDL_GetError());
        g_network.isServer = false;
        return -1;
    }

    g_network.server = net_server;
    SDL_Log("[SERVER] Listening...");

    uint32_t lastGameTick = SDL_GetTicks();
    const uint32_t GAME_TICK_INTERVAL = 16;  // ~60 FPS game logic

    while (g_network.isServer) {
        int while_start = SDL_GetTicks();
        // Új kliens fogadása
        NET_StreamSocket* newClient = nullptr;
        if (NET_AcceptClient(net_server, &newClient) && newClient) {
            SDL_Log("[SERVER] Client connected!");
            start = true;
            server = true;
            if (g_network.clientSocket) {
                NET_DestroyStreamSocket(newClient);
            } else {
                g_network.clientSocket = newClient;
                g_network.isConnected = true;

                // Kezdeti állapot küldése
                SendGameStateToClient();
            }
        }

        // Parancsok fogadása
        if (g_network.clientSocket) {
            NetworkMessage msg;
            int bytes = NET_ReadFromStreamSocket(g_network.clientSocket, &msg, sizeof(NetworkMessage));

            if (bytes == sizeof(NetworkMessage)) {
                ProcessClientCommand(msg.command);
            } else if (bytes < 0) {
                SDL_Log("[SERVER] Client disconnected");
                NET_DestroyStreamSocket(g_network.clientSocket);
                g_network.clientSocket = nullptr;
                g_network.isConnected = false;
            }
        }

        // JÁTÉK LOGIKA FUTTATÁSA (minden tick-ben!)
        uint32_t currentTime = SDL_GetTicks();
        if (currentTime - lastGameTick >= GAME_TICK_INTERVAL) {
            lastGameTick = currentTime;

            if (g_network.isConnected && start) {
                // Játék frissítése
                ServerUpdateGameLogic();

                // Állapot küldése a kliensnek
                SendGameStateToClient();
            }
        }
        //fix fps
        int while_frameTime = SDL_GetTicks() - while_start;
        if (while_frameTime < (1000 / TARGET_FPS)) {
            SDL_Delay((1000 / TARGET_FPS) - while_frameTime);
        }

        SDL_Delay(1);  // Kicsi delay, hogy ne égesse a CPU-t
    }

    SDL_Log("[SERVER] Thread ending");
    return 0;
}

// ============================================================================
// INICIALIZÁCIÓ
// ============================================================================

// Inicializálás (egyszer hívd meg a program elején, pl. main()-ben)
bool InitializeNetworking() {
    if (g_network.isInitialized) {
        return true; // Már inicializálva van
    }
    
    if (!NET_Init()) {
        SDL_Log("NET_Init failed: %s", SDL_GetError());
        return false;
    }
    
    g_network.isInitialized = true;
    SDL_Log("SDL_net initialized successfully");
    return true;
}

// Cleanup (egyszer hívd meg a program végén)
void CleanupNetworking() {
    if (!g_network.isInitialized) {
        return;
    }
    
    // Jelezzük a szerver szálnak, hogy álljon le
    g_network.isServer = false;
    
    // Szerver szál leállítása
    if (g_network.serverThread) {
        SDL_WaitThread(g_network.serverThread, nullptr);
        g_network.serverThread = nullptr;
    }
    
    // Szerver bezárása
    if (g_network.server) {
        NET_DestroyServer(g_network.server);
        g_network.server = nullptr;
    }
    
    // Kliens bezárása
    if (g_network.clientSocket) {
        NET_DestroyStreamSocket(g_network.clientSocket);
        g_network.clientSocket = nullptr;
    }
    
    NET_Quit();
    g_network.isInitialized = false;
    SDL_Log("SDL_net cleaned up");
}

// Szerver indítása külön szálon (nem blokkoló!)
bool StartServerAsync() {
    if (!g_network.isInitialized) {
        SDL_Log("Network not initialized! Call InitializeNetworking() first.");
        return false;
    }
    
    if (g_network.isServer) {
        SDL_Log("Server already running");
        return false;
    }
    
    g_network.isServer = true;
    g_network.serverThread = SDL_CreateThread(ServerThreadFunction, "ServerThread", nullptr);
    
    if (!g_network.serverThread) {
        SDL_Log("Failed to create server thread: %s", SDL_GetError());
        g_network.isServer = false;
        return false;
    }
    
    SDL_Log("Server thread created successfully");
    return true;
}

// Csatlakozás szerverhez (nem blokkoló - de várunk a kapcsolatra!)
bool ConnectToServer(const char* hostname) {
    if (!g_network.isInitialized || g_network.clientSocket) {
        return false;
    }

    SDL_Log("Resolving hostname: %s", hostname);
    NET_Address* address = NET_ResolveHostname(hostname);
    if (!address) {
        SDL_Log("NET_ResolveHostname failed: %s", SDL_GetError());
        return false;
    }
    
    // Várunk a DNS feloldásra (max 5 másodperc)
    NET_Status status = NET_WaitUntilResolved(address, 5000);
    if (status != NET_SUCCESS) {
        SDL_Log("Address resolution failed: %s", SDL_GetError());
        NET_UnrefAddress(address);
        return false;
    }
    
    SDL_Log("Creating client connection to port 12345");
    NET_StreamSocket* sock = NET_CreateClient(address, 12345);
    if (!sock) {
        SDL_Log("NET_CreateClient failed: %s", SDL_GetError());
        NET_UnrefAddress(address);
        return false;
    }
    
    // Várunk a kapcsolódásra (max 5 másodperc)
    status = NET_WaitUntilConnected(sock, 5000);
    if (status != NET_SUCCESS) {
        SDL_Log("Connection failed: %s", SDL_GetError());
        NET_DestroyStreamSocket(sock);
        NET_UnrefAddress(address);
        return false;
    }
    
    g_network.clientSocket = sock;
    g_network.isConnected = true;
    SDL_Log("Connected to server!");
    
    NET_UnrefAddress(address);
    return true;
}

