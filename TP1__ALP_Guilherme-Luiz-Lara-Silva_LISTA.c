/* Este c�digo tem o intuito de implementar um jogador do Jogo da Velha conforme
   especifica��o do Trabalho Pr�tico 1 de ALP.

   Para executar um teste, compile este c�digo 2 vezes, gerando dois arquivos de
   sa�da distintos (exemplo: t1.exe e t2.exe). Depois disso, abra 2 terminais
   (linhas de comando). No 1� terminal, execute o jogador 1 usando o seguinte
   comando:

   t1.exe teste.txt 1

   Em seguida, execute o jogador 2 no outro terminal aberto, indicando o mesmo
   arquivo texto, com o seguinte comando:

   t2.exe teste.txt 2

*/

#define TAMANHOBUFFER 50
#define WIN32_LEAN_AND_MEAN // Usado na implementa��o da fun��o gettimeofday para gera��o aleat�ria de jogadas
#define MaxTam 9
#define Inicio 0

#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h> // Usado na implementa��o da fun��o gettimeofday para gera��o aleat�ria de jogadas

// Usado na implementa��o da fun��o gettimeofday para gera��o aleat�ria de jogadas
/*typedef struct timeval {
    long tv_sec;
    long tv_usec;
} timeval;*/

// Implementa fun��o equivalente � "gettimeofday" do Linux, para gera��o aleat�ria de jogadas
/*int gettimeofday(struct timeval * tp, struct timeval * tzp){
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}*/

/* Estrutura que guarda as informa��es de uma jogada: n� do jogador, linha e coluna selecionadas */
typedef struct Jogada_Lista{
  int jogador;
  int linha;
  int coluna;
  int Head;
  int Tail;
} Jogada;
//=--------------------------------------

void ListaVazia(Jogada Lista[9]){
  	Lista[0].Head = Inicio;
  	Lista[0].Tail = Lista[0].Head;
}  /* FLVazia */

void LLista(int i, Jogada Lista[i]){
  Lista[i].Tail= Lista[i++].Tail;
}
//--------------------------------
//FUN��O PARA PESQUISAR A JOGADA
/*void PesquisaJogada(Jogada Lista[9], int numeroJogadas){
    int Jog_Esc, z, i;
    printf("Digite o numero da jogada :");
    scanf("%d", &Jog_Esc);
    for(i = 0; i < numeroJogadas; i++){
        for(z = 0; z <= Jog_Esc;z++){
            }
        }
    printf("A jogada escolhida foi : &d",Lista[z]);
}


//----------------------------------------

/* Fun��o que escolhe uma jogada e retorna a jogada escolhida */
Jogada escolheJogada(int (*tabuleiro)[3][3], int jogador){
  Jogada disponiveis[9];
  int num_disponiveis = 0, i, j, escolhida;

  // Percorre o tabuleiro anotando as posi��es vazias (dispon�veis)
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      if((*tabuleiro)[i][j] == 0){
        disponiveis[num_disponiveis].linha = i;
        disponiveis[num_disponiveis++].coluna = j;
      }
    }
  }

  // Encerra se n�o houver jogada para escolher (checar se o jogo acabou antes de escolher jogada)
  if(num_disponiveis == 0){
    printf("\n** Erro permanente: nao ha jogada para escolher! Cheque se o jogo acabou antes de mandar escolher uma nova jogada! **\n");
    exit(-1);
  }

  // Escolhe a primeira  jogada dispon�vel entre as jogadas dispon�veis
  escolhida = (int) (( (double) rand() / (RAND_MAX + 1) ) * 0);

  // Anota o n� do jogador na jogada escolhida
  disponiveis[escolhida].jogador = jogador;

  // Anota a jogada escolhida no tabuleiro
  (*tabuleiro)[disponiveis[escolhida].linha][disponiveis[escolhida].coluna] = jogador;

  return(disponiveis[escolhida]);
}

