#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX 150
#define MAX_CONTRATOS 100

typedef struct freguesia {
	int id_freg[6];
	char nome_freguesia[MAX];
}FREGUESIA;

typedef struct data
{
	int dia;
	int mes;
	int ano;
}DATA;

typedef struct leituras
{
	DATA data_leituras[12];
	int leitura[12][1];
	float conta[12][1];//Na primeira "dimensao" e guardado o mes em que foi feita a leitura, na segunda guarda-se o valor a pagar
	int potencia; //Guardar 2.45 como sendo 1, 6.9 como sendo 2 e 13.8 como sendo 3 e fazer um switch
}LEITURA;


typedef struct contrato {
	char nome[MAX];
	int id_contrato[9];
	DATA data;
	FREGUESIA localidade;
	LEITURA contas;
	int contrato_ocupado;
}CONTRACT;

CONTRACT* alocar_contratos(int n_contratos) {
	CONTRACT* contratos = (CONTRACT*)malloc(sizeof(CONTRACT) * n_contratos);

	if (contratos == NULL)
	{
		printf("Erro!\n");
		return 0;
	}

	return contratos;
}

void inicializar_contratos(CONTRACT* contratos)
{
	//Inicializar o reservado com valor false
	int n_contrato, i, j;
	for (n_contrato = 0; n_contrato < MAX_CONTRATOS; n_contrato++)
	{
		contratos[n_contrato].contrato_ocupado = 0;
		
		for(j=0; j<12; j++)
		contratos[n_contrato].contas.leitura[j][0] = 0; //Inicializacao das leituras de cada mes com valor false
	
		for(i=0; i<12; i++)
		{
			contratos[n_contrato].contas.conta[i][0] = 0; //Inicializacao das contas (i representa o numero dos meses) com valor false
		}
	}	
}

float media_conta(CONTRACT *contratos, int pos)
{
	int i, aux_2 = 0;
	float soma=0, media=0; //aux2 conta os contratos com consumo, para depois servir para a divisao
	
	for(i=0; i<12; i++)
		{
			if(contratos[pos].contas.conta[i][0]!=0)
			{
				soma = soma + contratos[pos].contas.conta[i][0];
				aux_2++;
			}
		}
		
	if(aux_2!=0)
	{
		media = soma/aux_2;
		return (media);
	}

return 0;
}

float media_freguesia(CONTRACT *contratos, char* freguesia)
{
	int i, j, aux_2 = 0;
	float soma=0, media=0; //aux2 conta os contratos com consumo, para depois servir para a divisao
	
	for(i=0; i<MAX_CONTRATOS; i++)
		{
			if(strcmp(contratos[i].localidade.nome_freguesia, freguesia)==0)
			{
				for(j=0; j<12; j++)
					if(contratos[i].contas.conta[j][0]!=0)
					{
						soma = soma + contratos[i].contas.conta[j][0];
						aux_2++;
					}
			}
		}
		
	if(aux_2!=0)
	{
		media = soma/aux_2;
		return (media);
	}

return 0;
}

void guardar_contratos_fich_txt(CONTRACT* contratos)
{
	int i, n_contrato, k;
	FILE* fich;
	fich = fopen("Contratos.txt", "w");
	
	if(fich == NULL)
	{
		printf("Erro na abertura do ficheiro!");
		return 0;
	}
	
	fprintf(fich, "\n\t-----LISTA DE CONTRATOS-----\n");
	
	for (n_contrato = 0; n_contrato < MAX_CONTRATOS; n_contrato++)
	{
		if(contratos[n_contrato].contrato_ocupado!=0)
		{
			fprintf(fich, "\nId: ");
			for (i = 0; i < 9; i++)
			{
				fprintf(fich, "%d", contratos[n_contrato].id_contrato[i]);
			}

			fprintf(fich, "\nNome do cliente: %s", contratos[n_contrato].nome);
			fprintf(fich, "\nNome da freguesia: %s", contratos[n_contrato].localidade.nome_freguesia);

			fprintf(fich, "\nId da freguesia: ");
			for (i = 0; i < 6; i++)
			{
				fprintf(fich, "%d", contratos[n_contrato].localidade.id_freg[i]);
			}
			//Print da potencia
			switch (contratos[n_contrato].contas.potencia)
			{
			case 1:
				fprintf(fich, "\nPotência contratada: 2.45kva\n");
				break;
			case 2:
				fprintf(fich, "\nPotência contratada: 6.9kva\n");
				break;
			case 3:
				fprintf(fich, "\nPotência contratada: 13.8kva\n");
				break;
			}
			
			fprintf(fich, "Data da criação do contrato: %d/%d/%d", contratos[n_contrato].data.dia, contratos[n_contrato].data.mes, contratos[n_contrato].data.ano);
			
			fprintf(fich, "\n\n\t-----CONTA DO CLIENTE-----\n\n");
			for(k=0; k<12; k++)
			{
				if(contratos[n_contrato].contas.conta[k][0]!=0)
				{
					verifica_mes_fich(k, fich);
					fprintf(fich, "%.2fEUR\n\n", contratos[n_contrato].contas.conta[k][0]);
				}
			}
				fprintf(fich, "\nO cliente tem uma média de %.2fEUR de consumos", media_conta(contratos, n_contrato));
				fprintf(fich, "\n-------------------------------------------------\n");
			}
		}
	fclose(fich);
}

void guardar_contratos_eliminados_fich_txt(CONTRACT* contratos, int posicao)
{
	int i, k;
	FILE* fich;
	fich = fopen("Contratos Eliminados.txt", "a");
	
	if(fich == NULL)
	{
		printf("Erro na abertura do ficheiro!");
		return 0;
	}
			fprintf(fich, "\nId: ");
			for (i = 0; i < 9; i++)
			{
				fprintf(fich, "%d", contratos[posicao].id_contrato[i]);
			}

			fprintf(fich, "\nNome do cliente: %s", contratos[posicao].nome);
			fprintf(fich, "\nNome da freguesia: %s", contratos[posicao].localidade.nome_freguesia);

			fprintf(fich, "\nId da freguesia: ");
			for (i = 0; i < 6; i++)
			{
				fprintf(fich, "%d", contratos[posicao].localidade.id_freg[i]);
			}
			//Print da potencia
			switch (contratos[posicao].contas.potencia)
			{
			case 1:
				fprintf(fich, "\nPotência contratada: 2.45kva\n");
				break;
			case 2:
				fprintf(fich, "\nPotência contratada: 6.9kva\n");
				break;
			case 3:
				fprintf(fich, "\nPotência contratada: 13.8kva\n");
				break;
			}
			
			fprintf(fich, "Data da criação do contrato: %d/%d/%d", contratos[posicao].data.dia, contratos[posicao].data.mes, contratos[posicao].data.ano);
			
			fprintf(fich, "\n\n\t-----CONTA DO CLIENTE-----\n\n");
			for(k=0; k<12; k++)
			{
				if(contratos[posicao].contas.conta[k][0]!=0)
				{
					verifica_mes_fich(k, fich);
					fprintf(fich, "%.2fEUR\n\n", contratos[posicao].contas.conta[k][0]);
				}
			}
				fprintf(fich, "\nO cliente tem uma média de %.2fEUR de consumos", media_conta(contratos, posicao));
				fprintf(fich, "\n-------------------------------------------------\n");
	fclose(fich);
}

