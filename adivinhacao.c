#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define TENTATIVAS_FACIL 20
#define TENTATIVAS_MEDIO 15
#define TENTATIVAS_DIFICIL 6
#define PONTOS_INICIAL 1000

int main() {

//Define a Semente pra gerar o numero secreto

srand(time(0));

int numerosecreto;
int chute;
int tentativas = 1;
double pontos = PONTOS_INICIAL;
int nivel;
int totaldetentativas;
int acertou = 0;
int interstar;
int interend;
int jogardenovo = 1;

printf("\n\n");
printf("        P /_\\ P 				\n");
printf("      /_\\_|_|_/_\\ 				\n");
printf("  n_n | ||. .|| | n_n          Bem-vindo ao 	\n");
printf("  |_|_|nnnn nnnn|_|_|      Jogo de Adivinhação! \n");
printf(" |\" \" |   |_|  |\"  \" | 			\n");
printf(" |_____| ' _ ' |_____| 				\n");
printf("       \\__|_|__/ 				\n");
printf("\n\n");


while(jogardenovo == 1) {

printf("\nQual o nível de dificuldade?\n");
printf("(1)Fácil (2)Médio (3)Difícil\n\n");
printf("Escolha: ");
scanf("%d", &nivel);

switch(nivel) {

case 1:
	totaldetentativas = TENTATIVAS_FACIL;
	break;
case 2:
	totaldetentativas = TENTATIVAS_MEDIO;
	break;
default:
	totaldetentativas = TENTATIVAS_DIFICIL;
	break;
}

printf("\n\033[33mAgora escolha o intervalo que o computador irá chutar!\033[m");
printf("\n\nDe: ");
scanf("%d", &interstar);
printf("Até: ");
scanf("%d", &interend);

numerosecreto = (rand() % (interend - interstar)) + interstar;

for(int i = 1; i <= totaldetentativas; i++) {

printf("\n\033[32mTentativa %d de %d\033[m", i, totaldetentativas);
printf("\nQual é o seu chute? ");
scanf("%d", &chute);

int lastguessednumber;

if (chute == lastguessednumber) {

	printf("\n\033[31mVocê ja chutou esse número!\033[m\n");
	i--;
	continue;

}

lastguessednumber = chute;

if(chute < 0) {

	printf("\n\033[31mVocê nao pode chutar numeros negativos!\033[m\n");
	i--;
	continue;
}

acertou = chute == numerosecreto;
int maior = chute > numerosecreto;

if(acertou) {

	break;

} else if(maior) {

	printf("\nSeu chute foi maior que o número secreto!\n");

} else {

	printf("\nSeu chute foi menor que o número secreto!\n");

}

double pontosperdidos = abs(chute - numerosecreto) / 2.0;
pontos = pontos - pontosperdidos;
tentativas++;

}

if(acertou) {

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
printf("\nVocê fez %.2f pontos. Até a próxima!\n\n", pontos);

} else {

printf("\n\n\033[31m \\|/ ____ \\|/ 	\n");
printf("  @~/ ,. \\~@ 			\n");
printf(" /_( \\__/ )_\\ 		\n");
printf("    \\__U_/ 			\n");

printf("\n\033[1;31mVOCE PERDEU! \033[mTente novamente!\n\n");
}

printf("\nDeseja jogar novamente? Se sim, Digite 1, senão, digite 0: ");
scanf("%d", &jogardenovo);
}

printf("\n\033[32mOBRIGADO POR JOGAR!!\033[m");
printf("\n\033[33mFim de jogo\033[m\n\n");
}
