#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

template <int tamanhocartela, typename X>
struct Bingo { // Struct genérica, com o tipo da cartela não defino e com o
               // tamanho da cartela não definido
  X Cartelas[tamanhocartela][tamanhocartela]; //Cartela "original" dos jogadores
  X CartelasCopia[tamanhocartela][tamanhocartela]; //cartela cópia para ser usada para fazer o preenchimento das cores dos números
  string NomeDoParticipante; //String que vai armazenar o nome dos participantes do bingo
  int ContadorBingo = 0; //contador de números presentes no bingo, quando bater 25, é sinal que toda a cartela foi preenchida e alguém venceu o jogo.
};

template <int *Quant, int tamanhocartela, typename X> struct QuantidadeCartelas {
  Bingo<tamanhocartela, X>
      Membros[*Quant]; // Essa struct acompanha a lógica da alterior, atribuindo
                      // o tipo Bingo aos Membros, que agora possui uma
                      // quantidade não definida.
};

int MultiQuinze(int k) { // Essa função automatiza a geração de numeros que deve ser atendida a cada linha.
  int cont = 0;
  for (int i = 0; i < k; i++)
    cont =
        (k == 0) ? 0 : cont += 15; // a cada laço será gerado 0, 15, 30, 45 e 60

  return cont; //retorna o número gerado a cada laço de k
}

template <int *Quant, int tamanhocartela, typename X>
int RandNoRepeat(QuantidadeCartelas<*Quant, tamanhocartela, X> Jogadores, int i,
                 int j, int k) { //essa função preenche cada cartela dos jogadores com números aleatórios seguindo a regra do intervalo de número de cada linha, além de estarem ordenados e com cartelas não repetidas. 
  srand(time(NULL) + i); // A variável de bloco i aumenta ainda mais a variedade  de número aleatórios e corrigi o bug das cartelas repetidas pelo "&" na variável "Jogadores". 
  int Num; //retorna um número aleatório sem repetição
  bool Repetiu;

  do {
    //esse laço do-while gera o número aletório e verifica se ele já não está presente na dentro na matriz cartela do jogador...
    Repetiu = false; //A variável começa em falso para deixar o laço em loop...
    Num = MultiQuinze(k) + rand() % 15 + 1; //...Aqui o número aleatório é gerado respeitando o intervalo de cada linha

    for (int c = 0; c < j && !Repetiu; c++) {
      Repetiu = (Jogadores.Membros[i].Cartelas[k][c] == Num); //É percorrido toda a matriz da cartela do jogador a fim de verificar se p número gerado já está presente, caso sim, retorna true e todo o loop se repete até um novo número aleatório ser gerado.
    }

  } while (Repetiu); //Se true, sinal que o número randômico já foi gerado, caso false, é sinal queo número gerado é ainda não está presente na linha(é novo)

  return Num; //Assim que o número é gerado, é retornado para a novo posição da matriz.
}

template <int *Quant, int tamanhocartela, typename X>
bool ConferirRepeticaoDeCartela(
    QuantidadeCartelas<*Quant, tamanhocartela, X> Jogadores) { //essa função confere se duas cartelas, por ventura, não são iguais.
  for (int i = 0; i < *Quant; i++) //Verifica até p limite de jogadores
    for (int k = 0; k < tamanhocartela - 1; k++) //Verifica até o tamanho da cartela menos
      for (int j = 0; j < tamanhocartela - 1; j++) {
        if (Jogadores.Membros[i].Cartelas[k][j] !=
            Jogadores.Membros[i + 1].Cartelas[k][j]) // Compara as cartelas de todos os jogadores para verificar se elas não são iguais, se o primeiro número for diferente, já retorna false e sai do laço da função principal, só irá retorna true se as duas cartelas iguais, ou seja, se todos os números comparados eram iguais.
          return false;
      }
  return true;
}

template <int *Quant, int tamanhocartela, typename X>
void OrdenarCartela(QuantidadeCartelas<*Quant, tamanhocartela, X> &Jogadores) {// Função de ordenação variante do método de inserção criada exclusivamente para o tipo de várivel struct utilizada.
  for (int i = 0; i < *Quant; i++) {
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

template <int *Quant, int tamanhocartela, typename X>
void EspelharCartela(QuantidadeCartelas<*Quant, tamanhocartela, X> &Jogadores) { //Essa função preenche a matriz cartela cópia com os valores da matriz original
  for (int i = 0; i < *Quant; i++) 
    for (int k = 0; k < tamanhocartela; k++) 
      for (int j = 0; j < tamanhocartela; j++) 
        Jogadores.Membros[i].CartelasCopia[k][j] =
            Jogadores.Membros[i].Cartelas[k][j];
}

template <int *Quant, int tamanhocartela, typename X>
void PreencherCartelasSemRepetir(
    QuantidadeCartelas<Quant, tamanhocartela, X> &Jogadores,
    int QuantJogadores = *Quant, int TamCartela = tamanhocartela) { //Utilização de parâmetros default para otimizar o código e evitar redundâncias
  do {
    for (int i = 0; i < QuantJogadores;
         i++) { // esse é o laço que corresponde ao jogador.
      for (int k = 0; k < TamCartela;
           k++) { // Esse laço percorre o tamanho da cartela
        for (int j = 0; j < TamCartela;
             j++) { // já esse laço percorre as linhas para aplicar toda a lógica do RandNoRepeat, pelo fato da matriz se quadrada, não havia necessidade desse laço exitir, mas o criei para conseguir aplicar as lógicas com mais clareza.
          Jogadores.Membros[i].Cartelas[k][j] =
              RandNoRepeat(Jogadores, i, j, k); //recebe o número aleatório sem repetição
        }
      }
    }
    // Nessa linha vai a função de ordenação
    OrdenarCartela(Jogadores);// Após todas as cartelas serem prenchidas, elas são ordenadas em ordem crescente
  } while (ConferirRepeticaoDeCartela(Jogadores)); //Confere se não há cartelas repetidas.
  EspelharCartela(Jogadores); //Criar as cartelas cópias para serem usadas durante o jogo.
}

void selection_sort(int num[], int tam) { //Método se inserção utilizado para deixar o vetor do globo de sorteio em ordem na tela. Foio pega diretamente do slide.
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

int GloboDoSorteio(int NumeroSorteados[], int QuantidadeMaxima) { //Essa função gera o número sorteado do bingo, esse número será aleatório e sem repetição dentro do intervalo de 1 à 75. Possui um lógica muito semelhante a utilizada para gerar as matrizes.
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

template <int *Quant, int tamanhocartela, typename X>
void JogoDoBingo(QuantidadeCartelas<*Quant, tamanhocartela, X> Jogadores) {
  int NumMax = tamanhocartela * 15;
  int *NumeroSorteados = new int[NumMax];
  for(int i = 0; i < NumMax; i++)
  GloboDoSorteio(NumeroSorteados, i); 
  
  delete[] NumeroSorteados;
}

void MenuDoJogoDoBingo(int Select){
  switch(Select){
    case 1: //Novo Jogo
      
    break;
    case 2: //Créditos
    break;
    case 3: //Sair do jogo
    default: //Caso não seja nenhuma das opções listadas.
    cout << "\nNenhuma opção correspodente\n";
  }
}