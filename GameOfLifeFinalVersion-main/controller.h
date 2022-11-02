#include "view.h"

//faz com que toda a tela do console seja limpa a fim de melhorar o UI
void limparTela () {
	system("cls");
}

//permite que o jogador configure uma nova quantidade de linhas (eixo X) e colunas (eixo Y)
void tamanhoMapa() {

	limparTela();

	int tamanho = 0;

	printf("Insira o tamanho do mundo no jogo:\n");
	scanf("%d", &tamanho);

	if (10 > tamanho || tamanho > 60) {
		printf("O tamanho inserido deve estar entre 10 e 60!\n");
		sleep(3);
		tamanhoMapa();
		return tamanho;
	}
	maximoEixoX = tamanho;
	maximoEixoY = tamanho;
}

//Abre o menu de configurações do jogo
void configuracaoGeral(int matrizJogo[100][100]) {

	limparTela();

	int opcao = 0;

	printf("1 - Alterar tamanho do mundo do jogo\n");
	printf("2 - Voltar\n\n");

	printf("Selecione uma opção:\n");
	scanf("%d", &opcao);

	limparTela();

	switch (opcao) {

	case 1:
		tamanhoMapa();
		break;

	case 2:
		return;
		break;
	}
}

//permite que o jogador selecione e coloque os seres vivos na posição onde desejar
void insereSerVivo(int matrizJogo[100][100]) {
	while (!0) {
		int posicaoX = 0;
		int posicaoY = 0;

		printf("Insira coordenadas para o nascimento do ser vivo(exemplo: X Y)\n");
		printf("Caso voce queria sair, insira 999 999\n");
		scanf("%d %d", &posicaoX, &posicaoY);

		if (posicaoX == 999 && posicaoY == 999) {
			return;
		}

		matrizJogo[posicaoY][posicaoX] = 1;

		printf("A posicao %d %d foi marcada como um ser vivo!\n", posicaoX, posicaoY);
	}
}

//possibilita o jogador ver as informações sobre o tamanho do mundo
void tamanhoAtual(){
	printf("Carregando as informacoes salvas sobre o seu jogo. Por favor aguarde...\n");
	sleep(2);
	printf("O tamanho atual do mapa do jogo e: %d por %d\n", maximoEixoX, maximoEixoY);
	sleep(2);
	printf("Voltando automaticamente para o menu principal...\n");
	sleep(2);
}

//confirmação e validador de saída do jogo
void saida() {
	char opcao = ' ';

	printf("Voce realmente deseja sair do jogo? S - Sim ou N - Nao\n");
	scanf(" %c", &opcao);

	if (opcao == 'S' || opcao == 's'){
		printf("Obrigado por jogar o Jogo da Vida!\n");
		printf("Saindo do Jogo... Por favor aguarde enquanto encerramos o jogo corretamente\n\n");
		exit(0);
	}
	else if (opcao == 'N' || opcao == 'n'){
		return;
	}
	else{
		printf("A opcao selecionada e invalida, por favor insira novamente corretamente a opcao!\n\n");
		saida();
	}
}

/*copia a geracao para a matriz do jogo mantendo o funcionamento correto do codigo
ao armazenar tudo em suas respectivas posicoes corretamente*/
void copiarGeracao(int matrizJogo[100][100], int geracaoSeguinte[100][100]) {

	int auxComanX = 0;
	while (maximoEixoX > auxComanX) {
		int auxComanY = 0;
		while (maximoEixoY > auxComanY) {

			matrizJogo[auxComanX][auxComanY] = geracaoSeguinte[auxComanX][auxComanY];
			auxComanY++;
		}
		auxComanX++;
	}

}

