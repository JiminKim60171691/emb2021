#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_t thread_object_1, thread_object_2;
pthread_mutex_t lockinput;
int guessNumber=0;
int i=1;
int ready = 0;
void* doSomeThing1(void *arg)                      //랜덤 숫자 1초마다 생성 및 출력하는 함수
{
    pthread_mutex_lock(&lockinput);                  //unlock될 때 까지 lock을 구하는 다른 쓰레드는 블락
    guessNumber = rand();                            //랜덤 숫자 생성
    printf("%d.랜덤 숫자: %d  ", i, guessNumber);     //순서 확인, 랜덤 숫자 출력
    usleep(1000000);                                 //1초마다 동작하기 위해 + 함수 코드 내부 강제 휴식
    ready = 1;                                       //ready 변수 -> 1
    pthread_mutex_unlock(&lockinput);                //unlock
    return NULL;
}

void* doSomeThing2(void *arg)                     //해당 숫자 출력 함수

{   if(ready==1)                                    //랜덤 숫자 생성 및 출력하는 쓰레드 다음에만 동작(순서 지정)
    {
    pthread_mutex_lock(&lockinput);                 //unlock될 때 까지 lock을 구하는 다른 쓰레드는 블락
    printf("출력 숫자: %d\r\n", guessNumber);       //해당 숫자 출력
   
    ready = 0;                                      //이 쓰레드가 연속으로 동작하는 것 방지(순서 지정)
    pthread_mutex_unlock(&lockinput);               //unlock
    }
    return NULL;
}

int main(void)
{
int err;
if (pthread_mutex_init(&lockinput, NULL) != 0)        //mutex 객체 초기화, 실패 경우 실패 메세지 출력
{
printf ("\n Mutex Init Failed!!\n");
return 1;
}

while (1)                                                            //반복문 시작
{
err = pthread_create(&(thread_object_1), NULL, &doSomeThing1, NULL);   //랜덤 숫자 생성 및 출력하는 함수 쓰레드 생성, 실패 경우 실패메세지 출력
if (err != 0)
printf ("Thread Create Error: [%d]\n", err);

err = pthread_create(&(thread_object_2), NULL, &doSomeThing2, NULL);   //해당 숫자 출력 함수 쓰레드 생성, 실패 경우 실패메세지 출력
if (err != 0)
printf ("Thread Create Error: [%d]\n", err);

pthread_join (thread_object_1, NULL);                                 //쓰레드 종료 대기
pthread_join (thread_object_2, NULL);

i++;                                                                  //순서 확인

}
return 0;
}