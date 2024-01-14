#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

struct ColorStruct { //Struct de Cores do terminal
  string reset = "\x1b[0m";
  string bold = "\x1b[1m";
  string italic = "\x1b[3m";
  string underline = "\x1b[4m";
  string inverse = "\x1b[7m";
  string black = "\x1b[30m";
  string red = "\x1b[31m";
  string green = "\x1b[32m";
  string yellow = "\x1b[33m";
  string blue = "\x1b[34m";
  string magenta = "\x1b[35m";
  string cyan = "\x1b[36m";
  string white = "\x1b[37m";
  string gray = "\x1b[90m";
  string bright_red = "\x1b[91m";
  string bright_green = "\x1b[92m";
  string bright_yellow = "\x1b[93m";
  string bright_blue = "\x1b[94m";
  string bright_magenta = "\x1b[95m";
  string bright_cyan = "\x1b[96m";
  string bright_white = "\x1b[97m";
  string bg_black = "\x1b[40m";
  string bg_red = "\x1b[41m";
  string bg_green = "\x1b[42m";
  string bg_yellow = "\x1b[43m";
  string bg_blue = "\x1b[44m";
  string bg_magenta = "\x1b[45m";
  string bg_cyan = "\x1b[46m";
  string bg_white = "\x1b[47m";
  string bg_gray = "\x1b[100m";
  string bg_bright_red = "\x1b[101m";
  string bg_bright_green = "\x1b[102m";
  string bg_bright_yellow = "\x1b[103m";
  string bg_bright_blue = "\x1b[104m";
  string bg_bright_magenta = "\x1b[105m";
  string bg_bright_cyan = "\x1b[106m";
  string bg_bright_white = "\x1b[107m";
};

void ClearScreeen(){
  cout << "\033[2J\033[0;0H"; //Comando para limpar a a tela
}

void PauseScreen(){
  if (system("read 0 -p") == -1) { //Comando para pausar a tela.
  }
}

template <int tamanhocartela, typename X>
struct Bingo { // Struct genérica, com o tipo da cartela não defino e com o
               // tamanho da cartela não definido
  X Cartelas[tamanhocartela][tamanhocartela]; // Cartela "original" dos
                                              // jogadores
  X CartelasCopia[tamanhocartela]
                 [tamanhocartela]; // cartela cópia para ser usada para fazer o
                                   // preenchimento das cores dos números
  string NomeDoParticipante;       // String que vai armazenar o nome dos
                                   // participantes do bingo
  int ContadorBingo =
      0; // contador de números presentes no bingo, quando bater 25, é sinal que
         // toda a cartela foi preenchida e alguém venceu o jogo.
};

template <int Quant, int tamanhocartela, typename X> struct QuantidadeCartelas {
  Bingo<tamanhocartela, X>
      Membros[Quant]; // Essa struct acompanha a lógica da alterior, atribuindo
                      // o tipo Bingo aos Membros, que agora possui uma
                      // quantidade não definida.
};

int MultiQuinze(int k) { // Essa função automatiza a geração de numeros que deve
                         // ser atendida a cada linha.
  int cont = 0;
  for (int i = 0; i < k; i++)
    cont =
        (k == 0) ? 0 : cont += 15; // a cada laço será gerado 0, 15, 30, 45 e 60

  return cont; // retorna o número gerado a cada laço de k
}

template <int Quant, int tamanhocartela, typename X>
int RandNoRepeat(
    QuantidadeCartelas<Quant, tamanhocartela, X> Jogadores, int i, int j,
    int k) { // essa função preenche cada cartela dos jogadores com números
             // aleatórios seguindo a regra do intervalo de número de cada
             // linha, além de estarem ordenados e com cartelas não repetidas.
  srand(time(NULL) + i); // A variável de bloco i aumenta ainda mais a variedade
                         // de número aleatórios e corrigi o bug das cartelas
                         // repetidas pelo "&" na variável "Jogadores".
  int Num; // retorna um número aleatório sem repetição
  bool Repetiu;

  do {
    // esse laço do-while gera o número aletório e verifica se ele já não está
    // presente na dentro na matriz cartela do jogador...
    Repetiu = false; // A variável começa em falso para deixar o laço em loop...
    Num = MultiQuinze(k) + rand() % 15 +
          1; //...Aqui o número aleatório é gerado respeitando o intervalo de
             // cada linha

    for (int c = 0; c < j && !Repetiu; c++) {
      Repetiu = (Jogadores.Membros[i].Cartelas[k][c] ==
                 Num); //É percorrido toda a matriz da cartela do jogador a fim
                       // de verificar se p número gerado já está presente, caso
                       // sim, retorna true e todo o loop se repete até um novo
                       // número aleatório ser gerado.
    }

  } while (Repetiu); // Se true, sinal que o número randômico já foi gerado,
                     // caso false, é sinal queo número gerado é ainda não está
                     // presente na linha(é novo)

  return Num; // Assim que o número é gerado, é retornado para a novo posição da
              // matriz.
}

