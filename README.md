![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Plataforma](https://img.shields.io/badge/Plataforma-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)

# Arquitetura de Computadores - UFC 🎓

Este repositório contém as atividades práticas desenvolvidas na disciplina de **Arquitetura de Computadores** na Universidade Federal do Ceará (UFC), com foco na simulação de componentes de hardware em baixo nível utilizando a linguagem C.

---

### 📖 Sobre o Projeto

O objetivo principal destes projetos é solidificar o entendimento teórico da arquitetura de computadores através da implementação prática. Ao construir simuladores para componentes fundamentais como a Unidade Lógica e Aritmética (ULA), é possível visualizar e depurar o fluxo de dados e as operações a nível de bits, compreendendo desafios como overflow, underflow e a representação de números inteiros e de ponto flutuante.

---

### 🚀 Projetos Desenvolvidos

✅ **Simulador de ULA para Aritmética de Inteiros (8 bits)**
* Implementação de uma ULA de 8 bits capaz de realizar as quatro operações aritméticas básicas (soma, subtração, multiplicação e divisão) para inteiros com sinal, utilizando a representação em complemento de dois.
* Inclui detecção de overflow.

✅ **Simulador de ULA para Aritmética de Ponto Flutuante (Padrão IEEE 754)**
* Simulador que implementa as quatro operações aritméticas para números de ponto flutuante de 32 bits, seguindo os algoritmos baseados no padrão IEEE 754.
* Inclui detecção de overflow e underflow de expoente.

---

### 💻 Tecnologias e Conceitos

* **Linguagem:** C
* **Conceitos Principais:** Manipulação de bits, representação de dados (complemento de dois, IEEE 754), lógica de circuitos, organização de processadores e simulação de hardware.
* **Compilador:** GCC (MinGW no Windows)

---

### ⚙️ Como Executar

Para compilar e executar os simuladores, siga os passos abaixo.

1.  **Clone o repositório:**
    ```bash
    git clone (https://github.com/NicolasHarnisch/Atividades-ARQ-UFC.git)
    ```

2.  **Navegue até a pasta de um dos projetos:**
    ```bash
    cd Atividades-ARQ-UFC/NomeDaPastaDoProjeto
    ```

3.  **Compile os arquivos C:**
    O comando abaixo junta o programa principal (`main.c`) com a lógica da ULA (`ULA.c`) e cria um executável.
    ```bash
    gcc main.c ULA.c -o simulador.exe
    ```

4.  **Execute o simulador:**
    O programa irá ler os dados de entrada do arquivo `dados.txt` ou `operandos.txt`.
    ```bash
    ./simulador.exe
    ```

---

### 📩 Contato

Caso tenha sugestões ou dúvidas, fique à vontade para abrir uma [*issue*](https://github.com/NicolasHarnisch/Atividades-ARQ-UFC/issues/new) ou entrar em contato!
