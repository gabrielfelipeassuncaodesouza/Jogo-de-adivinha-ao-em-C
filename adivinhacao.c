#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TENTATIVAS_FACIL 20
#define TENTATIVAS_MEDIO 15
#define TENTATIVAS_DIFICIL 6
#define PONTOS_INICIAL 1000

typedef struct snumber {

	int numeroSecreto;
	int interEnd;
	int interStar;

} snumber;

typedef struct gameState {

	snumber snumber;
	int tentativas;
	double pontos;
	int nivel;
	int totaldetentativas;
	bool acertou;
	bool jogardenovo;

} gameState;

gameState game;

void init() {
	srand(time(0));

	game.snumber.numeroSecreto = 0;
        game.tentativas = 0;
        game.pontos = PONTOS_INICIAL;
	game.nivel = 0;
	game.totaldetentativas = 0; 
        game.acertou = false;
	game.snumber.interStar = 0;
	game.snumber.interEnd = 0;
	game.jogardenovo = false;
}

void printAbertura() {
	printf("\n\n");
	printf("        P /_\\ P 				\n");
	printf("      /_\\_|_|_/_\\ 				\n");
	printf("  n_n | ||. .|| | n_n          Bem-vindo ao 	\n");
	printf("  |_|_|nnnn nnnn|_|_|      Jogo de Adivinhação! \n");
	printf(" |\" \" |   |_|  |\"  \" | 			\n");
	printf(" |_____| ' _ ' |_____| 				\n");
	printf("       \\__|_|__/ 				\n");
	printf("\n\n");

}

void selectGuesses(gameState* game) {
	switch(game->nivel) {

		case 1:
			game->totaldetentativas = TENTATIVAS_FACIL;
			break;
		case 2:
			game->totaldetentativas = TENTATIVAS_MEDIO;
			break;
		default:
			game->totaldetentativas = TENTATIVAS_DIFICIL;
		break;
	}
}

void selectLevel(gameState* game) {
	int buf;

	printf("\nQual o nível de dificuldade?\n");
	printf("(1)Fácil (2)Médio (3)Difícil\n\n");
	printf("Escolha: ");
	scanf("%d", &buf);

	game->nivel = buf;
	selectGuesses(game);
}

void selectInterval(gameState* game) {
	//change to an array
	int buf1, buf2;

	printf("\n\033[33mAgora escolha o intervalo que o computador irá chutar!\033[m");
	printf("\nDe: ");
	scanf("%d", &buf1);
	printf("Até: ");
	scanf("%d", &buf2);

	game->snumber.interStar = buf1;
	game->snumber.interEnd = buf2;
}

void printVitoria() {
	printf("\n\n\033[32m              OOOOOOOOOOO 	\n");
	printf("          OOOOOOOOOOOOOOOOOOO 		\n");
	printf("       OOOOOO  OOOOOOOOO  OOOOOO 	\n");
	printf("     OOOOOO      OOOOO      OOOOOO 	\n");
	printf("   OOOOOOOO  #   OOOOO  #   OOOOOOOO 	\n");
	printf("  OOOOOOOOOO    OOOOOOO    OOOOOOOOOO 	\n");
	printf(" OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO 	\n");
	printf(" OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO 	\n");
	printf(" OOOO  OOOOOOOOOOOOOOOOOOOOOOOOO  OOOO 	\n");
	printf("  OOOO  OOOOOOOOOOOOOOOOOOOOOOO   OOOO 	\n");
	printf("   OOOO   OOOOOOOOOOOOOOOOOOOO   OOOO 	\n");
	printf("     OOOOO   OOOOOOOOOOOOOOO   OOOO 	\n");
	printf("       OOOOOO   OOOOOOOOO   OOOOOO 	\n");
	printf("          OOOOOO         OOOOOO 	\n");
	printf("              OOOOOOOOOOOO 		\n");
	printf("\n\033[1;32mPARABÉNS! \033[mVocê acertou!\n");
	printf("\nVocê fez %.2f pontos. Até a próxima!\n\n", game.pontos);
}

void printDerrota() {
	printf("\n\n\033[31m \\|/ ____ \\|/ 	\n");
	printf("  @~/ ,. \\~@ 			\n");
	printf(" /_( \\__/ )_\\ 		\n");
	printf("    \\__U_/ 			\n");

	printf("\n\033[1;31mVOCE PERDEU! \033[mTente novamente!\n\n");
}

bool jogarNovamente()
{
	int buf;
	printf("\nDeseja jogar novamente? Se sim, Digite 1, senão, digite 0: ");
	scanf("%d", &buf);
	if(buf == 1) return true;
	return false;
}

bool ehValido(int chute) {
	if(chute < 0) {
		printf("\n\033[31mVocê nao pode chutar numeros negativos!\033[m\n");
		return false;
	}
	return true;
}

int chuta(int *chute) {
	printf("\nQual é o seu chute? ");
	scanf("%d", chute);
        return *chute;
}

void gameLoop(int *chute, int qtd) {
	printf("\n\033[32mTentativa %d de %d\033[m", qtd, game.totaldetentativas);
	int c = chuta(chute);
	if(!ehValido(c))
		gameLoop(chute, qtd);
			
	game.acertou = c == game.snumber.numeroSecreto;
	bool maior = c > game.snumber.numeroSecreto;

	if(game.acertou || qtd == game.totaldetentativas)
		return;
	else if(maior)
		printf("\nSeu chute foi maior que o número secreto!\n");
	else 
		printf("\nSeu chute foi menor que o número secreto!\n");

	double pontosperdidos = abs(c - game.snumber.numeroSecreto) / 2.0;
	game.pontos = game.pontos - pontosperdidos;
	game.tentativas++;
	gameLoop(chute, qtd+1);
}

int calculaNumeroSecreto() {
		return (rand() % (game.snumber.interEnd - game.snumber.interStar)) + game.snumber.interStar;
}

int main() {

	int chute;

	init();
	printAbertura();

	do {
		selectLevel(&game);
		selectInterval(&game);

		game.snumber.numeroSecreto = calculaNumeroSecreto();

		gameLoop(&chute, 1);

		if(game.acertou)
			printVitoria();
		else
			printDerrota();
	
	} while(jogarNovamente());

	printf("\n\033[32mOBRIGADO POR JOGAR!!\033[m");
	printf("\n\033[33mFim de jogo\033[m\n\n");
}
