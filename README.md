# 🎮 Monster Survival - Jogo de Sobrevivência

Um jogo de sobrevivência desenvolvido em **C** utilizando a biblioteca **Raylib**. O objetivo é escapar dos fantasmas pelo maior tempo possível, controlando um pistoleiro no Velho Oeste.

## 🎯 Sobre o Projeto

Este projeto foi desenvolvido para aprimorar conhecimentos em:
- Programação em C
- Biblioteca Raylib para desenvolvimento de jogos
- Manipulação de vetores e matemática de jogos
- Gerenciamento de colisões
- Programação orientada a estruturas

## 🕹️ Como Jogar

- **Setas do teclado**: Mover o jogador
- **P**: Pausar/Despausar o jogo
- **Enter**: Reiniciar após game over

### Objetivo
Sobreviva o máximo de tempo possível evitando ser pego pelos fantasmas vermelhos que te perseguem!

## 🛠️ Tecnologias Utilizadas

- **Linguagem**: C
- **Biblioteca Gráfica**: Raylib
- **IDE**: Visual Studio Code
- **Compilador**: GCC

## 📋 Funcionalidades

### ✅ Implementadas
- [x] Movimentação fluida do jogador
- [x] Sistema de perseguição inteligente dos inimigos
- [x] Detecção de colisões entre jogador e monstros
- [x] Sistema de colisão entre monstros (evita sobreposição)
- [x] Música de fundo temática do Velho Oeste
- [x] Sistema de pause
- [x] Contador de tempo de sobrevivência
- [x] Sprites customizadas (pistoleiro, fantasmas, cenário)
- [x] Tela de game over com opção de reiniciar

### 🎨 Assets Visuais
- Sprite do pistoleiro (gunslinger.png)
- Sprites dos fantasmas (fantasma.png)
- Cenário do Velho Oeste (teladefundo.png)
- Música ambiente (OldWest.mp3)

## 🏗️ Estrutura do Código

### Principais Estruturas
```c
typedef struct Player {
    Vector2 position;
    Vector2 size;
    float speed;
    Rectangle rectangle_player;
    Color color;
} Player;

typedef struct Monster {
    Vector2 position;
    float speed;
    float radius;
    bool active;
    Color color;
} Monster;
```

### Funções Matemáticas Customizadas
- `MyVector2Subtract()`: Subtração de vetores
- `MyVector2Normalize()`: Normalização de vetores
- `MyVector2Distance()`: Cálculo de distância entre vetores

## 🚀 Como Executar

### Pré-requisitos
- Raylib instalada
- Compilador GCC
- Sistema Windows/Linux/macOS

### Compilação
```bash
gcc SurvivalSimples.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o game
```

### Execução
```bash
./game
```

## 📁 Estrutura do Projeto

```
simple-game-raylib/
├── SurvivalSimples.c          # Código principal do jogo
├── README.md                  # Documentação do projeto
└── resources/                 # Assets do jogo
    ├── fantasma.png          # Sprite dos monstros
    ├── gunslinger.png        # Sprite do jogador
    ├── OldWest.mp3          # Música de fundo
    └── teladefundo.png      # Imagem de fundo
```

## 🎮 Mecânicas do Jogo

### Sistema de Perseguição
Os fantasmas utilizam um algoritmo de perseguição baseado em vetores normalizados, movendo-se constantemente em direção ao jogador.

### Sistema de Colisão Anti-Sobreposição
Implementação de lógica para evitar que os monstros se sobreponham, criando um gameplay mais fluido e visualmente agradável.

### Controle de Bordas
O jogador é limitado às bordas da tela, impedindo que saia dos limites visuais do jogo.

## 📊 Estatísticas Técnicas

- **Linguagem**: C (100%)
- **FPS Target**: 60 FPS
- **Resolução**: 1080x720
- **Máximo de Monstros**: 4 simultâneos
- **Velocidade dos Monstros**: 1.5 unidades/frame

## 🎯 Aprendizados e Conquistas

- Implementação de matemática vetorial em jogos
- Gerenciamento de estados de jogo (playing, paused, game over)
- Otimização de colisões em tempo real
- Integração de assets audiovisuais
- Arquitetura modular de código em C

## 🔄 Possíveis Melhorias Futuras

- [ ] Sistema de power-ups
- [ ] Diferentes tipos de inimigos
- [ ] Sistema de pontuação
- [ ] Múltiplas fases
- [ ] Efeitos sonoros
- [ ] Partículas visuais

## 👨‍💻 Desenvolvedor

**Bruno** - Desenvolvedor de Software  
📍 Focado em aprimorar habilidades em programação de jogos e bibliotecas gráficas

---

*Projeto desenvolvido como parte do estudo contínuo em desenvolvimento de jogos e programação em C.*