template <int Quant, int tamanhocartela, typename X>
bool ConferirRepeticaoDeCartela(
    QuantidadeCartelas<Quant, tamanhocartela, X>
        Jogadores) { // essa função confere se duas cartelas, por ventura, não
                     // são iguais.
  for (int i = 0; i < Quant; i++) // Verifica até p limite de jogadores
    for (int k = 0; k < tamanhocartela - 1;
         k++) // Verifica até o tamanho da cartela menos
      for (int j = 0; j < tamanhocartela - 1; j++) {
        if (Jogadores.Membros[i].Cartelas[k][j] !=
            Jogadores.Membros[i + 1]
                .Cartelas[k]
                         [j]) // Compara as cartelas de todos os jogadores para
                              // verificar se elas não são iguais, se o primeiro
                              // número for diferente, já retorna false e sai do
                              // laço da função principal, só irá retorna true
                              // se as duas cartelas iguais, ou seja, se todos
                              // os números comparados eram iguais.
          return false;
      }
  return true;
}

template <int Quant, int tamanhocartela, typename X>
void OrdenarCartela(QuantidadeCartelas<Quant, tamanhocartela, X>
                        &Jogadores) { // Função de ordenação variante do método
                                      // de inserção criada exclusivamente para
                                      // o tipo de várivel struct utilizada.
  for (int i = 0; i < Quant; i++) {
    int key, c;
    for (int k = 0; k < tamanhocartela; k++) {
      for (int j = 1; j < tamanhocartela; j++) {
        key = Jogadores.Membros[i].Cartelas[k][j];
        c = j - 1;
        while (c >= 0 && Jogadores.Membros[i].Cartelas[k][c] > key) {
          Jogadores.Membros[i].Cartelas[k][c + 1] =
              Jogadores.Membros[i].Cartelas[k][c];
          c = c - 1;
        }
        Jogadores.Membros[i].Cartelas[k][c + 1] = key;
      }
    }
  }
}

template <int Quant, int tamanhocartela, typename X>
void EspelharCartela(QuantidadeCartelas<Quant, tamanhocartela, X> &
                         Jogadores) { // Essa função preenche a matriz cartela
                                      // cópia com os valores da matriz original
  for (int i = 0; i < Quant; i++)
    for (int k = 0; k < tamanhocartela; k++)
      for (int j = 0; j < tamanhocartela; j++)
        Jogadores.Membros[i].CartelasCopia[k][j] =
            Jogadores.Membros[i].Cartelas[k][j];
}

template <int Quant, int tamanhocartela, typename X>
void PreencherCartelasSemRepetir(
    QuantidadeCartelas<Quant, tamanhocartela, X> &Jogadores,
    int QuantJogadores = Quant, int TamCartela = tamanhocartela) {
  do {
    for (int i = 0; i < QuantJogadores;
         i++) { // esse é o laço que corresponde ao jogador.
      for (int k = 0; k < TamCartela;
           k++) { // Esse laço percorre o tamanho da cartela
        for (int j = 0; j < TamCartela;
             j++) { // já esse laço percorre as linhas para aplicar toda a
                    // lógica do RandNoRepeat, pelo fato da matriz se quadrada,
                    // não havia necessidade desse laço exitir, mas o criei para
                    // conseguir aplicar as lógicas com mais clareza.
          Jogadores.Membros[i].Cartelas[k][j] = RandNoRepeat(
              Jogadores, i, j, k); // recebe o número aleatório sem repetição
        }
      }
    }
    // Nessa linha vai a função de ordenação
    OrdenarCartela(Jogadores); // Após todas as cartelas serem prenchidas, elas
                               // são ordenadas em ordem crescente
  } while (ConferirRepeticaoDeCartela(
      Jogadores)); // Confere se não há cartelas repetidas.
  EspelharCartela(
      Jogadores); // Criar as cartelas cópias para serem usadas durante o jogo.
}

void selection_sort(
    int num[],
    int tam) { // Método se inserção utilizado para deixar o vetor do globo de
               // sorteio em ordem na tela. Foi pego diretamente do slide.
  int i, j, min;
  for (i = 0; i < (tam - 1); i++) {
    min = i;
    for (j = (i + 1); j < tam; j++) {
      if (num[j] < num[min]) {
        min = j;
      }
    }
    if (i != min) {
      int swap = num[i];
      num[i] = num[min];
      num[min] = swap;
    }
  }
}

