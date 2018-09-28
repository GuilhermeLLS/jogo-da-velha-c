/* Este código tem o intuito de implementar um jogador do Jogo da Velha conforme
   especificação do Trabalho Prático 1 de ALP.

   Para executar um teste, compile este código 2 vezes, gerando dois arquivos de
   saída distintos (exemplo: t1.exe e t2.exe). Depois disso, abra 2 terminais
   (linhas de comando). No 1º terminal, execute o jogador 1 usando o seguinte
   comando:

   t1.exe teste.txt 1

   Em seguida, execute o jogador 2 no outro terminal aberto, indicando o mesmo
   arquivo texto, com o seguinte comando:

   t2.exe teste.txt 2

*/

#define TAMANHOBUFFER 50
#define WIN32_LEAN_AND_MEAN // Usado na implementação da função gettimeofday para geração aleatória de jogadas
#define MaxTam 9
#define Inicio 0

#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h> // Usado na implementação da função gettimeofday para geração aleatória de jogadas

// Usado na implementação da função gettimeofday para geração aleatória de jogadas
/*typedef struct timeval {
    long tv_sec;
    long tv_usec;
} timeval;*/

// Implementa função equivalente à "gettimeofday" do Linux, para geração aleatória de jogadas
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
int Topo_Jog, Topo_Linha, Topo_Coluna, vet_Jog[9], vet_Linha[9],TopoJog, TopoLinha, TopoColuna ,vet_Coluna[9], vetJog[9], vetLinha[9], vetColuna[9];

/* Estrutura que guarda as informações de uma jogada: nº do jogador, linha e coluna selecionadas */
typedef struct Jogada_Pilha{
  int jogador;
  int linha;
  int coluna;
} Jogada;
//=--------------------------------------
//Empilha as jogadas
void EmpilharPilha(int i, Jogada jogadas[i], int numeroJogadas){
  for(i = 0; i < (numeroJogadas - 1); i++){
        Topo_Jog = i;
        Topo_Linha = i;
        Topo_Coluna = i;
        vet_Jog[Topo_Jog] = jogadas[i].jogador;
        vet_Linha[Topo_Linha] = jogadas[i].linha;
        vet_Coluna[Topo_Coluna] = jogadas[i].coluna;
    }
//Inverte a pilha
}
void InverterPilha(int i, Jogada jogadas[i],int numeroJogadas){
  for(i = 0; i < (numeroJogadas - 1); i++){
        Topo_Jog = i;
        Topo_Linha = i;
        Topo_Coluna = i;
		vetJog[TopoJog] = vet_Jog[Topo_Jog];
        vetLinha[TopoLinha] = vet_Linha[Topo_Linha];
        vetColuna[TopoColuna] = vet_Coluna[Topo_Coluna];
    	Topo_Jog--;
    	Topo_Linha--;
    	Topo_Coluna--;
	}
}
//----------------------------------------
//Função a qual  pesquisa a jogada na TAD

/*void PesquisaJogada(int i, Jogada jogadas[9], int numeroJogadas, int vetJog[TopoJog], int vetLinha[TopoLinha],int vetColuna[TopoColuna]){
    int f, g, h, Jog_Desejada;
    printf("Digite qual jogada deseja procurar :");
    scanf("%d", &Jog_Desejada);
    for(f = 0; f <TopoJog ; f++ ){
            for(g = 0; g < TopoLinha ; g++){
                    for(h = 0; h < TopoColuna; h++){
                    }
                }
            }
            printf("Jogada na posição %d eh:%d%d%d", Jog_Desejada, vetJog[f], vetLinha[g], vetColuna[h]);
}
//----------------------------------------

/* Função que escolhe uma jogada e retorna a jogada escolhida */
Jogada escolheJogada(int (*tabuleiro)[3][3], int jogador){
  Jogada disponiveis[9];
  int num_disponiveis = 0, i, j, escolhida;

  // Percorre o tabuleiro anotando as posições vazias (disponíveis)
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      if((*tabuleiro)[i][j] == 0){
        disponiveis[num_disponiveis].linha = i;
        disponiveis[num_disponiveis++].coluna = j;
      }
    }
  }

  // Encerra se não houver jogada para escolher (checar se o jogo acabou antes de escolher jogada)
  if(num_disponiveis == 0){
    printf("\n** Erro permanente: nao ha jogada para escolher! Cheque se o jogo acabou antes de mandar escolher uma nova jogada! **\n");
    exit(-1);
  }

  // Escolhe uma jogada aleatória entre as jogadas disponíveis
  escolhida = (int) (( (double) rand() / (RAND_MAX + 1) ) * 0);

  // Anota o nº do jogador na jogada escolhida
  disponiveis[escolhida].jogador = jogador;

  // Anota a jogada escolhida no tabuleiro
  (*tabuleiro)[disponiveis[escolhida].linha][disponiveis[escolhida].coluna] = jogador;

  return(disponiveis[escolhida]);
}