/* Retorna 1 se o jogo tiver acabado ou retorna 0, caso contrario. */
int jogoAcabou(int tabuleiro[3][3]){
  int i,j, contador = 0;

  // Verifica se h� algum alinhamento no tabuleiro
  // Alinhamento em uma linha
  for (i = 0; i < 3; i++){
    if( (tabuleiro[i][0] == 1 || tabuleiro[i][0] == 2) &&
        (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]) ) {
      printf("\nJogador %d venceu.\n", tabuleiro[i][0]);
      return(1);
    }
  }

  // Alinhamento em uma coluna
  for (i = 0; i < 3; i++){
    if( (tabuleiro[0][i] == 1 || tabuleiro[0][i] == 2) &&
        (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i]) ){
      printf("\nJogador %d venceu.\n", tabuleiro[0][i]);
      return(1);
    }
  }

  // Alinhamento nas diagonais
  if( ( (tabuleiro[0][0] == 1 || tabuleiro[0][0] == 2) &&
        (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) ) ||
      ( (tabuleiro[2][0] == 1 || tabuleiro[2][0] == 2) &&
        (tabuleiro[2][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[0][2]) ) ){
    printf("\nJogador %d venceu.\n", tabuleiro[1][1]);
    return(1);
  }

  // Verifica se o tabuleiro est� cheio (empate)
  for(i = 0; i < 3  && contador == 0; i++){
    for(j = 0; j < 3 && contador == 0; j++){
      if(tabuleiro[i][j] == 0){
        contador++;
      }
    }
  }
  if(contador == 0){
    printf("\nEmpate.\n");
    return(1);
  }

  return(0);
}

/* Imprime na tela o estado atual do tabuleiro de jogo. */
void imprimeTabuleiro(int tabuleiro[3][3]){
  int i,j;
  printf("\nTabuleiro:\n");
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      if(tabuleiro[i][j] == 0){
        printf("-");
      }
      else{
        printf("%d",tabuleiro[i][j]);
      }
      if(j == 2){
        printf("\n");
      }
      else{
        printf("|");
      }
    }
  }
}


/* Escreve, no arquivo texto, os dados das jogadas j� realizadas.
   Fecha o arquivo para que o advers�rio possa ler a �ltima jogada anotada.
   Encerra a execu��o caso n�o consiga escrever. */
void escreveJogadas(HANDLE* arq, char* nome_arq, int jogador, int numeroJogadas, Jogada jogadas[9]){

  int i;                                  // vari�vel de itera��o
  int codigoErro = 0;                     // indica eventual erro na escrita
  unsigned long int numBytesEscrever = 0; // n�mero de bytes a escrever no arquivo
  unsigned long int numBytesEscritos = 0; // n�mero de bytes escritos no arquivo
  char saida[50] = {'\0'};				  // string a ser escrita no arquivo
    ListaVazia(jogadas);
	LLista(i, jogadas);

  // Monta a string completa a ser escrita no arquivo (vide padroniza��o do formato do arquivo na especifica��o do TP)
  saida[0] = jogador + '0';                    // converte d�gito no valor ASCII equivalente
  saida[1] = '\r';                             // quebra de linha - parte 1
  saida[2] = '\n';                             // quebra de linha - parte 2
  saida[3] = numeroJogadas + '0';              // converte d�gito no valor ASCII equivalente
  saida[4] = '\r';                             // quebra de linha - parte 1
  saida[5] = '\n';                             // quebra de linha - parte 2

  for(i = 0; i < (numeroJogadas - 1); i++){    // percorre o vetor de jogadas j� realizadas
    saida[6 + i*5] = jogadas[i].jogador + '0'; // anota o jogador que fez a jogada
    saida[7 + i*5] = jogadas[i].linha + '0';   // anota a linha da jogada no tabuleiro
    saida[8 + i*5] = jogadas[i].coluna + '0';  // anota a coluna da jogada no tabuleiro
    saida[9 + i*5] = '\r';                     // quebra de linha - parte 1
    saida[10 + i*5] = '\n';                   // quebra de linha - parte 2
  }
  saida[6 + i*5] = jogadas[i].jogador + '0';   // anota o jogador que fez a �ltima jogada
  saida[7 + i*5] = jogadas[i].linha + '0';     // anota a linha da �ltima jogada
  saida[8 + i*5] = jogadas[i].coluna + '0';    // anota a coluna da �ltima jogada

  // Escreve as informa��es no arquivo (incluindo a jogada escolhida)
  printf("\nEscrevendo os seguintes dados no arquivo %s:\n%s\n", nome_arq, saida);
  numBytesEscrever = (unsigned long int) strlen(saida);
  codigoErro = WriteFile(arq,               // ponteiro para o arquivo
                         saida,             // string a ser escrita
                         numBytesEscrever,  // n�mero de bytes a escrever
                         &numBytesEscritos, // n�mero de bytes que foram escritos
                         NULL);             // sem estruturas sobrepostas

  // Trata erros na escrita
  if(codigoErro == 0){
    printf("\n** Erro permanente: nao foi possivel escrever no arquivo. **\n");
    exit(-1);
  }
  else{
    if(numBytesEscritos != numBytesEscrever){
      printf("\n** Erro permanente: numBytesEscritos != numBytesEscrever. **\n");
      exit(-1);
    }
    else{
      printf("Escreveu %lu bytes em %s com sucesso.\n", numBytesEscritos, nome_arq);
    }
  }

  CloseHandle(arq); // Fecha o arquivo
}

