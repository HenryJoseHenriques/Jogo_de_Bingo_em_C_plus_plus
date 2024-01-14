/*
O sorteio dos valores de cada cartela (cada cartela possui 25 números, sendo que
cada linha possui 5 números sorteados) segue o seguinte padrão:
• Primeira linha – sorteados valores de 1 a 15; OK
• Segunda linha – sorteados valores de 16 a 30; OK
• Terceira linha – sorteados valores de 31 a 45; OK
• Quarta linha – sorteados valores de 46 a 60; e OK
• Quinta linha – sorteados valores de 61 a 75. OK
Deve-se gerar 5 cartelas randomicamente, que sigam as regras abaixo:
• A cada nova execução deverá haver um novo sorteio com valores diferenciados;
OK • Cada cartela terá um número de identificação; • Não pode haver valores
repetidos nas linhas; • Não pode haver cartelas repetidas; e • Exibir na tela as
cartelas geradas durante toda a execução. • Marcar os valores já sorteados nas
cartelas • As linhas devem estar em ordem crescente
*/

#include "FuncoesBingo.h"
#include <cstdlib>
#include <iostream>
#include <time.h>

int main() {
  QuantidadeCartelas<3, 5, int> Jogadores;
  MenuDoJogoDoBingo(Jogadores);
}