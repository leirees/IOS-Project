

void _cd(const char *dir, int op_dir){

}

int main(int argc, const char *argv[]){
    if (argc==1){
        if(argv[0]=="."){
        //print current directory
        _cd(".",0);
        }else{
            write(1,"You aren't using the command correctly",strlen("You aren't using the command correctly"));
        }
        
    } else if(argc==2){
        int op_dir=0;
        if(argv[0]=="." && argv[1]=="."){
        //go back to the previous directory
        _cd(".",op_dir);
        }
    }else if (argc>2){
        
    }
}