void guardar_contratos_fich_bin(CONTRACT* contratos)
{
	int n_contrato;
	FILE* fich;
	fich = fopen("Contratos.dat", "wb");
	
	if(fich == NULL)
	{
		printf("Erro na abertura do ficheiro!");
		return 0;
	}
	
	for (n_contrato = 0; n_contrato < MAX_CONTRATOS; n_contrato++)
	{
		if(contratos->contrato_ocupado)
		{
			fwrite(contratos, sizeof(CONTRACT), 1, fich);
		}
		contratos++;
	}
	fclose(fich);
}

void guardar_contratos_eliminados_fich_bin(CONTRACT* contratos, int posicao)
{
	FILE* fich;
	fich = fopen("Contratos Eliminados.dat", "ab");
	
	if(fich == NULL)
	{
		printf("Erro na abertura do ficheiro!");
		return 0;
	}
	contratos = contratos + posicao + 1; //Coloca-se o ponteiro a apontar para a posicao em que esta o contrato que foi eliminado
	fwrite(contratos, sizeof(CONTRACT), 1, fich);	
	fclose(fich);
}

void le_contratos_fich_bin(CONTRACT* contratos)
{
	int n_contrato;
	FILE* fich;
	fich = fopen("Contratos.dat", "rb");
	
	if(fich == NULL)
	{
		fprintf(stderr, "Impossivel abrir ficheiro");
		return;
	}
	
	n_contrato=0;
	
	while(!feof(fich))
	{
		n_contrato=0;
		if(n_contrato <= MAX_CONTRATOS)
		{
			fread(contratos, sizeof(CONTRACT), 1, fich);
			contratos++;
		}
		else
		{
			printf("Durante a leitura do ficheiro, atingiu-se o tamanho max do vetor\n.");
			fclose(fich);
			return;
		}
	}
	fclose(fich);
}

void guardar_freguesias_fich_txt(CONTRACT* contratos)
{
	int i, n_contrato, j;
	FILE* fich;
	fich = fopen("Freguesias.txt", "w");
	
	if(fich == NULL)
	{
		printf("Erro na abertura do ficheiro!");
		return 0;
	}
	
	fprintf(fich, "\n\t-----LISTA DE FREGUESIAS-----\n\n");
	
	for (n_contrato = 0; n_contrato < MAX_CONTRATOS; n_contrato++)
	{
		if(contratos[n_contrato].contrato_ocupado!=0)
		{
			if(verificacao_id_freguesia(contratos, contratos[n_contrato].localidade.nome_freguesia, n_contrato)==0)
			{
				for (i = 0; i < 6; i++)
				{
					fprintf(fich, "%d", contratos[n_contrato].localidade.id_freg[i]);
				}
					fprintf(fich, "\t%s\n\n", contratos[n_contrato].localidade.nome_freguesia);
			}
		}
	}
	fclose(fich);
}

int verificacao_id_freguesia(CONTRACT *contratos, char* nome_localidade, int pos)
//Ciclo para ver os contratos anteriores à pos do contrato, se houver pelo menos 1 contrato com o mesmo nome da localidade que o contrato a analisar, retorna false
{
	int i=0, aux=0;
	while(i<pos)
	{	
		if(strcmp(nome_localidade, contratos[i].localidade.nome_freguesia)==0)
		{
			aux++;
		}
		i++;
	}
	
	if(aux==0)
	return 0;
	
	if(aux!=0)
	return 1;
}

void guardar_leituras_fich_txt(CONTRACT* contratos)
{
	int i, n_contrato, j;
	FILE* fich;
	fich = fopen("Leituras.txt", "w");
	
	if(fich == NULL)
	{
		printf("Erro na abertura do ficheiro!");
		return 0;
	}
	
	fprintf(fich, "\n\t-----LEITURAS-----\n\n");
	fprintf(fich, "Id_contrato");
	fprintf(fich, "     Leitura");
	fprintf(fich, "           Data\n\n");
	
	for (n_contrato = 0; n_contrato < MAX_CONTRATOS; n_contrato++)
	{
		if(contratos[n_contrato].contrato_ocupado!=0)
		{
			for(j = 0; j < 12; j++)
			{
				if(contratos[n_contrato].contas.leitura[j][0]!=0)
				{
					for (i = 0; i < 9; i++)
					{
						fprintf(fich, "%d", contratos[n_contrato].id_contrato[i]);
					}
						fprintf(fich, "\t%dKva", contratos[n_contrato].contas.leitura[j][0]);
						fprintf(fich, "\t\t%d/%d/%d\n", contratos[n_contrato].contas.data_leituras[j].dia, contratos[n_contrato].contas.data_leituras[j].mes, contratos[n_contrato].contas.data_leituras[j].ano);
				}
			}
		fprintf(fich, "\n");
		}
			
	}
	fclose(fich);
}

void verifica_mes_fich(int pos, FILE* fich)
{
	switch(pos)
	{
	case 0:
			fprintf(fich, "Consumo em Janeiro: ");
		break;
		
		case 1:
			fprintf(fich, "Consumo em Fevereiro: ");
		break;
		
		case 2:
			fprintf(fich, "Consumo em Março: ");
		break;
		
		case 3:
			fprintf(fich, "Consumo em Abril: ");
		break;
		
		case 4:
			fprintf(fich, "Consumo em Maio: ");
		break;
		
		case 5:
			fprintf(fich, "Consumo em Junho: ");
		break;
		
		case 6:
			fprintf(fich, "Consumo em Julho: ");
		break;
		
		case 7:
			fprintf(fich, "Consumo em Agosto: ");
		break;
		
		case 8:
			fprintf(fich, "Consumo em Setembro: ");
		break;
		
		case 9:
			fprintf(fich, "Consumo em Outubro: ");
		break;
		
		case 10:
			fprintf(fich, "Consumo em Novembro: ");
		break;
		
		case 11:
			fprintf(fich, "Consumo em Dezembro: ");
		break;
	}
}

