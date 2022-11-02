/*Projeto LP - 2� Semestre Ci�ncia da Computa��o - Projeto Jogo da Vida - Julio Arakaki - 2022
    Alice de Oliveira Duarte - RA00319006
    Bruno dos Santos Torres Novo - RA00320039
    Caio Pereira Guimar�es - RA00318945
    Jo�o Pedro do Carmo Ribeiro - RA00319514
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <locale.h>
#include "controller.h"

int main() {

    // Pega as informacoes dos caracteres da lingua portuguesa
    setlocale(LC_ALL, "Portuguese");

    int matrizJogo[100][100]; //Cria a matriz do mapa do jogo
    int geracaoSeguinte[100][100]; //Cria a matriz do mapa do jogo na proxima geracao

    // Evita que o jogador cause um bug no programa em caso de m�-selecao
    while (!0) {

        int opcaoMenu;
        limparTela();

        //Abertura do programa
        printf("\t\t\t\t\t********************************\n");
        printf("\t\t\t\t\t**Bem Vindo ao Jogo da Vida!!!**\n");
        printf("\t\t\t\t\t********************************\n");

        //menu de op��es
        printf("\n");
        printf("Escolha uma op��o para continuar:\n");
        printf("1 -- Jogar\n");
        printf("2 -- Configurar mundo\n");
        printf("3 -- Ver tamanho do mundo atual\n");
        printf("4 -- Carregar um jogo salvo\n");
        printf("5 -- Reiniciar o jogo e suas configuracoes\n");
        printf("6 -- Ver cr�ditos\n");
        printf("7 -- Sair do jogo\n");

        scanf(" %d", &opcaoMenu);

        limparTela();

        switch (opcaoMenu) {

        case 1:
            printf("Aguarde alguns instantes enquanto carregamos o seu jogo...\n\n");
            printf("Tudo pronto para comecarmos a jogar! ;) \n");

            int autoGerarSeres = 0; //captura e salva quantas vezes uma geracao automatica ser� realizada
            float atrasoGeracao = 0; //faz o atraso (delay) entre uma geracao e outra
            bool tudoCerto = true; //Checa o status se est� tudo em conformidade para fazer a proxima geracao

            while (!0) {

                limparTela();

                printf("A gera��o atual � a: %d\n\n", numGeracaoAtual);
                copiarMapa(matrizJogo, geracaoSeguinte);

                if (numGeracaoAtual != 0 && tudoCerto) {
                    analisaJogo(matrizJogo, geracaoSeguinte);
                }
                tudoCerto = true;

                mostrarGeracaoSeguinte(geracaoSeguinte);

                copiarGeracao(matrizJogo, geracaoSeguinte);

                if (autoGerarSeres != 0) {
                    sleep(atrasoGeracao);
                    autoGerarSeres--;
                }
                else {
                    int escolha = 0;
                    scanf("%d", &escolha);
                    if (escolha == 2) {
                        FILE* f = fopen("salvar-carregar.txt", "w");
                        if (f == NULL) {
                            printf("Erro ao abrir o arquivo\n");
                            exit(1);
                        }
                        fprintf(f, "%d;%d;%d\n", maximoEixoX, maximoEixoY, numGeracaoAtual);
                        int auxComanX = 0;

                        while (100 > auxComanX) {
                            int auxComanY = 0;

                            while (100 > auxComanY) {

                                if (matrizJogo[auxComanX][auxComanY] == 1) {
                                    fprintf(f, "1");
                                }
                                else {
                                    fprintf(f, "0");
                                }
                                auxComanY++;
                            }
                            fprintf(f, "\n");
                            auxComanX++;
                        }
                        fclose(f);
                        tudoCerto = false;
                        continue;
                    }

                    if (escolha == 4) {
                        limparTela();
                        int tempo = 0;
                        printf("Quantas vezes voc� deseja simular automaticamente as gera��es?\n");
                        scanf(" %d", &autoGerarSeres);

                        printf("Op��es pr� definidas:\n 1-> 1 segundo\n 2-> 3 segundos\n 3-> 5 segundos\n 4-> 10 segundos\n 5-> 20 segundos\n 6-> Escolher outro tempo (podendo usar numero decimal)\n");
                        scanf(" %d", &tempo);
                        if(tempo == 1){
                            atrasoGeracao = 1;
                        }
                         if(tempo == 2){
                            atrasoGeracao = 3;
                        }
                         if(tempo == 3){
                            atrasoGeracao = 5;
                        }
                         if(tempo == 4){
                            atrasoGeracao = 10;
                        }
                         if(tempo == 5){
                            atrasoGeracao = 20;
                        }
                         if(tempo == 6){
                        printf("Quantos segundos de atraso (delay utilizando virgula) ?\n");
                        scanf(" %f", &atrasoGeracao);
                        }
                    }
                    if (escolha == 5) {
                        printf("Levando voc� de volta para o menu do jogo. Por favor aguarde...\n")/
                        sleep(2);
                        main();
                    }
                    if (escolha == 6) {
                        limpezaTotal(matrizJogo);
                    }
                    if (escolha == 1) {
                        limparTela();

                        int opcao = 0;
                        printf("Escolha um padr�o para ser carregado.\n");
                        printf("Ao escolher um padr�o o seu jogo ser� deletado.");
                        printf("\nSair: 99\nInserir Manualmente: 0\nBlinker: 1\nToad: 2\nGlider: 3\n");
                        scanf(" %d", &opcao);

                        if(opcao == 99){
                            tudoCerto = false;
                            continue;
                        }
                        if (opcao == 0) {
                            insereSerVivo(matrizJogo);
                        }
                        if (opcao == 1) {
                            matrizJogo[1][0] = 1;
                            matrizJogo[1][1] = 1;
                            matrizJogo[1][2] = 1;
                        }
                        if (opcao == 2) {
                            matrizJogo[1][1] = 1;
                            matrizJogo[1][2] = 1;
                            matrizJogo[1][3] = 1;
                            matrizJogo[2][0] = 1;
                            matrizJogo[2][1] = 1;
                            matrizJogo[2][2] = 1;
                        }
                        if (opcao == 3) {
                            matrizJogo[0][0] = 1;
                            matrizJogo[1][1] = 1;
                            matrizJogo[1][2] = 1;
                            matrizJogo[2][1] = 1;
                            matrizJogo[2][0] = 1;
                        }
                        tudoCerto = false;
                        continue;
                    }
                }
                numGeracaoAtual++;
            }
            return 0;

        case 2:
            configuracaoGeral(matrizJogo);
            break;

        case 3:
            tamanhoAtual();
            break;

        case 4:
            carregarJogo(matrizJogo, true);
            break;

        case 5:
            printf("Reiniciando o jogo, por favor aguarde alguns instantes...\n\n\n");
            sleep(5);
            limparTela();
            break;

        case 6:
            creditos();
            break;

        case 7:
            saida();
            break;
        }
    }
}
