#include "triagem.h"
#include <conio.h>



int main(){
	
	Paciente *p = criar();
	No *atendido = criar_no();
	
	while(1){
		
		menu();
		char op = getch();
		if(op == 27)
			break;
		escolha(op, p, &atendido);
	
	}
	
	return 0;
}