int mostrar_menu_principal()
{
	//Mostrar as opcoes ao utilizador
	//Ler opcao enquanto nao for valida
	int opcao;
	int opcao_invalida;

	do {
		system("cls");
		printf("+**************************************************************************+\n\n");
		printf("|                              MENU PRINCIPAL                              |\n\n");
		printf("+**************************************************************************+\n");
		printf("\n\t1 - Área de Clientes\n");
		printf("\t2 - Área da Empresa\n");
		printf("\t3 - Estatísticas\n");
		printf("\t4 - Sair e fazer Reset\n");
		printf("\t5 - Sair e Guardar\n");
		printf("\nDigite opcao: ");
		scanf("%d", &opcao);
		printf("\n");
		opcao_invalida = !(opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 5);

		if (opcao_invalida)
		{
			printf("\n\tERRO!! Introduza uma opcao valida!\n\n\n");
			system("pause");
		}
		fseek(stdin, 2, 0);
	} while (opcao_invalida);

	return (opcao);
}

char mostrar_menu_area_contratos()
{
	//Mostrar as opcoes ao utilizador
	//Ler opcao enquanto nao for valida
	char opcao;
	char opcao_invalida;
	do {
		system("cls");
		printf("\t**MENU - ÁREA DO CLIENTE**");
		printf("\n\n\t A - Criar novo contrato;");
		printf("\n\t B - Eliminar contrato;");
		printf("\n\t C - Voltar;");
		printf("\n\n O que pretende fazer?\t");
		scanf("%c", &opcao);
		printf("\n");
		opcao_invalida = !(opcao == 'A' || opcao == 'a' || opcao == 'B' || opcao == 'b' || opcao == 'C' || opcao == 'c');

		if (opcao_invalida)
		{
			printf("\nERRO!! Introduza uma opcao valida!\n\n");
			system("pause");
		}
		fseek(stdin, 2, 0);
	} while (opcao_invalida);

	return (opcao);
}

char mostrar_menu_area_empresa()
{
	//Mostrar as opcoes ao utilizador
	//Ler opcao enquanto nao for valida
	char opcao;
	char opcao_invalida;
	do {
		system("cls");
		printf("\t**MENU - ÁREA DA EMPRESA**");
		printf("\n\n\t A - Listar contratos;");
		printf("\n\t B - Listar média de consumos por freguesia;");
		printf("\n\t C - Adicionar Leitura;");
		printf("\n\t D - Procurar contrato;");
		printf("\n\t E - Voltar;");
		printf("\n\n O que pretende fazer?\t");
		scanf("%c", &opcao);
		printf("\n");
		opcao_invalida = !(opcao == 'A' || opcao == 'a' || opcao == 'B' || opcao == 'b' || opcao == 'C' || opcao == 'c' || opcao == 'D' || opcao == 'd' || opcao == 'E' || opcao == 'e');

		if (opcao_invalida)
		{
			printf("\nERRO!! Introduza uma opcao valida!\n\n");
			system("pause");
		}
		fseek(stdin, 2, 0);
	} while (opcao_invalida);

	return (opcao);
}

void copiar_id(int* arr_origem, int* arr_destino, int n)
{
	int i;
	for(i=0; i<n; i++)
		arr_destino[i] = arr_origem[i];
}

void escrever_array(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d", arr[i]);
}

void id_contrato_random_multiplos_10(CONTRACT* contrato, int pos)
{
	int i = 0;
	int array[9] = {0}; //Inicializar um array com 9 casas todas a 0 para que se possa incrementar uma unidade, posteriormente
	srand(time(0)); //Seed para a geracao de numeros aleatorios, tem como ponto de partida o relógio do computador, e visto que este esta sempre a mudar, a geracao vai ser sempre diferente

	for (i = 0; i < 20; i++) //Com este ciclo definimos a soma (no lugar do 20 podia meter-se um multiplo qualquer de 10)
	{
		array[rand() % 9]++; //a funcao rand() % 9 vai gerar um algarismo de 0 a 9, correspondendo a uma das casas do vetor e o ++ vai incrementar uma unidade a essa casa
	}
	escrever_array(array, 9); //Dar print ao array gerado

	for (i = 0; i < 9; i++)
	{
		contrato[pos].id_contrato[i] = array[i]; //Igualar o id contrato ao array criado
	}

}

void id_freguesia_random(CONTRACT* contrato, int pos) //Funcao identica a usada para criar o id do contrato
{
	int i;
	int array[6] = { 0 };
	srand(time(0));

	for (i = 0; i < 18; i++) //Definiu-se a soma como 18 para haver um pouco mais de aleatoridade
	{
		array[rand() % 6]++;
	}

	for (i = 0; i < 6; i++)
	{
		contrato[pos].localidade.id_freg[i] = array[i];
	}
}

int calcula_tamanho_nome(char* nome)
{
	int i=0;
	while(*nome!='\0')
	{
		i++;
		nome++;
	}
	return i;
}

int verificacao_nome(CONTRACT* contratos, char* nome_comp, int pos, int tam)
{
	int j;	
	for(j=0; j<tam; j++)
	{
		if(contratos[pos].nome[j]!=nome_comp[j])
			return 0;
	}
	return 1;
}

int verificacao_apelido(CONTRACT* contratos, char* apelido, int pos, int tam_nome, int tam_apelido)
{
	int j;
	for(j=0; j<tam_apelido; j++)
	{
		if(contratos[pos].nome[j+tam_nome+1]!=apelido[j])//Ao pedir o segundo nome, temos de acrescentar o tam nome próprio mais uma unidade por causa do espaço
			return 0;
	}
	return 1;
}

int verificacao_nome_freguesia(CONTRACT* contratos, char* nome_comp, int pos, int tam)
{
	int j;	
	for(j=0; j<tam; j++)
	{
		if(contratos[pos].localidade.nome_freguesia[j]!=nome_comp[j])
			return 0;
	}
	return 1;
}

