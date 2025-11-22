# jopo.py menu de salvamento, carregamento...
jogo

# 🟡 Módulo do Menu, Pilha, Salvamento e Carregamento

Este módulo implementa o **menu principal**, o sistema de **salvamento/carregamento** do jogo e a estrutura de **pilha de ações** utilizadas no projeto Pac-Man desenvolvido em grupo.

Ele funciona de forma independente, mas se integra ao restante do jogo através da estrutura `GAME` definida pela Pessoa 1.

---

## 📌 Responsabilidades 



- 📁 `menu.c` — implementação completa do menu  
- 📁 `menu.h` — interface pública do módulo  
- 📦 Sistema de salvamento binário  
- 📦 Sistema de carregamento binário  
- 🧱 Implementação da pilha de ações  
- ⌨ Menu textual interativo via `getchar()`  
- 🔁 Comunicação com o loop principal através das flags:  
  - `g->resetar`  
  - `g->jogoPausado`

---

## 📁 Estrutura dos Arquivos