/* L�, de um arquivo texto, os dados que indicam as jogadas j� realizadas e
   preenche o buffer de entrada. O arquivo permanece aberto para mant�-lo
   bloqueado. Encerra a execu��o caso n�o consiga ler. */
void leArquivo(HANDLE* arq, char* nome_arq, char* buffer){

  unsigned long int numBytesLidos = 0;

  // Abre arquivo para leitura
  *arq = CreateFile(nome_arq,                     // nome do arquivo
                    GENERIC_READ | GENERIC_WRITE, // abre para leitura e escrita
                    0,                            // n�o compartilha
                    NULL,                         // seguran�a padr�o
                    OPEN_EXISTING,                // arquivo deve existir
                    FILE_ATTRIBUTE_NORMAL,        // arquivo de texto normal
                    NULL);                        // n�o usa template

  // Se estiver bloqueado ou n�o existir ainda, aguarda 1 segundo e tenta novamente
  while(*arq == INVALID_HANDLE_VALUE){
    printf("\nArquivo bloqueado ou inexistente. Tentando abrir novamente em 1 segundo...\n");
    Sleep(1000); // Aguarda por 1 segundo
    *arq = CreateFile(nome_arq,                     // nome do arquivo
                      GENERIC_READ | GENERIC_WRITE, // abre para leitura e escrita
                      0,                            // n�o compartilha
                      NULL,                         // seguran�a padr�o
                      OPEN_EXISTING,                // arquivo deve existir
                      FILE_ATTRIBUTE_NORMAL,        // arquivo de texto normal
                      NULL);                        // n�o usa template
  }

  // L� dados do arquivo. L� todos os caracteres de uma vez.
  // Em fun��o do formato definido para o arquivo, ele ter�, no m�ximo, 49 caracteres
  if( ReadFile(*arq, buffer, TAMANHOBUFFER-1, &numBytesLidos, NULL) == 0 ){
    printf("\n** Erro permanente: nao foi possivel ler do arquivo.\nGetLastError=%08lu\n", GetLastError());
    CloseHandle(*arq);
    exit(-1);
  }

  // Encerra a execu��o em caso de erro na leitura
  if (numBytesLidos < 0 || numBytesLidos > (TAMANHOBUFFER-1)){
    printf("\n** Erro permanente: valor inesperado para o numero de bytes lidos do arquivo %s: %lu bytes ** \n", nome_arq, numBytesLidos);
    CloseHandle(*arq);
    exit(-1);
  }

  // Imprime dados lidos
  printf("\nDados lidos do arquivo %s (%lu bytes): \n", nome_arq, numBytesLidos);
  printf("%s\n", buffer);
}