void verifica_mes(int pos)
{
	switch(pos)
	{
		case 0:
			printf("Consumo em Janeiro: ");
		break;
		
		case 1:
			printf("Consumo em Fevereiro: ");
		break;
		
		case 2:
			printf("Consumo em Março: ");
		break;
		
		case 3:
			printf("Consumo em Abril: ");
		break;
		
		case 4:
			printf("Consumo em Maio: ");
		break;
		
		case 5:
			printf("Consumo em Junho: ");
		break;
		
		case 6:
			printf("Consumo em Julho: ");
		break;
		
		case 7:
			printf("Consumo em Agosto: ");
		break;
		
		case 8:
			printf("Consumo em Setembro: ");
		break;
		
		case 9:
			printf("Consumo em Outubro: ");
		break;
		
		case 10:
			printf("Consumo em Novembro: ");
		break;
		
		case 11:
			printf("Consumo em Dezembro: ");
		break;
	}
}

void criar_contrato(CONTRACT contratos[MAX_CONTRATOS])
{
	int n_contrato=0, opcao, opcao_dia, opcao_mes, opcao_ano, opcao_invalida_potencia, opcao_invalida_dia, opcao_invalida_mes, opcao_invalida_ano, tam_nome_freguesia, pos_contrato_nome_freguesia, nome_repetido=0;
	int i=0;
	
	while((contratos[n_contrato].contrato_ocupado!=0) && (n_contrato<MAX_CONTRATOS))
		{
			n_contrato++;
		}
	if(n_contrato<MAX_CONTRATOS)
	{
			fseek(stdin, 0, 2);
			printf("\nNome do cliente: ");
			fseek(stdin, 0 ,2);
			gets(contratos[n_contrato].nome);
			printf("Nome da freguesia: ");
			fseek(stdin, 0, 2);
			gets(contratos[n_contrato].localidade.nome_freguesia);
			
			tam_nome_freguesia=calcula_tamanho_nome(contratos[n_contrato].localidade.nome_freguesia);
			
			while(i<MAX_CONTRATOS)
				{
					if(contratos[i].contrato_ocupado!=0)
						if(verificacao_nome_freguesia(contratos, contratos[n_contrato].localidade.nome_freguesia, i, tam_nome_freguesia))
							{
								pos_contrato_nome_freguesia=i;
								nome_repetido++;
							}
						i++;
				}
				
			if(nome_repetido!=0)
			{
				copiar_id(contratos[pos_contrato_nome_freguesia].localidade.id_freg, contratos[n_contrato].localidade.id_freg, 6);
			}
			
			else
			{
				id_freguesia_random(contratos, n_contrato);
			}
				
			printf("\nId do contrato de %s: ",contratos[n_contrato].nome);
			id_contrato_random_multiplos_10(contratos, n_contrato);	
			printf("\nId de %s: ",contratos[n_contrato].localidade.nome_freguesia);
			escrever_array(contratos[n_contrato].localidade.id_freg, 6);
			printf("\n\nQual a potencia contratada?\n");
			printf("\nInsira:\n1 para 2.45kva;\n2 para 6.9kva;\n3 para 13.8kva:\n");
			printf("\nEscolha uma opção: ");
			do
			{
				scanf("%d", &opcao);
				opcao_invalida_potencia = !(opcao == 1 || opcao == 2 || opcao == 3);
				
				if (opcao_invalida_potencia)
				{
					printf("\nERRO!! Introduza uma opcao valida!\n\n");
				}
				fseek(stdin, 2, 0);	
				
			}while(opcao_invalida_potencia);
				
				switch (opcao)
					{
					case 1: contratos[n_contrato].contas.potencia = 1; break;
					case 2: contratos[n_contrato].contas.potencia = 2; break;
					case 3: contratos[n_contrato].contas.potencia = 3; break;
					default:printf("\nOpcao nao encontrada!"); break;
					}while(opcao!=1 && opcao!=2 && opcao!=3);
		
		printf("\nInsira a data da criação do contrato:\n");
		printf("Dia: ");
			do
			{
				scanf("%d", &opcao_dia);
				opcao_invalida_dia = (opcao_dia < 1 || opcao_dia > 31);
				
				if (opcao_invalida_dia)
				{
					printf("\nERRO!! Introduza um dia válido!\n\n");
				}
				fseek(stdin, 2, 0);	
				
			}while(opcao_invalida_dia);
		contratos[n_contrato].data.dia = opcao_dia;
		
		printf("\nMês (Insira, por exemplo, 1 para designar Janeiro): ");
		do
			{
				scanf("%d", &opcao_mes);
				opcao_invalida_mes = (opcao_mes < 1 || opcao_mes > 12);
				
				if (opcao_invalida_mes)
				{
					printf("\nERRO!! Introduza um mês válido!\n\n");
				}
				fseek(stdin, 2, 0);	
				
		contratos[n_contrato].data.mes = opcao_mes;		
			}while(opcao_invalida_mes);	
					
		printf("\nAno: ");
		do
			{
				scanf("%d", &opcao_ano);
				opcao_invalida_ano = (opcao_ano < 1900 || opcao_ano > 2100);
				
				if (opcao_invalida_ano)
				{
					printf("\nERRO!! Introduza um ano válido!\n\n");
				}
				fseek(stdin, 2, 0);	
				
			}while(opcao_invalida_ano);			
		contratos[n_contrato].data.ano = opcao_ano;	
			
		contratos[n_contrato].contrato_ocupado=1;//Colocação do contrato como ocupado
		for(i=0; i<12; i++)
		{
			contratos[n_contrato].contas.conta[i][1] = 0;
		}
		printf("\nContrato criado com sucesso!\n\n");
	}
			
		if(n_contrato>MAX_CONTRATOS)
			printf("\nNúmero máximo de contratos atingido!!\n");	
}

