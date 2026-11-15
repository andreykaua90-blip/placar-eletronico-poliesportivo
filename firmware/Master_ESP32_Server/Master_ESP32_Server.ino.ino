#include <WiFi.h>
#include <WebServer.h>

boolean tipo = true;
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
        :root {
            --bg-body: #121212;
            --bg-card: #1e1e1e;
            --text-main: #ffffff;
            --text-muted: #b0b0b0;
            --green-neon: #00e676;
            --green-primary: #2e7d32;
            --green-hover: #1b5e20;
            --gray-button: #424242;
            --gray-hover: #616161;
            --gray-border: #555555;
        }

        body {
            font-family: 'Segoe UI', Roboto, Helvetica, Arial, sans-serif;
            margin: 0;
            padding: 20px;
            background-color: var(--bg-body);
            color: var(--text-main);
            min-height: 100vh;
            box-sizing: border-box;
        }

        .nav-container {
            display: flex;
            justify-content: center;
            margin-bottom: 30px;
        }

        .nav-button {
            background-color: var(--gray-button);
            color: var(--text-main);
            padding: 12px 30px;
            border: 1px solid var(--gray-border);
            border-radius: 30px;
            text-decoration: none;
            font-weight: 600;
            font-size: 0.85rem;
            transition: all 0.3s ease;
            text-transform: uppercase;
            letter-spacing: 1px;
        }

        .nav-button:hover {
            background-color: var(--gray-hover);
            border-color: var(--green-neon);
            color: var(--green-neon);
            box-shadow: 0 0 10px rgba(0, 230, 118, 0.2);
        }

        .container {
            display: grid;
            grid-template-columns: 1fr 1.2fr 1fr;
            gap: 25px;
            width: 100%;
            max-width: 1200px;
            margin: 0 auto;
        }

        .column {
            background-color: var(--bg-card);
            border-radius: 16px;
            padding: 25px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.5);
            display: flex;
            flex-direction: column;
            gap: 15px;
            border: 1px solid #333;
        }

        .column.center-panel {
            background: linear-gradient(180deg, var(--bg-card) 0%, #161616 100%);
            border: 2px solid var(--green-primary);
        }

        h1 {
            font-size: 1.1rem;
            margin: 0 0 10px 0;
            text-align: center;
            text-transform: uppercase;
            letter-spacing: 2px;
            color: var(--green-neon);
            opacity: 1;
            padding-bottom: 15px;
            border-bottom: 1px solid var(--gray-border);
            text-shadow: 0 0 5px rgba(0, 230, 118, 0.2);
        }

        button {
            border: none;
            border-radius: 8px;
            padding: 12px;
            cursor: pointer;
            font-size: 1rem;
            font-weight: bold;
            color: white;
            transition: all 0.2s;
            width: 100%;
        }

        button:active {
            transform: scale(0.98);
        }

        .btn-action { 
            background-color: var(--green-primary); 
            color: #fff;
            box-shadow: 0 4px 6px rgba(0,0,0,0.2);
        }
        .btn-action:hover { 
            background-color: var(--green-hover);
            box-shadow: 0 0 15px rgba(46, 125, 50, 0.6);
        }

        .btn-neutral { 
            background-color: var(--gray-button); 
            color: #fff;
            border: 1px solid var(--gray-border);
        }
        .btn-neutral:hover { 
            background-color: var(--gray-hover); 
            border-color: #fff;
        }
        
        .btn-outline {
            background-color: #2a2a2a;
            border: 2px solid var(--gray-border);
            color: #fff;
        }
        .btn-outline:hover {
            border-color: var(--green-neon);
            color: var(--green-neon);
            background-color: #333;
        }

        .control-row {
            display: flex;
            align-items: center;
            justify-content: space-between;
            background-color: rgba(255, 255, 255, 0.05);
            padding: 8px;
            border-radius: 10px;
            border: 1px solid #333;
        }

        .control-row span {
            font-weight: 700;
            text-transform: uppercase;
            font-size: 0.8rem;
            color: #ddd;
            flex-grow: 1;
            text-align: center;
        }

        .control-row button, 
        .std-btn-size {
            width: 45px !important;
            height: 45px !important;
            min-width: 45px !important;
            font-size: 1.4rem !important;
            display: flex;
            align-items: center;
            justify-content: center;
            padding: 0;
            border-radius: 8px;
        }

        .section-label {
            font-size: 0.75rem;
            color: #bbb;
            text-transform: uppercase;
            letter-spacing: 1px;
            margin-top: 15px;
            margin-bottom: 5px;
            display: block;
            font-weight: bold;
        }

        .timer-display {
            display: flex;
            align-items: center;
            justify-content: space-between;
            background-color: #000;
            border-radius: 12px;
            padding: 25px 30px;
            margin-bottom: 15px;
            border: 2px solid var(--gray-border);
            width: 100%;
            box-sizing: border-box;
        }

        #numberInput {
            background: transparent;
            color: var(--green-neon);
            font-family: 'Courier New', Courier, monospace;
            font-size: 3.5rem;
            font-weight: bold;
            border: 2px solid transparent;
            border-radius: 8px;
            text-align: center;
            width: 140px;
            text-shadow: 0 0 15px rgba(0, 230, 118, 0.4);
            outline: none;
            transition: border-color 0.3s;
            -moz-appearance: textfield;
        }
        #numberInput::-webkit-outer-spin-button,
        #numberInput::-webkit-inner-spin-button {
            -webkit-appearance: none;
            margin: 0;
        }

        #numberInput:focus {
            border-color: var(--green-neon);
            background-color: rgba(46, 125, 50, 0.1);
        }

        .btn-confirm {
            background-color: var(--green-primary);
            font-size: 1.1rem;
            text-transform: uppercase;
            letter-spacing: 1px;
            padding: 18px;
            font-weight: 800;
            border: 1px solid #4caf50;
            box-shadow: 0 4px 10px rgba(0,0,0,0.3);
        }
        .btn-confirm:hover {
            background-color: var(--green-neon);
            color: #000;
            box-shadow: 0 0 20px rgba(0, 230, 118, 0.5);
        }

        .playback-controls {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 15px;
            margin-top: 15px;
        }

        @media (max-width: 768px) {
            .container { grid-template-columns: 1fr; }
            #numberInput { font-size: 3rem; }
        }
    </style>
    <script>
        function loadInitialStates() {
            fetch('/getStates')
                .then(response => response.json())
                .then(data => {
                    document.querySelector('button[onclick^="toggleOrder"]').innerText = 
                        data.tipo ? "Crescente" : "Decrescente";
                })
                .catch(err => console.log("Erro ao carregar estados:", err));
        }
        window.onload = loadInitialStates;
        
        function sendCommand(command) {
            fetch('/' + command)
                .then(response => {
                    if(command === 'crescente') {
                        return response.json();
                    }
                    return response.text();
                })
                .then(data => {
                    if(command === 'crescente') {
                        document.querySelector('button[onclick^="toggleOrder"]').innerText = 
                            data.tipo ? "Crescente" : "Decrescente";
                    }
                })
                .catch(err => console.log("Erro ao enviar comando:", err));
        }

        function toggleOrder(button) {
            sendCommand('crescente');
        }

        function sendNumber(number) {
            number = parseInt(number);
            fetch('/numero_' + number);
        }

        function changeNumber(increment) {
            const numberInput = document.getElementById("numberInput");
            let currentNumber = parseInt(numberInput.value) || 0;
            currentNumber = Math.max(0, Math.min(50, currentNumber + increment));
            numberInput.value = currentNumber;
            sendNumber(currentNumber);
        }

        function manualInput(input) {
            let val = parseInt(input.value);
            
            if (isNaN(val)) val = 0;
            if (val > 50) val = 50; 
            if (val < 0) val = 0;

            if (input.value != val) {
                input.value = val;
            }
            
            sendNumber(val);
        }

        function confirmNumber() {
            fetch('/confirmar');
        }
    </script>