//faz o funcionamento principal do jogo
void analisaJogo(int matrizJogo[100][100], int geracaoSequinte[100][100]) {

	//roda a próxima geração do jogo fazendo com que o jogo continue em funcionamento
	int auxComanX = 0;
	while (maximoEixoX > auxComanX) {

		int auxComanY = 0;
		while (maximoEixoY > auxComanY) {

			//verifica as casas vizinhas e  suas respectivas posições
			int vizinhos = vizinhoPosicaoAtual(auxComanX, auxComanY, matrizJogo, maximoEixoX, maximoEixoY);

			if (matrizJogo[auxComanX][auxComanY] == 1) {
				if (2 > vizinhos) {
					geracaoSequinte[auxComanX][auxComanY] = 0;
				}
				else if (vizinhos > 3) {
					geracaoSequinte[auxComanX][auxComanY] = 0;
				}
				else {
					geracaoSequinte[auxComanX][auxComanY] = 1;
				}
			}
			else {
				if (vizinhos == 3) {
					geracaoSequinte[auxComanX][auxComanY] = 1;
				}
			}
			auxComanY++;
		}
		auxComanX++;
	}

}

//faz uma mesclagem e reprodução dos seres vivos presentes atualmente em jogo
int vizinhoPosicaoAtual(int x, int y, int matrizJogo[100][100], int maxX, int maxY) {

	int vizinhos = 0;

	int cimaX = -1; //caso esteja em cima dele no eixo x
	int cimaY = -1; //caso esteja em cima dele no eixo y
	int baixoX = 1; //caso esteja embaixo dele no eixo x
	int baixoY = 1; //caso esteja embaixo dele no eixo y

	if (0 >= x) {
		cimaX = 0;
	}
	if (0 >= y) {
		cimaY = 0;
	}
	if (x >= maxX - 1) {
		baixoX = 0;
	}
	if (y >= maxY - 1) {
		baixoY = 0;
	}

	int auxComanX = cimaX;

	while (baixoX >= auxComanX) {
		int auxComanY = cimaY;
		while (baixoY >= auxComanY) {
			int novoX = x + auxComanX;
			int novoY = y + auxComanY;

			if (x != novoX || y != novoY) {
				if (matrizJogo[x + auxComanX][y + auxComanY] == 1) {
					vizinhos++;
				}
			}
			auxComanY++;
		}
		auxComanX++;
	}
	return vizinhos;
}

//Faz o cálculo de quantos seres vivos estão ativos no mapa do jogo
int qtdSeresVivos(int geracaoSeguinte[100][100]) {

	int auxComanX = 0;
	int i = 0;

	while (100 > auxComanX) {

		int auxComanY = 0;

		while (100 > auxComanY) {

			if (geracaoSeguinte[auxComanX][auxComanY] == 1) {
				i++;
			}
			auxComanY++;
		}
		auxComanX++;
	}
	return i;
}

//carrega um jogo salvo de um arquivo externo
void carregarJogo(int matrizJogo[100][100], bool preVisualizacao) {

	char* nomeFileSaveLoad = "salvar-carregar.txt";
	FILE* arquivo;
	char linhasTotais[100];
	char* resultado;

	int i;
	arquivo = fopen("salvar-carregar.txt", "rt");

	if (arquivo == NULL) {
		printf("Problemas na abertura do arquivo: %s\n", "nomeFileSaveLoad");
		return;
	}
	i = 0;

	bool header = true;
	int atual = 0;

	//funcionamento do save e abertura do jogo
	while (!feof(arquivo)) {
		resultado = fgets(linhasTotais, 102, arquivo);

		if (resultado) {
			if (header) {
				char* aux;
				char* item;

				aux = strtok(resultado, ";");
				maximoEixoX = strtol(aux, &item, 10);
				aux = strtok(NULL, ";");
				maximoEixoY = strtol(aux, &item, 10);
				aux = strtok(NULL, ";");
				numGeracaoAtual = strtol(aux, (char**)NULL, 10);
				header = false;
			}
			else {
				int index = 0;

				for (index = 0; 100 > index; index++) {
					char lt = linhasTotais[index];
					if (lt == '0') {
						matrizJogo[atual][index] = 0;
					}
					else {
						matrizJogo[atual][index] = 1;
					}
				}
				atual++;
			}
		}
		i++;
	}
	if (preVisualizacao) {
		printf("Pré-Visualização do jogo carregada\n");
		mostrarGeracaoSeguinte(matrizJogo);
		printf("Aperte qualquer tecla para continuar...");
		getch();
	}
	fclose(arquivo);
}