void eliminar_contrato(CONTRACT contratos[MAX_CONTRATOS], int* n_contratos_criados) //elimina mas só elimina no vetor! Falta eliminar no ficheiro
{
	int i=0, j=0, nome_repetido=0, apelido_repetido=0;
	int tam_nome, tam_apelido,pos_contrato_nome, pos_contrato_apelido;
	int n_contrato, n_contratos_possiveis = 0, n_contratos = 0;
	char nome_proprio[MAX];
	char apelido[MAX];
	
	for (n_contrato = 0; n_contrato < MAX_CONTRATOS; n_contrato++)
	{
		if (contratos[n_contrato].contrato_ocupado == 1)
		{
			n_contratos++;
		}
		else
			n_contratos_possiveis++;
	}

	if (n_contratos == 0)
	{
		printf("\n\n\n\n\tNenhum contrato encontrado!\n\n\n\n\n");
	}
	
	if (n_contratos != 0)
	{
		printf("\nInsira o nome associado ao contrato que pretende remover: ");
		fseek(stdin, 0, 2);
		gets(nome_proprio);
		tam_nome=calcula_tamanho_nome(nome_proprio);//Calcula o número de letras do nome inserido
		//Enquanto nao encontrar um contrato com aquelas informacoes ou enquanto nao chegar ao fim do numero maximo de contratos, acrescenta uma unidade ao i
		while(i<MAX_CONTRATOS)
		{
			if(contratos[i].contrato_ocupado==1)
				if(verificacao_nome(contratos, nome_proprio, i, tam_nome))
					{
					pos_contrato_nome=i;
					nome_repetido++;
					}
			i++;
		}
		switch(nome_repetido)
		{
		case 0:
			printf("\nNenhum contrato associado aos dados inseridos!\n\n");
		break;
		
		case 1:
		{
			printf("\n%s\n", contratos[pos_contrato_nome].nome);
			guardar_contratos_eliminados_fich_txt(contratos,pos_contrato_nome);
			guardar_contratos_eliminados_fich_bin(contratos,pos_contrato_nome);
			contratos[pos_contrato_nome].contrato_ocupado=0;
			printf("\nContrato eliminado com sucesso!\n\n");
		}
		break;
		
		default:
		{
			printf("\nExistem %d contratos associados aos dados inseridos!\n", nome_repetido);
			printf("\nInsira o segundo nome/apelido: ");
			fseek(stdin, 0, 2);
			gets(apelido);
			tam_apelido=calcula_tamanho_nome(apelido);
			while(j<MAX_CONTRATOS)
			{
				
			if(contratos[j].contrato_ocupado==1)
			{
				if(verificacao_apelido(contratos, apelido, j, tam_nome, tam_apelido))
					{
					pos_contrato_apelido=j;
					apelido_repetido++;
					}
				}
			j++;
			}
				if(apelido_repetido==0)
					{
						printf("\nNenhum contrato associado aos dados inseridos!\n");
					}
				if(apelido_repetido == 1)
				{
					printf("\n%s\n", contratos[pos_contrato_apelido].nome);
					guardar_contratos_eliminados_fich_txt(contratos,pos_contrato_nome);
					guardar_contratos_eliminados_fich_bin(contratos,pos_contrato_nome);
					contratos[pos_contrato_apelido].contrato_ocupado=0;
					printf("\nContrato eliminado com sucesso!\n\n");
				}
				else
					printf("\nExistem %d contratos associados aos dados inseridos!\n", apelido_repetido);
		}
		break;
		}
	}
	*n_contratos_criados = n_contratos;
}

void listar_contratos(CONTRACT* contratos)
{
	int n_contrato, aux = 0, n_contratos_possiveis = 0;
	int i, j;

	printf("\n\t-----LISTA DE CONTRATOS-----\n");
	for (n_contrato = 0; n_contrato < MAX_CONTRATOS; n_contrato++)
	{
		if (contratos[n_contrato].contrato_ocupado == 1)
		{
			printf("\nId: ");
			for (i = 0; i < 9; i++)
			{
				printf("%d", contratos[n_contrato].id_contrato[i]);
			}

			printf("\nNome do cliente: %s", contratos[n_contrato].nome);
			printf("\nNome da freguesia: %s", contratos[n_contrato].localidade.nome_freguesia);

			printf("\nId da freguesia: ");
			for (i = 0; i < 6; i++)
			{
				printf("%d", contratos[n_contrato].localidade.id_freg[i]);
			}
			//Print da potencia
			switch (contratos[n_contrato].contas.potencia)
			{
			case 1:
				printf("\nPotência contratada: 2.45kva\n");
				break;
			case 2:
				printf("\nPotência contratada: 6.9kva\n");
				break;
			case 3:
				printf("\nPotência contratada: 13.8kva\n");
				break;
			}
			
			printf("Data da criação do contrato: %d/%d/%d", contratos[n_contrato].data.dia, contratos[n_contrato].data.mes, contratos[n_contrato].data.ano);
			
			printf("\n\n\t-----CONTA DO CLIENTE-----\n\n");
			for(j=0; j<12; j++)
				{
					if(contratos[n_contrato].contas.leitura[j][0] !=0 && contratos[n_contrato].contas.conta[j][0] != 0)
					{
						verifica_mes(j); //Apenas faz a listagem das contas por mês
						printf("%.2fEUR\n", contratos[n_contrato].contas.conta[j][0]);
					}
				}
			printf("\nO cliente tem uma média de %.2fEUR de consumos\n", media_conta(contratos, n_contrato));
			printf("\n-------------------------------------------------\n");
			aux++;
		}
		else
			n_contratos_possiveis++;
	}

	if (aux == 0)
	{
		printf("\n\n\n\n\tNenhum contrato encontrado!\n\n\n\n\n");
	}
	printf("\n\n");
}

int calcular_numero(int gasto, int intervalo_min)
{
	int i = gasto, aux=0;
	
	while(i-intervalo_min!=0)
	{
		i--;
		aux++;
	}
	return aux;
}