int GloboDoSorteio(
    int NumeroSorteados[],
    int QuantidadeMaxima) { // Essa função gera o número sorteado do bingo, esse
                            // número será aleatório e sem repetição dentro do
                            // intervalo de 1 à 75. Possui um lógica muito
                            // semelhante a utilizada para gerar as matrizes.
  srand(time(NULL));
  int Num;
  bool Repetiu;

  do {
    Repetiu = false;
    Num = rand() % 75 + 1;

    for (int i = 0; i < QuantidadeMaxima && !Repetiu; i++) {
      Repetiu = (NumeroSorteados[i] == Num);
    }

  } while (Repetiu);

  return Num;
}

template <int Quant, int tamanhocartela, typename X>
void NomeDosJogadores(QuantidadeCartelas<Quant, tamanhocartela, X> &Jogadores) {
  cout << "\nnome dos participantes\n"; //Essa função preenche a parte da sctruct responsável por mostrar o nome dos jogadores da partida de bingo
  for (int i = 0; i < Quant; i++) {
    cout << "\nNome do " << i + 1 << "º particpantes:\n";
    cin >> Jogadores.Membros[i].NomeDoParticipante; //NomeDoParticipante é um struct do tipo string
    ClearScreeen();
  }
}

template <int Quant, int tamanhocartela, typename X>
void ZeraCartelasSorteadas(
    QuantidadeCartelas<Quant, tamanhocartela, X> &Jogadores, int NumSorteados) { //Substitui por zero os números sorteados das cartelas originais. Isso serve para aplicar a lógica de verificação dos números nas cartelas cópias.
  for (int i = 0; i < Quant; i++)
    for (int k = 0; k < tamanhocartela; k++)
      for (int j = 0; j < tamanhocartela; j++)
        if (Jogadores.Membros[i].Cartelas[k][j] == NumSorteados) {
          Jogadores.Membros[i].Cartelas[k][j] = 0;
          Jogadores.Membros[i].ContadorBingo++; //Além disso, um contador de número sorteados e inclusivo, ele serve para verificar a houve 25 substituições por zero na cartela, o que siginifica que o jogador venceu, ou seja, fez "Bingo"
        }
}

template <int Quant, int tamanhocartela, typename X>
void ImprimirCartelasNaTela(
    QuantidadeCartelas<Quant, tamanhocartela, X> Jogadores) {
  ColorStruct Colors; //Aqui é usado a struct de cores criadas anteriormente

  for (int i = 0; i < Quant; i++) {
    cout << "\nJogador: " << Jogadores.Membros[i].NomeDoParticipante << "\n"; //Exibe o nome do jogador
    for (int k = 0; k < tamanhocartela; k++) {
      for (int j = 0; j < tamanhocartela; j++) {
        if (Jogadores.Membros[i].Cartelas[k][j] == 0) //Se o número for igual a zero na cartela original
          cout << Colors.red /*Pinta de vermelho*/ << Jogadores.Membros[i].CartelasCopia[k][j]
               << Colors.white /*Pinta de branco*/ << "\t"; //Significa que o número foi sorteado, estão o seu equivalente na cartela copia e pintado de vermelho e exibido na tela.
        else
          cout << Colors.white << Jogadores.Membros[i].CartelasCopia[k][j] //caso contrário, ele é exibido com suas cor original.
               << "\t";
      }
      cout << "\n";
    }
  }

  cout << "\n\n\n";
}

void NumeroJaSorteados(int NumeroSorteadosEspelho[], int i) { //Essa função exibe os números sorteados
  cout << "\nNúmero já sorteados: ";
  for (int j = 0; j <= i; j++) {
    cout << NumeroSorteadosEspelho[j]; 
    if (j != i) { //caso seja diferente do último número do vetor, a cada laço uma vígula é acrescentada no final após o número
      cout << ", ";
    } else {
      cout << "."; //quando atige o último número, exibe um ponto.
    }
  }
}

template <int Quant, int tamanhocartela, typename X>
bool VitoriaBingo(QuantidadeCartelas<Quant, tamanhocartela, X> Jogadores) {
  for (int i = 0; i < Quant; i++) //Essa função verifica se o contador de cada jogador bateu 25, caso verdadeiro, ele venceu o jogo, pois todos os números da sua cartela foram sorteados, caso falso , o jogo continua.
    if (Jogadores.Membros[i].ContadorBingo == 25)
      return true;

  return false;
}

