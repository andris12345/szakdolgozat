#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include <SDL3_net/SDL_net.h>
#include <SDL3/SDL.h>
#include <SDL3_net/SDL_net.h>
#include <cstring>

#include "../variables/Variables.h"

// Hálózati állapot struktura
struct NetworkState {
    bool isInitialized = false;
    bool isServer = false;
    bool isConnected = false;
    NET_Server* server = nullptr;
    NET_StreamSocket* clientSocket = nullptr;
    SDL_Thread* serverThread = nullptr;
};

// Globális hálózati állapot (a cpp fájlban definiálva)
extern NetworkState g_network;

// Inicializálás és cleanup
// Ezeket egyszer hívd meg a program elején/végén!
bool InitializeNetworking();
void CleanupNetworking();

// Szerver indítása külön szálon (nem blokkoló)
// Visszatér true-val, ha sikerült elindítani
bool StartServerAsync();

// Csatlakozás szerverhez
// hostname: pl. "127.0.0.1" vagy "192.168.1.100"
// Várja meg a kapcsolódást (max ~5 másodperc), de nem fagyasztja be teljesen a GUI-t
bool ConnectToServer(const char* hostname);

// Frissítés minden frame-ben
// Olvassa az érkező üzeneteket (csak kliens esetén érdemes hívni)
void UpdateNetworking();

// Szerver szál függvénye (ezt ne hívd közvetlenül!)
int ServerThreadFunction(void* data);
#endif //MULTIPLAYER_H
