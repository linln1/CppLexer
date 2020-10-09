struct point{
    int x;
    float y;
}

int main(int argc, char* argv[]){
    int arr[10];
    struct point a;
    a.x = 1;
    a.y = 3.0;
    for(int i=0; i<10; i++){
        arr[i] = i;
        if( i == 6 ){
            continue;
        }
        else{
            printf("%d, %f", a.x, a.y);
        }
    }
    printf("hello world!\n");
    return 0;
}