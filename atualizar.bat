@echo off
title Atualizar GitHub
color 0A

echo =======================================================
echo    Sincronizando o Placar Eletronico com o GitHub...
echo =======================================================
echo.

:: O comando "add ." adiciona todos os arquivos alterados
git add .

:: O comando "commit" salva as mudancas
git commit -m "Atualizacao de arquivos e layout via script - %date%"

:: O comando "pull" baixa as alteracoes feitas no site do GitHub
git pull origin main --rebase

:: O comando "push" envia para a nuvem
git push origin main

echo.
echo =======================================================
echo    Tudo pronto! Os arquivos estao no GitHub.
echo =======================================================
pause