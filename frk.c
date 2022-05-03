#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *somar(void *l);
int total = 0;
int quantidade = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct linha {
    int *nums;
};
int main() {
    printf("Digite o tamanho da matriz: ");
    scanf("%d", &quantidade);
    int matriz[quantidade][quantidade];
    pthread_t threads[quantidade];
    for(int i = 0; i < quantidade; i++) {
        for(int j = 0; j < quantidade; j++) {
            scanf(" %d", &matriz[i][j]);
        }
        struct linha *l = (struct linha*)malloc(sizeof(struct linha));
        l->nums = (int *)malloc(quantidade * sizeof(int));
        l->nums = matriz[i];
        pthread_create(&(threads[i]), NULL, somar, (void *)l);
    }
    for(int i = 0; i<quantidade; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("total %d\n", total);
    return 0;
}
void *somar(void *l)
{
    int soma = 0;
    struct linha *lista = (struct linha*)l;
    for(int i = 0; i < quantidade; i++){
        soma += lista->nums[i];
    }
    pthread_mutex_lock(&mutex);
    total += soma;
    pthread_mutex_unlock(&mutex);
    return l;
}