void inserir_conta_contrato(CONTRACT* contratos, int* n_contratos_criados)
{
	char nome_proprio[MAX], apelido[MAX];
	int gastos, categoria, extra = 0, aux, mes;
	float  conta = 0;
	int n_contrato, n_contratos_possiveis = 0, n_contratos = 0;
	int opcao_dia, opcao_mes, opcao_ano, opcao_invalida_dia, opcao_invalida_mes, opcao_invalida_ano, pos_contrato_nome, pos_contrato_apelido;
	int i = 0, tam_nome, posicao = 0, opcao = 0, j, nome_repetido = 0, tam_apelido, apelido_repetido;

	for (n_contrato = 0; n_contrato < MAX_CONTRATOS; n_contrato++)
	{
		if (contratos[n_contrato].contrato_ocupado == 1)
		{
			n_contratos++;
		}
		else
			n_contratos_possiveis++;
	}
	
	if (n_contratos == 0)
	{
		printf("\n\n\n\n\tNenhum contrato encontrado!\n\n\n\n\n");
	}
	
	if (n_contratos != 0)
	{
		printf("Insira o nome do cliente: ");
		fseek(stdin, 0, 2);
		gets(nome_proprio);
		tam_nome = calcula_tamanho_nome(nome_proprio);
		
		while(i<MAX_CONTRATOS)
		{
			if(contratos[i].contrato_ocupado==1)
				if(verificacao_nome(contratos, nome_proprio, i, tam_nome))
					{
					pos_contrato_nome=i;
					nome_repetido++;
					}
			i++;
		}
		switch(nome_repetido)
		{
		case 0:
			printf("\nNenhum contrato associado aos dados inseridos!\n\n");
		break;
		
		case 1:
		{
			categoria = contratos[pos_contrato_nome].contas.potencia;//potencia
			//Dar o valor da potencia do cliente
						switch (categoria)
						{
						case 1:
							printf("\nPotência contratada: 2.45kva\n");
							extra = 10;
							break;
						case 2:
							printf("\nPotência contratada: 6.9kva\n");
							extra = 15;
							break;
						case 3:
							printf("\nPotência contratada: 13.8kva\n");
							extra = 20;
							break;
						}
		
						printf("\nQual a leitura, em Kva? ");//intervalo de consumo por mês
						scanf("%d", &gastos);
						printf("\nInsira a data da leitura:\n");
						printf("Dia: ");
							do
							{
								scanf("%d", &opcao_dia);
								opcao_invalida_dia = (opcao_dia < 1 || opcao_dia > 31);
								
								if (opcao_invalida_dia)
								{
									printf("\nERRO!! Introduza um dia válido!\n\n");
								}
								fseek(stdin, 2, 0);	
								
							}while(opcao_invalida_dia);
						
						printf("\nMês (Insira, por exemplo, 1 para designar Janeiro): ");
						do
							{
								scanf("%d", &opcao_mes);
								opcao_invalida_mes = (opcao_mes < 1 || opcao_mes > 12);
								
								if (opcao_invalida_mes)
								{
									printf("\nERRO!! Introduza um mês válido!\n\n");
								}
								fseek(stdin, 2, 0);	
								
						contratos[pos_contrato_nome].contas.data_leituras[opcao_mes-1].mes = opcao_mes;
						contratos[pos_contrato_nome].contas.data_leituras[opcao_mes-1].dia = opcao_dia;
						contratos[pos_contrato_nome].contas.leitura[opcao_mes-1][0] = gastos;	//Guardar os gastos no mes especificado
							}while(opcao_invalida_mes);	
									
						printf("\nAno: ");
						do
							{
								scanf("%d", &opcao_ano);
								opcao_invalida_ano = (opcao_ano < 1900 || opcao_ano > 2100);
								
								if (opcao_invalida_ano)
								{
									printf("\nERRO!! Introduza um ano válido!\n\n");
								}
								fseek(stdin, 2, 0);	
								
							}while(opcao_invalida_ano);			
						contratos[pos_contrato_nome].contas.data_leituras[opcao_mes-1].ano = opcao_ano;	
						do
						{
							
							if(gastos<=300)
							{
								conta+=gastos*0.2;
								gastos-=300;
							}
							
							else if(gastos>300 && gastos<=600)
							{
								aux=calcular_numero(gastos, 300);
								conta+=aux*0.25;
								gastos-=aux;
							}
							
							else if(gastos>600 && gastos<=1000)
							{
								aux=calcular_numero(gastos, 600);
								conta+=aux*0.3;
								gastos-=aux;
							}
							
							else if(gastos>1000)
							{
								aux=calcular_numero(gastos, 1000);
								conta += aux*0.35;
								gastos-=aux;
							}
						
						}while(gastos>=0);
						
							conta = conta + extra;
							printf("\nConta: %.2fEUR", conta);
							printf("\n\n");
							contratos[pos_contrato_nome].contas.conta[opcao_mes-1][0] = conta;
							break;
		}break;
		
			default:
			{	
				printf("\nExistem %d contratos associados aos dados inseridos!\n", nome_repetido);
				printf("\nInsira o segundo nome/apelido: ");
				fseek(stdin, 0, 2);
				gets(apelido);
				tam_apelido=calcula_tamanho_nome(apelido);
				while(j<MAX_CONTRATOS)
				{
					
				if(contratos[j].contrato_ocupado==1)
				{
					if(verificacao_apelido(contratos, apelido, j, tam_nome, tam_apelido))
						{
						pos_contrato_apelido=j;
						apelido_repetido++;
						}
					}
				j++;
				}
					if(apelido_repetido==0)
						{
							printf("\nNenhum contrato associado aos dados inseridos!\n");
						}
					if(apelido_repetido == 1)
					{
						categoria = contratos[pos_contrato_apelido].contas.potencia;//potencia
						//Dar o valor da potencia do cliente
						switch (categoria)
						{
						case 1:
							printf("\nPotência contratada: 2.45kva\n");
							extra = 10;
							break;
						case 2:
							printf("\nPotência contratada: 6.9kva\n");
							extra = 15;
							break;
						case 3:
							printf("\nPotência contratada: 13.8kva\n");
							extra = 20;
							break;
						}
		
						printf("\nQual a leitura, em Kva? ");//intervalo de consumo por mês
						scanf("%d", &gastos);
						printf("\nInsira a data da leitura:\n");
						printf("Dia: ");
							do
							{
								scanf("%d", &opcao_dia);
								opcao_invalida_dia = (opcao_dia < 1 || opcao_dia > 31);
								
								if (opcao_invalida_dia)
								{
									printf("\nERRO!! Introduza um dia válido!\n\n");
								}
								fseek(stdin, 2, 0);	
								
							}while(opcao_invalida_dia);
						
						printf("\nMês (Insira, por exemplo, 1 para designar Janeiro): ");
						do
							{
								scanf("%d", &opcao_mes);
								opcao_invalida_mes = (opcao_mes < 1 || opcao_mes > 12);
								
								if (opcao_invalida_mes)
								{
									printf("\nERRO!! Introduza um mês válido!\n\n");
								}
								fseek(stdin, 2, 0);	
								
						contratos[pos_contrato_apelido].contas.data_leituras[opcao_mes-1].mes = opcao_mes;
						contratos[pos_contrato_apelido].contas.data_leituras[opcao_mes-1].dia = opcao_dia;
						contratos[pos_contrato_apelido].contas.leitura[opcao_mes-1][0] = gastos;	//Guardar os gastos no mes especificado
							}while(opcao_invalida_mes);	
									
						printf("\nAno: ");
						do
							{
								scanf("%d", &opcao_ano);
								opcao_invalida_ano = (opcao_ano < 1900 || opcao_ano > 2100);
								
								if (opcao_invalida_ano)
								{
									printf("\nERRO!! Introduza um ano válido!\n\n");
								}
								fseek(stdin, 2, 0);	
								
							}while(opcao_invalida_ano);			
						contratos[pos_contrato_apelido].contas.data_leituras[opcao_mes-1].ano = opcao_ano;	
						do
						{
							
							if(gastos<=300)
							{
								conta+=gastos*0.2;
								gastos-=300;
							}
							
							else if(gastos>300 && gastos<=600)
							{
								aux=calcular_numero(gastos, 300);
								conta+=aux*0.25;
								gastos-=aux;
							}
							
							else if(gastos>600 && gastos<=1000)
							{
								aux=calcular_numero(gastos, 600);
								conta+=aux*0.3;
								gastos-=aux;
							}
							
							else if(gastos>1000)
							{
								aux=calcular_numero(gastos, 1000);
								conta += aux*0.35;
								gastos-=aux;
							}
						
						}while(gastos>=0);
						
							conta = conta + extra;
							printf("\nConta: %.2fEUR", conta);
							printf("\n\n");
							contratos[pos_contrato_apelido].contas.conta[opcao_mes-1][0] = conta;
							break;
					}
					else
						printf("\nExistem %d contratos associados aos dados inseridos!\n", apelido_repetido);
			}break;
		}
	}
	*n_contratos_criados = n_contratos;
}

