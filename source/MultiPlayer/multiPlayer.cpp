#include "multiPlayer.h"

// Globális hálózati állapot
NetworkState g_network;

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

// Szerver szál függvénye
int ServerThreadFunction(void* data) {
    SDL_Log("Server thread started on port 12345");
    
    NET_Server* server = NET_CreateServer(nullptr, 12345);
    if (!server) {
        SDL_Log("NET_CreateServer failed: %s", SDL_GetError());
        g_network.isServer = false;
        return -1;
    }
    
    g_network.server = server;
    SDL_Log("Server listening...");
    
    // Várunk kliensekre
    while (g_network.isServer) {
        NET_StreamSocket* newClient = nullptr;
        
        // Non-blocking accept
        if (NET_AcceptClient(server, &newClient) && newClient) {
            SDL_Log("Client connected!");
            start = true;
            
            // Ha már van kliens, zárjuk be az újat (egyszerre 1 kliens)
            if (g_network.clientSocket) {
                SDL_Log("Already have a client, rejecting new connection");
                NET_DestroyStreamSocket(newClient);
            } else {
                g_network.clientSocket = newClient;
                g_network.isConnected = true;
                
                // Üdvözlő üzenet
                const char* welcome = "Welcome to the server!";
                NET_WriteToStreamSocket(g_network.clientSocket, welcome, strlen(welcome));
            }
        }
        
        // Ha van kliens, olvassunk tőle
        if (g_network.clientSocket) {
            char buffer[256];
            int bytes = NET_ReadFromStreamSocket(g_network.clientSocket, buffer, sizeof(buffer) - 1);
            
            if (bytes > 0) {
                buffer[bytes] = '\0';
                SDL_Log("Received from client: %s", buffer);
                
                // Echo vissza
                const char* reply = "Message received!";
                NET_WriteToStreamSocket(g_network.clientSocket, reply, strlen(reply));
            } else if (bytes < 0) {
                SDL_Log("Client disconnected");
                NET_DestroyStreamSocket(g_network.clientSocket);
                g_network.clientSocket = nullptr;
                g_network.isConnected = false;
            }
            // bytes == 0 azt jelenti, hogy nincs új adat (ez normális)
        }
        
        SDL_Delay(10); // Kis szünet, hogy ne égesse a CPU-t
    }
    
    SDL_Log("Server thread ending");
    return 0;
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
    if (!g_network.isInitialized) {
        SDL_Log("Network not initialized! Call InitializeNetworking() first.");
        return false;
    }
    
    if (g_network.clientSocket) {
        SDL_Log("Already connected");
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
    
    // Teszt üzenet küldése
    const char* testMsg = "Hello from client! Szeretem az oszt!";
    NET_WriteToStreamSocket(g_network.clientSocket, testMsg, strlen(testMsg));
    
    NET_UnrefAddress(address);
    return true;
}

// Frissítés minden frame-ben (ha kliens vagy és kommunikálni akarsz)
void UpdateNetworking() {
    if (!g_network.isConnected || !g_network.clientSocket) {
        return;
    }
    
    // Olvassunk a szervertől (non-blocking)
    char buffer[256];
    int bytes = NET_ReadFromStreamSocket(g_network.clientSocket, buffer, sizeof(buffer) - 1);
    
    if (bytes > 0) {
        buffer[bytes] = '\0';
        SDL_Log("Received from server: %s", buffer);
    } else if (bytes < 0) {
        SDL_Log("Connection lost");
        NET_DestroyStreamSocket(g_network.clientSocket);
        g_network.clientSocket = nullptr;
        g_network.isConnected = false;
    }
    // bytes == 0 azt jelenti, hogy nincs új adat (ez normális)
}