int main(int argc, char *argv[]){
  HANDLE arquivo = NULL;
  int tabuleiro[3][3] = {{0}};
  int numeroJogadas = 0;
  Jogada jogadas[9];
  Jogada jogada;
  int jogador = 0;
  int linha = 0;
  int coluna = 0;
  int ultimo_jogador = 0;
  int jogo_acabou = 0;
  //PesquisaJogada
  char bufferLeitura[TAMANHOBUFFER] = {'\0'};
  char stringLido[] = {'\0','\0'};
  unsigned long int posicaoAtualArquivo = 0;
  unsigned int semente; // semente usada na gera��o aleat�ria de valores
//  struct timeval agora; // usado para gerar semente para gerador de n�mero aleat�rio

  // Inicializa semente com a hora corrente para posteriormente fazer escolha aleat�ria de jogada.
  /*gettimeofday(&agora, NULL);
  semente = (agora.tv_sec * agora.tv_usec) ^ GetCurrentProcessId(); // ou exclusivo entre (segundos * micro-seg.) e PID
  srand(semente);*/

  // Checa se foram passados 3 par�metros na linha de comandos
  if( argc != 3 ){
    printf("\nErro de uso:\tNumero incorreto de argumentos. Uso:\n\n");
    printf("%s <nome_arquivo> <1=1o jogador ou 2=2o jogador>\n", argv[0]);
    return(-1);
  }

  // Se for o 1� jogador
  if(atoi(argv[2]) == 1){

    // Escolhe a 1� jogada, adiciona-a ao tabuleiro e � lista de jogadas j� efetuadas
    jogada = escolheJogada(&tabuleiro, 1);
    jogadas[numeroJogadas++] = jogada;
    printf("\nJogada escolhida: %d%d%d\n", jogada.jogador, jogada.linha, jogada.coluna);

    // Abre arquivo novo para escrita, bloqueando o acesso por outros programas
    // OBS: fun��o espec�fica do Sistema Operacional Windows!
    arquivo = CreateFile(argv[1],               // nome do arquivo
                         GENERIC_WRITE,         // abre para escrita
                         0,                     // n�o compartilha
                         NULL,                  // seguran�a padr�o
                         CREATE_ALWAYS,         // cria novo arquivo (sobrescreve caso j� exista)
                         FILE_ATTRIBUTE_NORMAL, // arquivo de texto normal
                         NULL);                 // n�o usa template

    // Escreve jogada no arquivo e fecha-o (desbloqueia o arquivo)
    escreveJogadas(arquivo, argv[1], 1, numeroJogadas, jogadas);

    imprimeTabuleiro(tabuleiro);

    // Aguarda 1 segundo para continuar
    Sleep(1000);

    // Continua jogando at� o fim do jogo
    while(! jogo_acabou){

      ultimo_jogador = 1;

      // Repete leitura at� que o jogador 2 (advers�rio) tenha jogado
      while(ultimo_jogador != 2){
        leArquivo(&arquivo, argv[1], bufferLeitura);
        stringLido[0] = bufferLeitura[0];
        ultimo_jogador = atoi(stringLido);
        if(ultimo_jogador != 2){
          CloseHandle(arquivo);
          printf("\nAguardando a jogada do adversario. Tentando ler novamente em 1 segundo...\n");
          Sleep(1000);
        }
      }

      // Anota a �ltima jogada no tabuleiro
      stringLido[0] = bufferLeitura[3]; // l� o n�mero de jogadas
      numeroJogadas = atoi(stringLido); // converte o n�mero de jogadas em inteiro
      if(numeroJogadas < 1 || numeroJogadas > 9){ // checa se jogador da �ltima jogada coincide com �ltimo jogador
        printf("\n** Erro permanente: n�mero de jogadas (%d) anotado no arquivo %s invalido ** \n", numeroJogadas, argv[1]);
        return(-1);
      }
      stringLido[0] = bufferLeitura[6 + (numeroJogadas-1)*5]; // l� o n�mero do jogador da �ltima jogada
      jogador = atoi(stringLido); // converte o n�mero do jogador em inteiro
      if(jogador != ultimo_jogador){ // checa se jogador da �ltima jogada coincide com �ltimo jogador
        printf("\n** Erro permanente: n�mero do �ltimo jogador (%d) anotado no arquivo %s n�o corresponde ao numero anotado na ultima jogada: %d ** \n", ultimo_jogador, argv[1], jogador);
        return(-1);
      }
      stringLido[0] = bufferLeitura[7 + (numeroJogadas-1)*5]; // l� o n�mero da linha da �ltima jogada
      linha = atoi(stringLido); // converte o n�mero da linha em inteiro
      stringLido[0] = bufferLeitura[8 + (numeroJogadas-1)*5]; // l� o n�mero da coluna da �ltima jogada
      coluna = atoi(stringLido); // converte o n�mero da coluna em inteiro
      tabuleiro[linha][coluna] = jogador;

      // Anota a �ltima jogada no vetor de jogadas
      jogadas[numeroJogadas-1].jogador = jogador;
      jogadas[numeroJogadas-1].coluna = coluna;
      jogadas[numeroJogadas-1].linha = linha;

      imprimeTabuleiro(tabuleiro);

      // Checa se o jogo acabou
      if(jogoAcabou(tabuleiro)){
        return(0);
      }

      // Escolhe jogada, adiciona-a ao tabuleiro e � lista de jogadas j� efetuadas
      jogada = escolheJogada(&tabuleiro, 1);
      jogadas[numeroJogadas++] = jogada;
      printf("\nJogada escolhida: %d%d%d\n", jogada.jogador, jogada.linha, jogada.coluna);

      // Reposiciona o cursor no in�cio do arquivo
      posicaoAtualArquivo = SetFilePointer(arquivo,     // ponteiro para o arquivo
                                           0,           // n�o move o cursor em rela��o ao 4� par�metro
                                           NULL,        // n�o move o cursor em rela��o ao 4� par�metro
                                           FILE_BEGIN); // move para o in�cio do arquivo

      // Confirma se o reposicionamento do cursor foi realizado
      if(posicaoAtualArquivo == INVALID_SET_FILE_POINTER){
        printf("\n ** Erro ao reposicionar o cursor para o inicio do arquivo ** \n");
        CloseHandle(arquivo);
        return(-1);
      }

      // Escreve jogadas no arquivo e fecha-o (desbloqueia o arquivo)
      escreveJogadas(arquivo, argv[1], 1, numeroJogadas, jogadas);

      imprimeTabuleiro(tabuleiro);

      // Checa se o jogo acabou
      if(jogoAcabou(tabuleiro)){
        return(0);
      }
    }
  }
  else if(atoi(argv[2]) == 2){// Se for o 2� jogador

    // Continua jogando at� o fim do jogo
    while(! jogo_acabou){

      ultimo_jogador = 2;

      // Repete leitura at� que o jogador 1 (advers�rio) tenha jogado
      while(ultimo_jogador != 1){
        leArquivo(&arquivo, argv[1], bufferLeitura);
        stringLido[0] = bufferLeitura[0];
        ultimo_jogador = atoi(stringLido);
        if(ultimo_jogador != 1){
          CloseHandle(arquivo);
          printf("\nAguardando a jogada do adversario. Tentando ler novamente em 1 segundo...\n");
          Sleep(1000);
        }
      }

      // Anota a �ltima jogada no tabuleiro
      stringLido[0] = bufferLeitura[3]; // l� o n�mero de jogadas
      numeroJogadas = atoi(stringLido); // converte o n�mero de jogadas em inteiro
      if(numeroJogadas < 1 || numeroJogadas > 9){ // checa se jogador da �ltima jogada coincide com �ltimo jogador
        printf("\n** Erro permanente: n�mero de jogadas (%d) anotado no arquivo %s invalido ** \n", numeroJogadas, argv[1]);
        return(-1);
      }
      stringLido[0] = bufferLeitura[6 + (numeroJogadas-1)*5]; // l� o n�mero do jogador da �ltima jogada
      jogador = atoi(stringLido); // converte o n�mero do jogador em inteiro
      if(jogador != ultimo_jogador){ // checa se jogador da �ltima jogada coincide com �ltimo jogador
        printf("\n** Erro permanente: n�mero do �ltimo jogador (%d) anotado no arquivo %s n�o corresponde ao numero anotado na ultima jogada: %d ** \n", ultimo_jogador, argv[1], jogador);
        return(-1);
      }
      stringLido[0] = bufferLeitura[7 + (numeroJogadas-1)*5]; // l� o n�mero da linha da �ltima jogada
      linha = atoi(stringLido); // converte o n�mero da linha em inteiro
      stringLido[0] = bufferLeitura[8 + (numeroJogadas-1)*5]; // l� o n�mero da coluna da �ltima jogada
      coluna = atoi(stringLido); // converte o n�mero da coluna em inteiro
      tabuleiro[linha][coluna] = jogador;

      // Anota a �ltima jogada no vetor de jogadas
      jogadas[numeroJogadas-1].jogador = jogador;
      jogadas[numeroJogadas-1].coluna = coluna;
      jogadas[numeroJogadas-1].linha = linha;

      imprimeTabuleiro(tabuleiro);

      // Checa se o jogo acabou
      if(jogoAcabou(tabuleiro)){
        return(0);
      }

      // Escolhe jogada, adiciona-a ao tabuleiro e � lista de jogadas j� efetuadas
      jogada = escolheJogada(&tabuleiro, 2);
      jogadas[numeroJogadas++] = jogada;
      printf("\nJogada escolhida: %d%d%d\n", jogada.jogador, jogada.linha, jogada.coluna);

      // Reposiciona o cursor no in�cio do arquivo
      posicaoAtualArquivo = SetFilePointer(arquivo,   // ponteiro para o arquivo
                                         0,           // n�o move o cursor em rela��o ao 4� par�metro
                                         NULL,        // n�o move o cursor em rela��o ao 4� par�metro
                                         FILE_BEGIN); // move para o in�cio do arquivo

      // Confirma se o reposicionamento do cursor foi realizado
      if(posicaoAtualArquivo == INVALID_SET_FILE_POINTER){
        printf("\n ** Erro ao reposicionar o cursor para o inicio do arquivo ** \n");
        CloseHandle(arquivo);
        return(-1);
      }

      // Escreve jogadas no arquivo e fecha-o (desbloqueia o arquivo)
      escreveJogadas(arquivo, argv[1], 2, numeroJogadas, jogadas);

      imprimeTabuleiro(tabuleiro);

      // Checa se o jogo acabou
      if(jogoAcabou(tabuleiro)){
        return(0);
      }
    }
  }
  else{
    printf("\nO valor %s enviado pela linha de comandos nao corresponde a um numero de jogador valido (1 ou 2)\n", argv[2]);
    return(-1);
  }

  return(0);
}