void estatistica_n_contratos(CONTRACT* contratos, int* n_contratos_criados)
{
	int n_contrato, n_contratos_possiveis = 0, n_contratos = 0;

	for (n_contrato = 0; n_contrato < MAX_CONTRATOS; n_contrato++)
	{
		if (contratos[n_contrato].contrato_ocupado == 1)
		{
			n_contratos++;
		}
		else
			n_contratos_possiveis++;
	}

	if (n_contratos == 0)
	{
		printf("\n\n\n\n\tNenhum contrato encontrado!\n\n\n\n\n");
	}

	if (n_contratos != 0)
	{
		printf("\nForam criados %d contratos até ao momento.\n", n_contratos);
		printf("\nAinda podem ser criados %d contratos!\n", n_contratos_possiveis);
	}
	*n_contratos_criados = n_contratos;
}

void estatistica_n_contratos_sem_consumo(CONTRACT* contratos, int* n_contratos_criados)
{
	int n_contrato, n_contratos_sem_consumo = 0, n_contratos_com_consumo = 0, k;

	for (n_contrato = 0; n_contrato < MAX_CONTRATOS; n_contrato++)
	{
		if (contratos[n_contrato].contrato_ocupado == 1)
		{
			if (contratos[n_contrato].contas.leitura != 0)
				n_contratos_com_consumo++;

			else
				n_contratos_sem_consumo++;
		}
	}
	if (*n_contratos_criados != 0)
	{
		printf("\nDos contratos criados, há %d contratos sem consumo e %d com consumo!", n_contratos_sem_consumo, n_contratos_com_consumo);
		printf("\n\n");
	}
}

void pesquisa_por_nome(CONTRACT* contratos, int* n_contratos_criados)
{

	int i = 0, j = 0, k, nome_repetido = 0, apelido_repetido = 0;
	int tam_nome, tam_apelido, pos_contrato_nome, pos_contrato_apelido;
	int n_contrato, n_contratos_possiveis = 0, n_contratos = 0;
	char nome_proprio[MAX];
	char apelido[MAX];

	for (n_contrato = 0; n_contrato < MAX_CONTRATOS; n_contrato++)
	{
		if (contratos[n_contrato].contrato_ocupado != 0)
		{
			n_contratos++;
		}
		else
			n_contratos_possiveis++;
	}

	if (n_contratos == 0)
	{
		printf("\n\n\n\n\tNenhum contrato encontrado!\n\n\n\n\n");
	}
	
	if (n_contratos != 0)
	{
		printf("\nInsira o nome do cliente a pesquisar: ");
		fseek(stdin, 0, 2);
		gets(nome_proprio);
		tam_nome = calcula_tamanho_nome(nome_proprio);//Calcula o número de letras do nome inserido
		//Enquanto nao encontrar um contrato com aquelas informacoes ou enquanto nao chegar ao fim do numero maximo de contratos, acrescenta uma unidade ao i
		while (i < MAX_CONTRATOS)
		{
			if (contratos[i].contrato_ocupado == 1)
				if (verificacao_nome(contratos, nome_proprio, i, tam_nome))
				{
					pos_contrato_nome = i;
					nome_repetido++;
				}
			i++;
		}
		switch (nome_repetido)
		{
		case 0:
			printf("\nNenhum contrato associado aos dados inseridos!\n\n");
			break;
	
		case 1:
		{
			printf("\nId: ");
			for (i = 0; i < 9; i++)
			{
				printf("%d", contratos[pos_contrato_nome].id_contrato[i]);
			}
			printf("\nNome do cliente: %s", contratos[pos_contrato_nome].nome);
			printf("\nFreguesia: %s", contratos[pos_contrato_nome].localidade.nome_freguesia);
			
			printf("\nId da freguesia: ");
			for (i = 0; i < 6; i++)
			{
				printf("%d", contratos[pos_contrato_nome].localidade.id_freg[i]);
			}
			//Print da potencia
			switch (contratos[pos_contrato_nome].contas.potencia)
			{
			case 1:
				printf("\nPotência contratada: 2.45kva\n");
				break;
			case 2:
				printf("\nPotência contratada: 6.9kva\n");
				break;
			case 3:
				printf("\nPotência contratada: 13.8kva\n");
				break;
			}
			
			printf("Data da criação do contrato: %d/%d/%d", contratos[pos_contrato_nome].data.dia, contratos[pos_contrato_nome].data.mes, contratos[pos_contrato_nome].data.ano);
			
			printf("\n\n\t-----CONTA DO CLIENTE-----\n\n");
			for(k=0; k<12; k++)
			{
				if(contratos[pos_contrato_nome].contas.leitura[k][0] !=0 && contratos[pos_contrato_nome].contas.conta[k][0] != 0)	
				{
					verifica_mes(k);
					printf("%.2fEUR\n", contratos[pos_contrato_nome].contas.conta[k][0]);
				}
			}
				printf("\nO cliente tem uma média de %.2fEUR de consumos\n\n", media_conta(contratos, pos_contrato_nome));
			}
		break;
	
		default:
		{
			printf("\nExistem %d contratos associados aos dados inseridos!\n", nome_repetido);
			printf("\nInsira o segundo nome/apelido: ");
			fseek(stdin, 0, 2);
			gets(apelido);
			tam_apelido = calcula_tamanho_nome(apelido);
			while (j < MAX_CONTRATOS)
			{
	
				if (contratos[j].contrato_ocupado == 1)
				{
					if (verificacao_apelido(contratos, apelido, j, tam_nome, tam_apelido))
					{
						pos_contrato_apelido = j;
						apelido_repetido++;
					}
				}
				j++;
			}
			if (apelido_repetido == 0)
			{
				printf("\nNenhum contrato associado aos dados inseridos!\n\n");
			}
			if (apelido_repetido == 1)
			{
				printf("\nId: ");
				for (i = 0; i < 9; i++)
				{
					printf("%d", contratos[pos_contrato_nome].id_contrato[i]);
				}
				printf("\nNome do cliente: %s", contratos[pos_contrato_nome].nome);
				printf("\nFreguesia: %s", contratos[pos_contrato_nome].localidade.nome_freguesia);
	
				printf("\nId da freguesia: ");
				for (i = 0; i < 6; i++)
				{
					printf("%d", contratos[pos_contrato_nome].localidade.id_freg[i]);
				}
				//Print da potencia
				switch (contratos[pos_contrato_nome].contas.potencia)
				{
				case 1:
					printf("\nPotência contratada: 2.45kva\n");
					break;
				case 2:
					printf("\nPotência contratada: 6.9kva\n");
					break;
				case 3:
					printf("\nPotência contratada: 13.8kva\n");
					break;
				}
	
				for(k=0; k<12; k++)
				{
					if(contratos[pos_contrato_nome].contas.leitura[k][0]!=0 && contratos[pos_contrato_nome].contas.conta[k][0]!=0)
					{
						verifica_mes(k);
						printf("\nConsumo: %.2fEUR\n", contratos[pos_contrato_nome].contas.conta[k][0]);
					}
				}
				printf("\nO cliente tem uma média de %.2fEUR de consumos\n", media_conta(contratos, pos_contrato_nome));
			}
			else
				printf("\nExistem %d contratos associados aos dados inseridos!\n", apelido_repetido);
		}
		break;
		}
	}
	*n_contratos_criados = n_contratos;
}