</head>
<body>
    <div class="nav-container">
        <a href="Jornal.html" class="nav-button">← Controle de Display</a>
    </div>
    
    <div class="container">
        <div class="column">
            <h1>Time A</h1>
            
            <div class="control-row">
                <button class="btn-neutral" onclick="sendCommand('local_pontuacao_menos')">-</button>
                <span>Pontuação</span>
                <button class="btn-action" onclick="sendCommand('local_pontuacao')">+</button>
            </div>

            <div class="control-row">
                <button class="btn-neutral" onclick="sendCommand('local_falta_menos')">-</button>
                <span>Faltas</span>
                <button class="btn-action" onclick="sendCommand('local_falta')">+</button>
            </div>

            <div class="control-row">
                <button class="btn-neutral" onclick="sendCommand('local_tempo_menos')">-</button>
                <span>Tempo Técnico</span>
                <button class="btn-action" onclick="sendCommand('local_tempo')">+</button>
            </div>
        </div>

        <div class="column center-panel">
            <h1>Controle Central</h1>
            
            <span class="section-label">Ajuste de Tempo (Minutos)</span>
            
            <div class="timer-display">
                <button class="btn-neutral std-btn-size" onclick="changeNumber(-1)">-</button>
                
                <input type="number" id="numberInput" min="0" max="50" value="0" oninput="manualInput(this)">
                
                <button class="btn-neutral std-btn-size" onclick="changeNumber(1)">+</button>
            </div>

            <button class="btn-outline" onclick="toggleOrder(this)" style="margin-bottom: 10px;">Crescente</button>

            <button class="btn-confirm" onclick="confirmNumber()">ENVIAR TEMPO PARA TELA</button>

            <div style="border-top: 1px solid #444; margin: 25px 0; width: 100%;"></div>

            <span class="section-label">Controle da Partida</span>
            
            <div class="control-row" style="background-color: transparent; border: 1px solid #555;">
                <button class="btn-neutral" onclick="sendCommand('set_menos')">-</button>
                <span>SETS</span>
                <button class="btn-action" onclick="sendCommand('set')">+</button>
            </div>

            <div class="playback-controls">
                <button class="btn-outline" onclick="sendCommand('pausar')">⏯ Play/Pausar</button>
                <button class="btn-outline" onclick="sendCommand('resetar')">↺ Resetar</button>
            </div>
        </div>

        <div class="column">
            <h1>Time B</h1>
            
            <div class="control-row">
                <button class="btn-neutral" onclick="sendCommand('visitante_pontuacao_menos')">-</button>
                <span>Pontuação</span>
                <button class="btn-action" onclick="sendCommand('visitante_pontuacao')">+</button>
            </div>

            <div class="control-row">
                <button class="btn-neutral" onclick="sendCommand('visitante_falta_menos')">-</button>
                <span>Faltas</span>
                <button class="btn-action" onclick="sendCommand('visitante_falta')">+</button>
            </div>

            <div class="control-row">
                <button class="btn-neutral" onclick="sendCommand('visitante_tempo_menos')">-</button>
                <span>Tempo Técnico</span>
                <button class="btn-action" onclick="sendCommand('visitante_tempo')">+</button>
            </div>
        </div>
    </div>
