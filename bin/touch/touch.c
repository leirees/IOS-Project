/**
 * @file touch.c
 * @author Team 2.2
 * 
 * @brief The command used to create items.
 * 
 * @version 0.1
 * @date 2021-03-16
 * 
 * @copyright Copyright (c) 2021
 */


/**
* @brief 
* @param 
*/
 void _touch(char *f_name){

 }

/**
* @brief The main loop of the program.
*
* @param argc argument counter.
* @param argv argument vector.
* @return 0 if it is executed correctly.
*/
 int main(int argc, int *argv[]){
     file = argv[1];
     if(argc>2){
         //It wil print out an error because the command is not used correctly.

     }else if(argc==2){
        //The command is used correctly, so check if there is already a file with the input f_name.
        if (! -f "$file"){

        }else{ //if not exists, then create a new file with that file

        }
     }
     return 0;
 }