template <int Quant, int tamanhocartela, typename X>
void AnunciaVencedor(QuantidadeCartelas<Quant, tamanhocartela, X> Jogadores) {
  for (int i = 0; i < Quant; i++)
    if (Jogadores.Membros[i].ContadorBingo == 25) //Seguindo a lógica da função de anuncia vencedor, ele exibe uma mensagem com o nome do jogador o parabenizando.
      cout << "\nO Vencendor do jogo é "
           << Jogadores.Membros[i].NomeDoParticipante << ". Meus Parabéns!!!\n";
}

template <int Quant, int tamanhocartela, typename X>
void JogoDoBingo(QuantidadeCartelas<Quant, tamanhocartela, X> Jogadores) {
  int NumMax = tamanhocartela * 15; //Quantidade máxima de números sorteados.
  int *NumeroSorteados = new int[NumMax]; //Ponteiro de vetor para exibir os números sorteados. Aloca um espaço de memória
  NomeDosJogadores(Jogadores); //Chama a função para preencher o nome dos jogadores.
  PreencherCartelasSemRepetir(Jogadores); //Preenche as Cartelas conforme as regras
  ImprimirCartelasNaTela(Jogadores); //Imprimi as cartelas na tela para os jogadores as verem.
  PauseScreen();
  ClearScreeen();

    for (int i = 0; i < NumMax && VitoriaBingo(Jogadores) == false; i++) {
      NumeroSorteados[i] = GloboDoSorteio(NumeroSorteados, i); //Sorteia um número e o preenche no vetor de números sorteados
      ZeraCartelasSorteadas(Jogadores, GloboDoSorteio(NumeroSorteados, i)); //Logo em seguida, verifica se ele está presente na cartela original
      cout << "\n Número Sorteado: " << NumeroSorteados[i] << "\n"; //Exibe o número na tela.
      cout << "\n";
      ImprimirCartelasNaTela(Jogadores); //Imprime as cartelas com os números sorteados.
      cout << "\n";
      selection_sort(NumeroSorteados, i + 1); //Organiza os números sorteados para serem exibidos em ordem crescente.
      NumeroJaSorteados(NumeroSorteados, i); //Exibe os números sorteados.
      cout << "\n";
      PauseScreen();
      ClearScreeen();
    }

  AnunciaVencedor(Jogadores); //Anuncia o vencedor se fizer bingo
  PauseScreen();
  ClearScreeen();
  delete[] NumeroSorteados; //Libera o espaço de memória
}

void Creditos() {
  cout << "\nUniversidade do Vale do Itajaí\n"
       << "\nCurso: Engenharia de Computação\n"
       << "\nAcadêmico/Desenvolvedor: Henry José\n"
       << "\nJaneiro de 2024\n"
       << "\nProjeto de Férias\n";
}

template <int Quant, int tamanhocartela, typename X>
void MenuDoJogoDoBingo(
    QuantidadeCartelas<Quant, tamanhocartela, X> &Jogadores) {
  int Select = 0;
  do {
    cout << "    ##   #####    #####    #####            #####     #####            ######    ######  ##   ##   #####    #####\n";
    cout << "    ##  ### ###  ##   ##  ### ###            ## ##   ### ###            ##  ##     ##    ###  ##  ##   ##  ### ###\n";
    cout << "    ##  ##   ##  ##       ##   ##            ##  ##  ##   ##            ##  ##     ##    #### ##  ##       ##   ##\n";
    cout << "     ##  ##   ##  ## ####  ##   ##            ##  ##  ##   ##            #####      ##    #######  ## ####  ##   ##\n";
    cout << "##   ##  ##   ##  ##   ##  ##   ##            ##  ##  ##   ##            ##  ##     ##    ## ####  ##   ##  ##   ##\n";
    cout << "## ##   ### ###  ##   ##  ### ###            ## ##   ### ###            ##  ##     ##    ##  ###  ##   ##  ### ###\n";
    cout << " ###     #####    #####    #####            #####     #####            ######    ######  ##   ##   #####    #####\n";
    cout << "\n\n\n";
    cout << "\nSelecione uma opção:\n"
         << "\n\n"
         << "\n1-Novo jogo\n"
         << "\n2-Créditos\n"
         << "\n3-Sair\n";
    cin >> Select;
    ClearScreeen();
    switch (Select) {
    case 1: // Novo Jogo
      JogoDoBingo(Jogadores);
      break;
    case 2: // Créditos
      Creditos();
      break;
    case 3: // Sair do jogo
      Select = 3;
      break;
    default: // Caso não seja nenhuma das opções listadas.
      cout << "\nNenhuma opção correspodente\n";
    }
  } while (Select != 3);
}