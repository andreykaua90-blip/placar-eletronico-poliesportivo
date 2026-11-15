@echo off
title Atualizar GitHub
color 0A

echo =======================================================
echo    Sincronizando o Placar Eletronico com o GitHub...
echo =======================================================
echo.

:: O comando "add ." adiciona todos os arquivos alterados (index, códigos, imagens)
git add .

:: O comando "commit" salva as mudanças. (O "%date%" insere a data automática)
git commit -m "Atualizacao de arquivos e layout via script - %date%"

:: O comando "push" envia para a nuvem
git push origin main

echo.
echo =======================================================
echo    Tudo pronto! Os arquivos estao no GitHub.
echo =======================================================
pause