/* Retorna 1 se o jogo tiver acabado ou retorna 0, caso contrario. */
int jogoAcabou(int tabuleiro[3][3]){
  int i,j, contador = 0;

  // Verifica se há algum alinhamento no tabuleiro
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

  // Verifica se o tabuleiro está cheio (empate)
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


/* Escreve, no arquivo texto, os dados das jogadas já realizadas.
   Fecha o arquivo para que o adversário possa ler a última jogada anotada.
   Encerra a execução caso não consiga escrever. */
void escreveJogadas(HANDLE* arq, char* nome_arq, int jogador, int numeroJogadas, Jogada jogadas[9]){

  int i;                                  // variável de iteração
  int codigoErro = 0;                     // indica eventual erro na escrita
  unsigned long int numBytesEscrever = 0; // número de bytes a escrever no arquivo
  unsigned long int numBytesEscritos = 0; // número de bytes escritos no arquivo
  char saida[50] = {'\0'};                // string a ser escrita no arquivo
	EmpilharPilha(i, &jogadas[i], numeroJogadas);
	InverterPilha(i, &jogadas[i], numeroJogadas);

  // Monta a string completa a ser escrita no arquivo (vide padronização do formato do arquivo na especificação do TP)
  saida[0] = jogador + '0';                    // converte dígito no valor ASCII equivalente
  saida[1] = '\r';                             // quebra de linha - parte 1
  saida[2] = '\n';                             // quebra de linha - parte 2
  saida[3] = numeroJogadas + '0';              // converte dígito no valor ASCII equivalente
  saida[4] = '\r';                             // quebra de linha - parte 1
  saida[5] = '\n';                             // quebra de linha - parte 2
  for(i = 0; i < (numeroJogadas - 1); i++){    // percorre o vetor de jogadas já realizadas
    saida[6 + i*5] = jogadas[i].jogador + '0'; // anota o jogador que fez a jogada
    saida[7 + i*5] = jogadas[i].linha + '0';   // anota a linha da jogada no tabuleiro
    saida[8 + i*5] = jogadas[i].coluna + '0';  // anota a coluna da jogada no tabuleiro
    saida[9 + i*5] = '\r';                     // quebra de linha - parte 1
    saida[10 + i*5] = '\n';                   // quebra de linha - parte 2
  }
  saida[6 + i*5] = jogadas[i].jogador + '0';   // anota o jogador que fez a última jogada
  saida[7 + i*5] = jogadas[i].linha + '0';     // anota a linha da última jogada
  saida[8 + i*5] = jogadas[i].coluna + '0';    // anota a coluna da última jogada

  // Escreve as informações no arquivo (incluindo a jogada escolhida)
  printf("\nEscrevendo os seguintes dados no arquivo %s:\n%s\n", nome_arq, saida);
  numBytesEscrever = (unsigned long int) strlen(saida);
  codigoErro = WriteFile(arq,               // ponteiro para o arquivo
                         saida,             // string a ser escrita
                         numBytesEscrever,  // número de bytes a escrever
                         &numBytesEscritos, // número de bytes que foram escritos
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

/* Lê, de um arquivo texto, os dados que indicam as jogadas já realizadas e
   preenche o buffer de entrada. O arquivo permanece aberto para mantê-lo
   bloqueado. Encerra a execução caso não consiga ler. */
void leArquivo(HANDLE* arq, char* nome_arq, char* buffer){

  unsigned long int numBytesLidos = 0;

  // Abre arquivo para leitura
  *arq = CreateFile(nome_arq,                     // nome do arquivo
                    GENERIC_READ | GENERIC_WRITE, // abre para leitura e escrita
                    0,                            // não compartilha
                    NULL,                         // segurança padrão
                    OPEN_EXISTING,                // arquivo deve existir
                    FILE_ATTRIBUTE_NORMAL,        // arquivo de texto normal
                    NULL);                        // não usa template

  // Se estiver bloqueado ou não existir ainda, aguarda 1 segundo e tenta novamente
  while(*arq == INVALID_HANDLE_VALUE){
    printf("\nArquivo bloqueado ou inexistente. Tentando abrir novamente em 1 segundo...\n");
    Sleep(1000); // Aguarda por 1 segundo
    *arq = CreateFile(nome_arq,                     // nome do arquivo
                      GENERIC_READ | GENERIC_WRITE, // abre para leitura e escrita
                      0,                            // não compartilha
                      NULL,                         // segurança padrão
                      OPEN_EXISTING,                // arquivo deve existir
                      FILE_ATTRIBUTE_NORMAL,        // arquivo de texto normal
                      NULL);                        // não usa template
  }

  // Lê dados do arquivo. Lê todos os caracteres de uma vez.
  // Em função do formato definido para o arquivo, ele terá, no máximo, 49 caracteres
  if( ReadFile(*arq, buffer, TAMANHOBUFFER-1, &numBytesLidos, NULL) == 0 ){
    printf("\n** Erro permanente: nao foi possivel ler do arquivo.\nGetLastError=%08lu\n", GetLastError());
    CloseHandle(*arq);
    exit(-1);
  }

  // Encerra a execução em caso de erro na leitura
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
  char bufferLeitura[TAMANHOBUFFER] = {'\0'};
  char stringLido[] = {'\0','\0'};
  //PesquisaJogada
  unsigned long int posicaoAtualArquivo = 0;
  unsigned int semente; // semente usada na geração aleatória de valores
  //struct timeval agora; // usado para gerar semente para gerador de número aleatório

  // Inicializa semente com a hora corrente para posteriormente fazer escolha aleatória de jogada.
  /*gettimeofday(&agora, NULL);
  semente = (agora.tv_sec * agora.tv_usec) ^ GetCurrentProcessId(); // ou exclusivo entre (segundos * micro-seg.) e PID
  srand(semente);*/

  // Checa se foram passados 3 parâmetros na linha de comandos
  if( argc != 3 ){
    printf("\nErro de uso:\tNumero incorreto de argumentos. Uso:\n\n");
    printf("%s <nome_arquivo> <1=1o jogador ou 2=2o jogador>\n", argv[0]);
    return(-1);
  }

  // Se for o 1º jogador
  if(atoi(argv[2]) == 1){

    // Escolhe a 1ª jogada, adiciona-a ao tabuleiro e à lista de jogadas já efetuadas
    jogada = escolheJogada(&tabuleiro, 1);
    jogadas[numeroJogadas++] = jogada;
    printf("\nJogada escolhida: %d%d%d\n", jogada.jogador, jogada.linha, jogada.coluna);

    // Abre arquivo novo para escrita, bloqueando o acesso por outros programas
    // OBS: função específica do Sistema Operacional Windows!
    arquivo = CreateFile(argv[1],               // nome do arquivo
                         GENERIC_WRITE,         // abre para escrita
                         0,                     // não compartilha
                         NULL,                  // segurança padrão
                         CREATE_ALWAYS,         // cria novo arquivo (sobrescreve caso já exista)
                         FILE_ATTRIBUTE_NORMAL, // arquivo de texto normal
                         NULL);                 // não usa template

    // Escreve jogada no arquivo e fecha-o (desbloqueia o arquivo)
    escreveJogadas(arquivo, argv[1], 1, numeroJogadas, jogadas);

    imprimeTabuleiro(tabuleiro);

    // Aguarda 1 segundo para continuar
    Sleep(1000);

    // Continua jogando até o fim do jogo
    while(! jogo_acabou){

      ultimo_jogador = 1;

      // Repete leitura até que o jogador 2 (adversário) tenha jogado
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

      // Anota a última jogada no tabuleiro
      stringLido[0] = bufferLeitura[3]; // lê o número de jogadas
      numeroJogadas = atoi(stringLido); // converte o número de jogadas em inteiro
      if(numeroJogadas < 1 || numeroJogadas > 9){ // checa se jogador da última jogada coincide com último jogador
        printf("\n** Erro permanente: número de jogadas (%d) anotado no arquivo %s invalido ** \n", numeroJogadas, argv[1]);
        return(-1);
      }
      stringLido[0] = bufferLeitura[6 + (numeroJogadas-1)*5]; // lê o número do jogador da última jogada
      jogador = atoi(stringLido); // converte o número do jogador em inteiro
      if(jogador != ultimo_jogador){ // checa se jogador da última jogada coincide com último jogador
        printf("\n** Erro permanente: número do último jogador (%d) anotado no arquivo %s não corresponde ao numero anotado na ultima jogada: %d ** \n", ultimo_jogador, argv[1], jogador);
        return(-1);
      }
      stringLido[0] = bufferLeitura[7 + (numeroJogadas-1)*5]; // lê o número da linha da última jogada
      linha = atoi(stringLido); // converte o número da linha em inteiro
      stringLido[0] = bufferLeitura[8 + (numeroJogadas-1)*5]; // lê o número da coluna da última jogada
      coluna = atoi(stringLido); // converte o número da coluna em inteiro
      tabuleiro[linha][coluna] = jogador;

      // Anota a última jogada no vetor de jogadas
      jogadas[numeroJogadas-1].jogador = jogador;
      jogadas[numeroJogadas-1].coluna = coluna;
      jogadas[numeroJogadas-1].linha = linha;

      imprimeTabuleiro(tabuleiro);

      // Checa se o jogo acabou
      if(jogoAcabou(tabuleiro)){
        return(0);
      }

      // Escolhe jogada, adiciona-a ao tabuleiro e à lista de jogadas já efetuadas
      jogada = escolheJogada(&tabuleiro, 1);
      jogadas[numeroJogadas++] = jogada;
      printf("\nJogada escolhida: %d%d%d\n", jogada.jogador, jogada.linha, jogada.coluna);

      // Reposiciona o cursor no início do arquivo
      posicaoAtualArquivo = SetFilePointer(arquivo,     // ponteiro para o arquivo
                                           0,           // não move o cursor em relação ao 4º parâmetro
                                           NULL,        // não move o cursor em relação ao 4º parâmetro
                                           FILE_BEGIN); // move para o início do arquivo

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
  else if(atoi(argv[2]) == 2){// Se for o 2º jogador

    // Continua jogando até o fim do jogo
    while(! jogo_acabou){

      ultimo_jogador = 2;

      // Repete leitura até que o jogador 1 (adversário) tenha jogado
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

      // Anota a última jogada no tabuleiro
      stringLido[0] = bufferLeitura[3]; // lê o número de jogadas
      numeroJogadas = atoi(stringLido); // converte o número de jogadas em inteiro
      if(numeroJogadas < 1 || numeroJogadas > 9){ // checa se jogador da última jogada coincide com último jogador
        printf("\n** Erro permanente: número de jogadas (%d) anotado no arquivo %s invalido ** \n", numeroJogadas, argv[1]);
        return(-1);
      }
      stringLido[0] = bufferLeitura[6 + (numeroJogadas-1)*5]; // lê o número do jogador da última jogada
      jogador = atoi(stringLido); // converte o número do jogador em inteiro
      if(jogador != ultimo_jogador){ // checa se jogador da última jogada coincide com último jogador
        printf("\n** Erro permanente: número do último jogador (%d) anotado no arquivo %s não corresponde ao numero anotado na ultima jogada: %d ** \n", ultimo_jogador, argv[1], jogador);
        return(-1);
      }
      stringLido[0] = bufferLeitura[7 + (numeroJogadas-1)*5]; // lê o número da linha da última jogada
      linha = atoi(stringLido); // converte o número da linha em inteiro
      stringLido[0] = bufferLeitura[8 + (numeroJogadas-1)*5]; // lê o número da coluna da última jogada
      coluna = atoi(stringLido); // converte o número da coluna em inteiro
      tabuleiro[linha][coluna] = jogador;

      // Anota a última jogada no vetor de jogadas
      jogadas[numeroJogadas-1].jogador = jogador;
      jogadas[numeroJogadas-1].coluna = coluna;
      jogadas[numeroJogadas-1].linha = linha;

      imprimeTabuleiro(tabuleiro);

      // Checa se o jogo acabou
      if(jogoAcabou(tabuleiro)){
        return(0);
      }

      // Escolhe jogada, adiciona-a ao tabuleiro e à lista de jogadas já efetuadas
      jogada = escolheJogada(&tabuleiro, 2);
      jogadas[numeroJogadas++] = jogada;
      printf("\nJogada escolhida: %d%d%d\n", jogada.jogador, jogada.linha, jogada.coluna);

      // Reposiciona o cursor no início do arquivo
      posicaoAtualArquivo = SetFilePointer(arquivo,   // ponteiro para o arquivo
                                         0,           // não move o cursor em relação ao 4º parâmetro
                                         NULL,        // não move o cursor em relação ao 4º parâmetro
                                         FILE_BEGIN); // move para o início do arquivo

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

