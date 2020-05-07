/****************************************************************
    Nome: Matheus Barbosa Silva
    NUSP: 11221741

    Fonte e comentários: O c1 e c2 escolhidos foram os mais con-
    sistentes encontrados quanto à formação de sequências aleató-
    rias com desvios pequenos (em uma execução com a semente igual
    a 0.3267962 e 1000 simulações, por exemplo, cada carta é encon-
    trada em média 3500 vezes pelo jogador, com variância pequena).

****************************************************************/

#include<stdio.h>
#define C1 73263
#define C2 0.75721

double frac ( double num ){
    int mant = num;
    return num - mant;
}

double modulo ( double num ){
    if ( num > 0)
        return num;
    else
        return -num;
}

double seno( double x ){
    double den = 1, termo = x;
    double res = termo;
    int i;

    for ( i = 2; modulo(termo) >= 0.00000001; i++ ){
        termo = (-termo * x * x * den ) / ( den * (2*i - 1) * (2*i - 2) );
        den = den * (2*i - 1) * (2*i - 2);
        res += termo;
    }

    return res;
}

int main(){
    double x = 1, porcent = 0;
    int num_sim, limiar, sim_feitas = 0, pont_jog = 0, pont_banca = 0, carta, i;
    int vitorias_jog = 0;

    while ( x <= 0 || x >= 1){
        printf("Digite a semente (0 < x < 1): ");
        scanf("%lf", &x);
    }

    printf("Digite o número de simulações para cada limiar: ");
    scanf("%d", &num_sim);

    for ( limiar = 12; limiar < 21; limiar++ ){
        for( sim_feitas = 0; sim_feitas < num_sim; sim_feitas++ ){
            while( pont_jog < limiar ){
                x = frac( C1 * modulo(seno(x)) + C2); 
                carta = 13 * x + 1;

                if ( carta > 10 ) {
                    carta = 10;
                }
                pont_jog += carta;
            }
        
            if ( pont_jog <= 21 ) {
                //como o empate foi considerado como vitoria da banca, ela para de
                //pegar cartas quando sua pontuacao for maior ou igual a do jogador.
                while ( pont_banca < pont_jog ) {
                    x = frac( C1 * modulo(seno(x)) + C2);
                    carta = 13 * x + 1;

                    if ( carta > 10 ) {
                        carta = 10;
                    }
                    pont_banca += carta;
                }

                if ( pont_banca > 21 ) {
                    vitorias_jog++;
                }
            }

            pont_jog = 0;
            pont_banca = 0;
        }
        porcent = ( (double) vitorias_jog / num_sim ) * 100.0;
        printf("%d ( %4.2lf%%) : ", limiar, porcent);
        for( i = 1; i <= porcent; i++){
            printf("*");
        }
        printf("\n");
        vitorias_jog = 0;
    }
}