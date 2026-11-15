#include <WiFi.h>
#include <WebServer.h>

boolean tipo = true;
boolean inverter = true;
int adjustedNumber = 0;

const char* ssid = "NOME_DA_REDE";
const char* password = "SENHA_DA_REDE";

WebServer server(80);

// Static IP configuration
IPAddress local_IP(192, 168, 1, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Controle de Placar Esportivo</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 20px;
            background-color: #1a1a1a;
            color: #ffffff;
            min-height: 100vh;
            box-sizing: border-box;
        }
        .nav-container {
            display: flex;
            justify-content: center;
            margin-bottom: 20px;
        }
        .nav-button {
            background-color: #28a745;
            color: #ffffff;
            padding: 12px 20px;
            border: none;
            border-radius: 5px;
            text-decoration: none;
            font-weight: bold;
            cursor: pointer;
            font-size: 1rem;
            transition: background-color 0.3s;
            text-align: center;
            max-width: 300px;
            width: 100%;
        }
        .nav-button:hover {
            background-color: #218838;
        }
        .container {
            display: grid;
            grid-template-columns: 1fr 1fr 1fr;
            gap: 20px;
            width: 100%;
            max-width: 1200px;
            margin: 0 auto;
        }
        .column {
            text-align: center;
            background-color: rgba(40, 40, 40, 0.8);
            border-radius: 10px;
            padding: 20px;
        }
        h1 {
            font-size: 1.5rem;
            margin-bottom: 20px;
            text-transform: uppercase;
        }
        button {
            background-color: #28a745;
            color: #ffffff;
            border: none;
            border-radius: 5px;
            padding: 12px 20px;
            margin: 10px auto;
            cursor: pointer;
            font-size: 1rem;
            font-weight: bold;
            width: 100%;
            max-width: 200px;
            display: block;
            transition: background-color 0.3s;
        }
        button:hover {
            background-color: #218838;
        }
        #numberInput {
            width: 60px;
            text-align: center;
            border: none;
            border-radius: 5px;
            padding: 12px;
            background-color: #ffffff;
            color: #000000;
            font-size: 1rem;
            margin: 0 5px;
        }
        .time-controls {
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 10px;
            margin: 20px 0;
        }
        .time-controls button {
            width: auto;
            padding: 10px 15px;
            margin: 0;
        }
        @media (max-width: 767px) {
            .container {
                grid-template-columns: 1fr;
            }
            .column {
                padding: 15px;
            }
            button {
                padding: 10px 15px;
                font-size: 0.9rem;
                max-width: 180px;
            }
            h1 {
                font-size: 1.3rem;
            }
        }
    </style>
    <script>
        function loadInitialStates() {
            fetch('/getStates')
                .then(response => response.json())
                .then(data => {
                    document.querySelector('button[onclick^="toggleOrder"]').innerText = 
                        data.tipo ? "Crescente" : "Decrescente";
                    document.querySelector('button[onclick^="toggleInvert"]').innerText = 
                        data.inverter ? "Inverter +" : "Inverter -";
                });
        }
        window.onload = loadInitialStates;
        
        function sendCommand(command) {
            fetch('/' + command)
                .then(response => {
                    if(command === 'crescente' || command === 'inverter') {
                        return response.json();
                    }
                    return response.text();
                })
                .then(data => {
                    if(command === 'crescente') {
                        document.querySelector('button[onclick^="toggleOrder"]').innerText = 
                            data.tipo ? "Crescente" : "Decrescente";
                    }
                    else if(command === 'inverter') {
                        document.querySelector('button[onclick^="toggleInvert"]').innerText = 
                            data.inverter ? "Inverter +" : "Inverter -";
                    }
                });
        }

        function toggleOrder(button) {
            sendCommand('crescente');
        }

        function toggleInvert(button) {
            sendCommand('inverter');
        }

        function sendNumber(number) {
            fetch('/numero_' + number);
        }

        function changeNumber(increment) {
            const numberInput = document.getElementById("numberInput");
            let currentNumber = parseInt(numberInput.value) || 0;
            currentNumber = Math.max(0, Math.min(50, currentNumber + increment));
            numberInput.value = currentNumber;
            sendNumber(currentNumber);
        }

        function confirmNumber() {
            fetch('/confirmar');
        }
    </script>
</head>
<body>
    <div class="nav-container">
        <a href="jornal.html" class="nav-button">Ir para Controle de Display</a>
    </div>
    
    <div class="container">
        <div class="column">
            <h1>Local</h1>
            <button onclick="sendCommand('local_pontuacao')">Pontuação</button>
            <button onclick="sendCommand('local_falta')">Falta</button>
            <button onclick="sendCommand('local_tempo')">Tempo</button>
        </div>

        <div class="column">
            <h1>Placar</h1>
            <div class="time-controls">
                <button onclick="changeNumber(-1)">-</button>
                <input type="number" id="numberInput" min="0" max="50" value="0" readonly>
                <button onclick="changeNumber(1)">+</button>
            </div>
            <button onclick="toggleOrder(this)">Crescente</button>
            <button onclick="confirmNumber()">Confirmar</button>
            <button onclick="sendCommand('set')">SET</button>
            <button onclick="sendCommand('pausar')">Pausar</button>
            <button onclick="sendCommand('resetar')">Resetar</button>
            <button onclick="toggleInvert(this)">Inverter +</button>
        </div>

        <div class="column">
            <h1>Visitante</h1>
            <button onclick="sendCommand('visitante_pontuacao')">Pontuação</button>
            <button onclick="sendCommand('visitante_falta')">Falta</button>
            <button onclick="sendCommand('visitante_tempo')">Tempo</button>
        </div>
    </div>