</body>
</html>
)rawliteral";

void handleRoot() {
    server.send(200, "text/html", index_html);
}

void handleGetStates() {
    String json = "{\"tipo\":" + String(tipo ? "true" : "false") + "}";
    server.send(200, "application/json", json);
}

void handleLocalPontuacao() {
    Serial1.println("AU_PONT_LO\n");
    server.send(200, "text/plain", "Local Pontuação +");
}
void handleLocalPontuacaoMenos() {
    Serial1.println("DI_PONT_LO\n");
    server.send(200, "text/plain", "Local Pontuação -");
}

void handleLocalFalta() {
    Serial1.println("AU_FAL_LO\n");
    server.send(200, "text/plain", "Local Falta +");
}
void handleLocalFaltaMenos() {
    Serial1.println("DI_FAL_LO\n");
    server.send(200, "text/plain", "Local Falta -");
}

void handleLocalTempo() {
    Serial1.println("AU_LOCA\n");
    server.send(200, "text/plain", "Local Tempo +");
}
void handleLocalTempoMenos() {
    Serial1.println("DI_LOCA\n");
    server.send(200, "text/plain", "Local Tempo -");
}

void handleVisitantePontuacao() {
    Serial2.println("AU_PONT_VI\n");
    server.send(200, "text/plain", "Visitante Pontuação +");
}
void handleVisitantePontuacaoMenos() {
    Serial2.println("DI_PONT_VI\n");
    server.send(200, "text/plain", "Visitante Pontuação -");
}

void handleVisitanteFalta() {
    Serial2.println("AU_FAL_VI\n");
    server.send(200, "text/plain", "Visitante Falta +");
}
void handleVisitanteFaltaMenos() {
    Serial2.println("DI_FAL_VI\n");
    server.send(200, "text/plain", "Visitante Falta -");
}

void handleVisitanteTempo() {
    Serial1.println("AU_VISI\n");
    server.send(200, "text/plain", "Visitante Tempo +");
}
void handleVisitanteTempoMenos() {
    Serial1.println("DI_VISI\n");
    server.send(200, "text/plain", "Visitante Tempo -");
}

void handleSet() {
    Serial2.println("AU_SET\n");
    server.send(200, "text/plain", "SET +");
}
void handleSetMenos() {
    Serial2.println("DI_SET\n");
    server.send(200, "text/plain", "SET -");
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

void handleNumero(int numero) {
    adjustedNumber = numero;
    server.send(200, "text/plain", String(numero));
}

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600, SERIAL_8N1, 22, 23);
    Serial2.begin(9600, SERIAL_8N1, 19, 21);
    
    // Static IP configuration
    if(!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
        Serial.println("STA Failed to configure");
    }

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected! IP address: " + WiFi.localIP().toString());

    server.on("/", handleRoot);
    server.on("/getStates", handleGetStates);
    server.on("/local_pontuacao", handleLocalPontuacao);
    server.on("/local_pontuacao_menos", handleLocalPontuacaoMenos);
    server.on("/local_falta", handleLocalFalta);
    server.on("/local_falta_menos", handleLocalFaltaMenos);
    server.on("/local_tempo", handleLocalTempo);
    server.on("/local_tempo_menos", handleLocalTempoMenos);
    server.on("/visitante_pontuacao", handleVisitantePontuacao);
    server.on("/visitante_pontuacao_menos", handleVisitantePontuacaoMenos);
    server.on("/visitante_falta", handleVisitanteFalta);
    server.on("/visitante_falta_menos", handleVisitanteFaltaMenos);
    server.on("/visitante_tempo", handleVisitanteTempo);
    server.on("/visitante_tempo_menos", handleVisitanteTempoMenos);
    server.on("/crescente", handleCrescente);
    server.on("/confirmar", handleConfirmar);
    server.on("/set", handleSet);
    server.on("/set_menos", handleSetMenos);
    server.on("/resetar", handleResetar);
    server.on("/pausar", handlePausar);

    for(int i = 0; i <= 100; i++) {
        server.on(("/numero_" + String(i)).c_str(), [i](){ handleNumero(i); });
    }

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}