void main()
{
	setlocale(LC_ALL, ("Portuguese"));
	int opcao_menu_inicial;
	char opcao_menu_area_contratos, opcao_menu_area_empresa, opcao_menu_ficheiros, nome_freg[MAX];
	int n_contratos = MAX_CONTRATOS;
	int aux = 0;
	int* ptr_aux = &aux;
	CONTRACT* contratos = alocar_contratos(n_contratos);	//Alocaçao para o numero max de contratos (especificado antes das structs)

	inicializar_contratos(contratos);
	le_contratos_fich_bin(contratos);//abre o conteúdo dos contratos.dat  Ou seja, todos os contratos guardados previamente serão automaticamente considerados.
	
	do {
		opcao_menu_inicial = mostrar_menu_principal();
		switch (opcao_menu_inicial)
		{
		case 1:
			fseek(stdin, 0, 2);
			system("cls");
			do {
				opcao_menu_area_contratos = mostrar_menu_area_contratos();
				switch (opcao_menu_area_contratos)
				{
				case 'A':
				case'a':
					system("cls");
					criar_contrato(contratos);
					fseek(stdin, 2, 0);
					break;

				case 'B':
				case 'b':
					system("cls");
					eliminar_contrato(contratos, ptr_aux);
					fseek(stdin, 2, 0);
					break;
				}
				system("pause");
				system("cls");
			} while (opcao_menu_area_contratos != 'C' && opcao_menu_area_contratos != 'c');
			break;
			
		case 2:
			fseek(stdin, 0, 2);
			system("cls");
			do {
				opcao_menu_area_empresa = mostrar_menu_area_empresa();
				switch (opcao_menu_area_empresa)
				{
				case 'A':
				case'a':
					system("cls");
					listar_contratos(contratos);
					fseek(stdin, 2, 0);
					break;

				case 'B':
				case 'b':
					system("cls");
					printf("\nQual o nome da freguesia? ");
					gets(nome_freg);
					printf("\nA média de %s é %.2fEUR\n\n", nome_freg, media_freguesia(contratos, nome_freg));
					fseek(stdin, 2, 0);
					break;
					
				case 'C':
				case 'c':
					system("cls");
					inserir_conta_contrato(contratos, ptr_aux);
					fseek(stdin, 2, 0);
					break;

				case 'D':
				case 'd':
					system("cls");
					pesquisa_por_nome(contratos, ptr_aux);
					break;
				
				}
				system("pause");
				system("cls");
			} while (opcao_menu_area_empresa != 'E' && opcao_menu_area_empresa != 'e');

			break;
			
		case 3:
			system("cls");
			estatistica_n_contratos(contratos, ptr_aux);
			estatistica_n_contratos_sem_consumo(contratos, ptr_aux);
			break;
		
		case 4:
			remove("Contratos.txt");					//Caso o utilizador escolha a opção 4, o programa encerra e:
			remove("Contratos.dat");					//	-No caso de já existirem ficheiros, estes serão removidos e o programa dá reset; 
			remove("Contratos Eliminados.txt");			//	-No caso de não existirem ficheiros, o programa encerra sem guardar os dados em ficheiro .txt e .dat
			remove("Contratos Eliminados.dat");
			remove("Freguesias.txt");
			remove("Leituras.txt");
			system("pause");
			system("cls");
			printf("\n\tFicheiros eliminados.\n");
			printf("\n\tPrograma encerrado. Obrigado!\n");
			return;
			break;
		}
		system("pause");
		system("cls");
		} while (opcao_menu_inicial != 5);
		
		guardar_contratos_fich_txt(contratos);			//Guardar todos os contratos. Isto significa que os contratos são guardados automaticamente quando o programa encerra
		guardar_contratos_fich_bin(contratos);			//Quando o utilizador escolhe a opção 5, o programa encerra e os dados são todos guardados em ficheiro .txt e .dat
		guardar_freguesias_fich_txt(contratos);			//Guardar em .txt apenas permite a visualização dos dados em ficheiro
		guardar_leituras_fich_txt(contratos);			//Guardar em .dat permite que os dados sejam guardados e utilizados na próxima vês que o programa for iniciado
		free(contratos);
		printf("\n\tFicheiros guardados com sucesso.\n");	
		printf("\n\t\tObrigado!\n");
}
