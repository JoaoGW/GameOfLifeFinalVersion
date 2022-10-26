int maximoEixoX = 20; //Valor máximo em X
int maximoEixoY = 20; //Valor máximo em Y
int numGeracaoAtual = 0; //Indica qual a geração que o programa se encontra atualmente

//exporta o mapa do jogo de uma tela para outra mantendo o jogo funcionando
void copiarMapa(int matrizJogo[100][100], int geracaoSeguinte[100][100]) {

	int auxComanX = 0;

	while (maximoEixoX > auxComanX) {

		int auxComanY = 0;
		while (maximoEixoY > auxComanY) {
			geracaoSeguinte[auxComanX][auxComanY] = matrizJogo[auxComanX][auxComanY];
			auxComanY++;
		}
		auxComanX++;
	}
}

//faz com que o jogador possa visualizar corretamente qual será o próximo mapa após o comando de geração
//menu de opções dentro da jogada
void mostrarGeracaoSeguinte(int geracaoSeguinte[100][100]) {

	int auxComanX = 0;

	while (maximoEixoX > auxComanX) {

		int auxComanY = 0;

		printf("||");

		while (maximoEixoY > auxComanY) {

			if (geracaoSeguinte[auxComanX][auxComanY] == 0) {

				printf("-", geracaoSeguinte[auxComanX][auxComanY]); //Linha por coluna com espaço vazio
			}
			else {
				printf("*"); //Linha por coluna com ser vivo
			}
			auxComanY++;
		}
		int quociente = maximoEixoX / 2;
		printf("||%d",auxComanX+1);

		if (auxComanX == quociente - 2) {
			printf("\tNúmero de células vivas é: %d", qtdSeresVivos(geracaoSeguinte));
		}
		if (auxComanX == quociente) {
			printf("\t1 - Para inserir seres vivos");
		}
		if (auxComanX == quociente + 1) {
			printf("\t2 - Para salvar");
		}
		if (auxComanX == quociente + 2) {
			printf("\t3 - Para avançar");
		}
		if (auxComanX == quociente + 3) {
			printf("\t4 - Para simular automaticamente");
		}
		if (auxComanX == quociente + 4) {
			printf("\t5 - Para voltar ao menu anterior");
		}
		if (auxComanX == quociente + 5) {
			printf("\t6 - Para fazer a limpeza das células do mundo");
		}
		printf("\n");
		auxComanX++;
	}

}

//limpa por completo todas as entradas
void limpezaTotal(int matrizJogo[100][100]) {

	int auxComanX = 0;
	while (100 > auxComanX) {

		int auxComanY = 0;
		while (100 > auxComanY) {
			matrizJogo[auxComanX][auxComanY] = 0;
			auxComanY++;
		}
		auxComanX++;
	}
	limparTela();
	printf("Aplicando configurações. Isto será rápido, eu prometo...\n");
	sleep(5);
}

//créditos aos criadores e ao professor
void creditos() {
	limparTela();
	printf("Projeto Jogo da Vida para a Disciplina de Laboratorio de Programacao LP\n");
	sleep(2);
	printf("Pontificia Universidade Catolica de Sao Paulo (PUC-SP), 2022 - Turma COM-MA2A\n");
	sleep(2);
	printf("Professor Julio Arakaki\n");
	sleep(2);
	printf("Grupo: Alice de Oliveira, Bruno dos Santos, Caio Pereira e Joao Pedro do Carmo\n");
	sleep(2);
	printf("Levando voce de Volta ao Menu. Obrigado por visitar os creditos!\n");
	sleep(4);

	limparTela();

}