</body>
</html>
)rawliteral";

void handleRoot() {
    server.send(200, "text/html", index_html);
}

void handleGetStates() {
    String json = "{\"tipo\":" + String(tipo ? "true" : "false") + 
                  ",\"inverter\":" + String(inverter ? "true" : "false") + "}";
    server.send(200, "application/json", json);
}

void handleLocalPontuacao() {
    if(inverter) Serial1.println("AU_PONT_LO\n");
    else Serial1.println("DI_PONT_LO\n");
    server.send(200, "text/plain", "Local Pontuação");
}

void handleLocalFalta() {
    if(inverter) Serial1.println("AU_FAL_LO\n");
    else Serial1.println("DI_FAL_LO\n");
    server.send(200, "text/plain", "Local Falta");
}

void handleLocalTempo() {
    if(inverter) Serial1.println("AU_LOCA\n");
    else Serial1.println("DI_LOCA\n");
    server.send(200, "text/plain", "Local Tempo");
}

void handleVisitantePontuacao() {
    if(inverter) Serial2.println("AU_PONT_VI\n");
    else Serial2.println("DI_PONT_VI\n");
    server.send(200, "text/plain", "Visitante Pontuação");
}

void handleVisitanteFalta() {
    if(inverter) Serial2.println("AU_FAL_VI\n");
    else Serial2.println("DI_FAL_VI\n");
    server.send(200, "text/plain", "Visitante Falta");
}

void handleVisitanteTempo() {
    if(inverter) Serial1.println("AU_VISI\n");
    else Serial1.println("DI_VISI\n");
    server.send(200, "text/plain", "Visitante Tempo");
}

void handleCrescente() {
    tipo = !tipo;
    String json = "{\"tipo\":" + String(tipo ? "true" : "false") + "}";
    server.send(200, "application/json", json);
    Serial.println(tipo ? "Crescente" : "Decrescente");
}

void handleConfirmar() {
    String estado = tipo ? "Crescente" : "Decrescente";
    String valor = String(adjustedNumber) + "\n";
    Serial.println(valor);
    delay(300);
    Serial.println(tipo ? "Crescente\n" : "Decrescente\n");
    server.send(200, "text/plain", "Confirmado: " + estado + ", Número: " + String(adjustedNumber));
}

void handleSet() {
    if(inverter) Serial2.println("AU_SET\n");
    else Serial2.println("DI_SET\n");
    server.send(200, "text/plain", "SET");
}

void handleResetar() {
    Serial2.println("RESETAR\n");
    Serial1.println("RESETAR\n");
    Serial.println("RESETAR\n");
    server.send(200, "text/plain", "Resetar");
}

void handlePausar() {
    Serial.println("PAUSAR\n");
    server.send(200, "text/plain", "Pausar");
}

void handleInverter() {
    inverter = !inverter;
    String json = "{\"inverter\":" + String(inverter ? "true" : "false") + "}";
    server.send(200, "application/json", json);
    Serial.println(inverter ? "Inverter +" : "Inverter -");
}

void handleNumero(int numero) {
    adjustedNumber = numero;
    server.send(200, "text/plain", String(numero));
}

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600, SERIAL_8N1, 22, 23);
    Serial2.begin(9600, SERIAL_8N1, 19, 21);
    
    // Configure static IP
    if(!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
        Serial.println("STA Failed to configure");
    }

    // Connect to WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected! IP address: " + WiFi.localIP().toString());

    // Set up server routes
    server.on("/", handleRoot);
    server.on("/getStates", handleGetStates);
    server.on("/local_pontuacao", handleLocalPontuacao);
    server.on("/local_falta", handleLocalFalta);
    server.on("/local_tempo", handleLocalTempo);
    server.on("/visitante_pontuacao", handleVisitantePontuacao);
    server.on("/visitante_falta", handleVisitanteFalta);
    server.on("/visitante_tempo", handleVisitanteTempo);
    server.on("/crescente", handleCrescente);
    server.on("/confirmar", handleConfirmar);
    server.on("/set", handleSet);
    server.on("/resetar", handleResetar);
    server.on("/pausar", handlePausar);
    server.on("/inverter", handleInverter);

    // Number commands
    for(int i = 0; i <= 100; i++) {
        server.on(("/numero_" + String(i)).c_str(), [i](){ handleNumero(i); });
    }

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}